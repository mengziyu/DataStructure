#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define DEFAULT_SIZE 10


struct List
{
	void* data;
	//数据大小
	int count = 0;
	//数据容量
	int capacity = 0;
};

void release(List* list) {
	if (list->data != NULL) {
		free(list->data);
		list->data = NULL;
	}
	list->count = 0;
	list->capacity = 0;
}

List create_list(size_t sizeof_t) {
	List list;
	list.data = malloc(sizeof_t*DEFAULT_SIZE);
	list.capacity = DEFAULT_SIZE;
	return list;
}

List create_list2(size_t sizeof_t,int len) {
	List list;
	list.data = malloc(sizeof_t * len);
	list.capacity = len;
	return list;
}


static void grow(List* list, size_t sizeof_t,int len) {
	void* new_data = realloc(list->data, sizeof_t * len);
	list->data = new_data;
	list->capacity = len;
}

bool add(List* list, size_t sizeof_t,void* v) {
	if (list->data != NULL) {
		if (list->count >= list->capacity) {
			grow(list,sizeof_t,list->count+DEFAULT_SIZE);
		}
		char* tmp_data = (char*)list->data;
		//地址偏移
		tmp_data += list->count * sizeof_t;
		char* tmp_val = (char*)v;
		//复制每个字节数据
		int i = 0;
		for (; i < sizeof_t; i++) {
			*(tmp_data +i) = *(tmp_val+i);
		}
		
		list->count++;
		return true;
	}
	return false;
}


int indexof(List* list, size_t sizeof_t, void* v) {
	char* tmp_data = (char*)list->data;
	char* tmp_val = (char*)v;
	int i = 0;
	for (; i < list->count*sizeof_t; i+=sizeof_t) {
		if ((tmp_data + i) == (tmp_val)) {
			return i / sizeof_t;
		}
	}
	return -1;
}

bool remove(List* list, size_t sizeof_t, int index) {
	if (index < 0 || index >= list->count) {
		printf("invalid index\n");
		return false;
	}
	char* tmp_data = (char*)list->data;
	//拷贝数据到新内存
	char* new_data = (char*)malloc(sizeof_t * (list->count - 1));

	int i = 0;
	int np = 0;
	if (index == 0) {
		i = sizeof_t;
		for (; i < list->count * sizeof_t;i++) {
			*(new_data + (np++)) = *(tmp_data+i);
		}
	}
	else if (index == list->count - 1) {
		for (; (i < list->count-1) * sizeof_t; i++) {
			*(new_data + (np++)) = *(tmp_data + i);
		}
	}
	else{
		for (; i < index * sizeof_t; i++) {
			*(new_data + (np++)) = *(tmp_data + i);
		}
		i = sizeof_t * (index+1);
		for (; i < list->count * sizeof_t; i++) {
			*(new_data + (np++)) = *(tmp_data + i);
		}
	}
	
	free(list->data);
	//指向新地址
	list->data = new_data;
	new_data = NULL;
	list->count--;
	return true;
}

bool set(List* list, size_t sizeof_t, int index, void* v) {
	if (index < 0 || index >= list->count) {
		printf("invalid index\n");
		return false;
	}
	char* tmp_data = (char*)list->data;
	tmp_data += sizeof_t*index;
	char* tmp_val = (char*)v;

	int i = 0;
	for (; i < sizeof_t; i++) {
		*(tmp_data + i) = *(tmp_val + i);
	}
	return true;
}

void* get(List* list, size_t sizeof_t, int index) {
	if (index < 0 || index >= list->count) {
		printf("invalid index\n");
		return NULL;
	}
	char* tmp_data = (char*)list->data;
	tmp_data += sizeof_t * index;

	return tmp_data;
}