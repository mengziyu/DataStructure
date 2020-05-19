#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


#define LOAD_FACTOR 0.75 

static struct Entry
{
	int hash = 0;
	void* key=NULL;
	void* value=NULL;
	Entry* next = NULL;
};

static struct Table
{
	Entry* header_entry = NULL;
};

struct Map
{
	//桶长度
	int tab_len = 16;
	Table* tab=new Table[16];
	int size = 0;
};

struct Itr
{
	int tab_index = 0;
	Entry* entry=NULL;
	bool (*has_next)(Map* map,Itr* itr);

};


int get_threshold(int len) {
	return LOAD_FACTOR * len;
}

int get_hash(char* s) {
	int h = 0;
	int len = strlen(s);
	int i = 0;
	for (; i < len; i++)
	{
		h = 31 * h + s[i];
	}
	return h;
}

void copy_data3(void* dst, void* src, size_t sizeof_t) {
	char* tmp_dst = (char*)dst;
	char* tmp_src = (char*)src;
	//复制每个字节数据
	int i = 0;
	for (; i < sizeof_t; i++) {
		*(tmp_dst + i) = *(tmp_src + i);
	}
}

bool equal(void* v1, void* v2,size_t sizeof_t) {
	char* tmp_v1 = (char*)v1;
	char* tmp_v2 = (char*)v2;
	int i = 0;
	bool eq = true;
	for (; i < sizeof_t; i++) {
		if (*(tmp_v1 + i) != *(tmp_v2 + i)) {
			return false;
		}
	}
	return eq;
}

bool has_next(Map* map, Itr* itr) {
	int i = itr->tab_index;
	for (; i < map->tab_len; i++) {
		itr->tab_index = i;
		if (itr->entry == NULL) {
			if (map->tab[i].header_entry != NULL) {
				itr->entry = map->tab[i].header_entry->next;
			}
		}
		else {
			itr->entry = itr->entry->next;
		}
		if (itr->entry != NULL) {
			return true;
		}
	}
	return false;
}

Itr get_itr(Map* map) {
	Itr itr;
	itr.has_next = has_next;
	return itr;
}

void release(Map* map) {
	int i = 0;
	for (; i < map->tab_len; i++) {
		if (map->tab[i].header_entry != NULL) {
			Entry* entry = map->tab[i].header_entry->next;
			//除了结构体，也要释放里面的内容
			while (entry != NULL) {
				Entry* tmp = entry;
				entry = tmp->next;

				free(tmp->key);
				free(tmp->value);
				tmp->next = NULL;
				free(tmp);
			}
			map->tab[i].header_entry->next = NULL;
			free(map->tab[i].header_entry);
		}
	}
}

void grow(Map* map){
	int new_len = map->tab_len * 2;
	Table *new_tab=new Table[new_len];
	int n = new_len - 1;
	int i = 0;
	for (; i < map->tab_len; i++) {
		if (map->tab[i].header_entry != NULL) {
			Entry* entry = map->tab[i].header_entry->next;
			while (entry != NULL) {
				int index = entry->hash & n;
				Entry* next = entry->next;
				//添加到头部
				if (new_tab[index].header_entry == NULL) {
					new_tab[index].header_entry = (Entry*)malloc(sizeof(Entry));
					new_tab[index].header_entry->next = entry;
					entry->next = NULL;
				}
				else {
					entry->next = new_tab[index].header_entry->next;
					new_tab[index].header_entry->next = entry;
				}
				entry = next;
			}
			free(map->tab[i].header_entry);
			map->tab[i].header_entry = NULL;
		}
	}
	map->tab_len = new_len;
	map->tab = new_tab;
}

Entry* create_new_entry(void* key,int hash ,size_t sizeof_k, void* value, size_t sizeof_v) {
	Entry* entry = (Entry*)malloc(sizeof(Entry));
	entry->hash = hash;
	entry->key = malloc(sizeof_k);
	entry->value = malloc(sizeof_v);
	copy_data3(entry->key,key,sizeof_k);
	copy_data3(entry->value,value, sizeof_v);
	entry->next = NULL;
	return entry;
}

void add_entry(Map* map, void* key, int hash,size_t sizeof_k, void* value, size_t sizeof_v,int index) {
	Entry* entry = create_new_entry(key, hash, sizeof_k, value, sizeof_v);
	if (map->tab[index].header_entry == NULL) {
		map->tab[index].header_entry = (Entry*)malloc(sizeof(Entry));
		map->tab[index].header_entry->next= entry;
	}
	else {
		entry->next = map->tab[index].header_entry->next;
		map->tab[index].header_entry->next = entry;
	}
	map->size++;

	//扩容
	if (map->size > get_threshold(map->tab_len)) {
		grow(map);
	}
}

static Entry* get_entry(Map* map,int index,void* key, size_t sizeof_k) {
	//遍历是否有key相同的
	if (map->tab[index].header_entry != NULL) {
		Entry* tmp = map->tab[index].header_entry->next;
		while (tmp != NULL) {
			if (equal(key, tmp->key, sizeof_k)) {
				return tmp;
			}
			tmp = tmp->next;
		}
	}
	return NULL;
}

void put(Map* map, void* key, int key_hash,size_t sizeof_k, void* value,size_t sizeof_v) {
	int n = map->tab_len;
	int index = key_hash & (n - 1);
	Entry* entry = get_entry(map,index,key,sizeof_k);
	if (entry != NULL) {
		copy_data3(entry->value,value,sizeof_v);
		return;
	}
	add_entry(map,key,key_hash,sizeof_k,value,sizeof_v,index);
}

void* get(Map* map, void* key, int key_hash, size_t sizeof_k) {
	int n = map->tab_len;
	int index = key_hash & (n - 1);
	
	Entry* entry = get_entry(map, index, key, sizeof_k);
	if (entry != NULL) {
		return entry->value;
	}
	return NULL;
}

void remove(Map* map, void* key, int key_hash, size_t sizeof_k) {
	int n = map->tab_len;
	int index = key_hash & (n - 1);
	if (map->tab[index].header_entry != NULL) {
		Entry* header = map->tab[index].header_entry;
		Entry* entry;
		while ((entry=header->next) != NULL) {
			if (equal(key, entry->key, sizeof_k)) {
				header->next = entry->next;

				free(entry->key);
				free(entry->value);
				entry->next = NULL;
				free(entry);
				map->size--;
				break;
			}
			header = header->next;
		}
	}
}