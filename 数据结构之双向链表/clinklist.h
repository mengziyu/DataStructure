#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


struct Node
{
	void* data;
	Node* prev=NULL;
	Node* next=NULL;
};

struct LinkList
{
	Node* first=NULL;
	Node* last=NULL;
	int count = 0;
};

void release(LinkList* list) {
	if (list != NULL) {
		
		while (list->first !=NULL)
		{
			Node* tmp_first = list->first;
			list->first = list->first->next;
			free(tmp_first);
			tmp_first = NULL;
		}
		list->first = NULL;
		list->last = NULL;
		list->count = 0;
	}
}

bool add_last(LinkList* list, size_t sizeof_t,void* v) {
	Node* tmp_last = list->last;

	Node* new_node=(Node*)malloc(sizeof(Node));
	new_node->data = malloc(sizeof_t);
	char* tmp_data = (char*)new_node->data;
	char* tmp_val = (char*)v;
	//复制每个字节数据
	int i = 0;
	for (; i < sizeof_t; i++) {
		*(tmp_data + i) = *(tmp_val + i);
	}
	new_node->prev = tmp_last;
	new_node->next = NULL;

	list->last = new_node;
	//第一次添加时tmp_last=NULL
	if (tmp_last == NULL) {
		list->first = new_node;
	}
	else {
		tmp_last->next = new_node;
	}
	list->count++;
	return true;
}

bool add_first(LinkList* list, size_t sizeof_t,void* v) {
	Node* tmp_first = list->first;

	Node* new_node = (Node*)malloc(sizeof(Node));
	new_node->data = malloc(sizeof_t);
	char* tmp_data = (char*)new_node->data;
	char* tmp_val = (char*)v;
	//复制每个字节数据
	int i = 0;
	for (; i < sizeof_t; i++) {
		*(tmp_data + i) = *(tmp_val + i);
	}

	new_node->prev = NULL;
	new_node->next = tmp_first;

	list->first = new_node;
	if (tmp_first == NULL) {
		list->last = new_node;
	}
	else {
		tmp_first->prev = new_node;
	}
	list->count++;
	return true;
}


bool add(LinkList* list, size_t sizeof_t,void* v) {
	return add_last(list, sizeof_t,v);
}

/*
	返回索引是index的节点
*/
Node* node_index(LinkList* list,int index){
	int mid = (list->count) >> 1;
	if (index < mid) {
		Node* tmp_first = NULL;
		int i = 0;
		for (; i <= index; i++) {
			if (tmp_first == NULL) {
				tmp_first = list->first;
			}
			else {
				tmp_first = tmp_first->next;
			}
		}
		return tmp_first;
	}
	else {
		Node* tmp_last = NULL;
		int i = list->count-1;
		for (; i >= index; i--) {
			if (tmp_last == NULL) {
				tmp_last = list->last;
			}
			else {
				tmp_last = tmp_last->prev;
			}
		}
		return tmp_last;
	}
}

bool add_index(LinkList* list, size_t sizeof_t,int index, void* v) {
	if (index <= 0) {
		return add_first(list, sizeof_t, v);
	}
	else if (index >= list->count) {
		return add_last(list, sizeof_t,v);
	}
	else {
		Node* in_node = node_index(list, index);

		Node* new_node = (Node*)malloc(sizeof(Node));
		new_node->data = malloc(sizeof_t);
		char* tmp_data = (char*)new_node->data;
		char* tmp_val = (char*)v;
		//复制每个字节数据
		int i = 0;
		for (; i < sizeof_t; i++) {
			*(tmp_data + i) = *(tmp_val + i);
		}
		
		//把新节点添加到该节点前面
		in_node->prev->next = new_node;
		new_node->prev = in_node->prev;
		new_node->next = in_node;
		in_node->prev = new_node;

		list->count++;
	}
	return true;
}

bool remove_first(LinkList* list) {
	Node* tmp_first = list->first;
	list->first = list->first->next;
	free(tmp_first);
	list->first->prev = NULL;
	tmp_first = NULL;
	return true;
}

bool remove_last(LinkList* list) {
	Node* tmp_last = list->last;
	list->last = list->last->prev;
	free(tmp_last);
	list->last->next = NULL;
	tmp_last = NULL;
	return true;
}

bool remove(LinkList* list,int index) {
	if (index <= 0) {
		return remove_first(list);
	}
	else if (index >= list->count) {
		return remove_last(list);
	}
	else {
		Node* in_node = node_index(list,index);
		in_node->prev->next = in_node->next;
		in_node->next->prev = in_node->prev;
		free(in_node);
	}
	list->count--;
	return true;
}


bool set(LinkList* list, int index, void* v) {
	Node* in_node = node_index(list, index);
	in_node->data = v;
	return true;
}

void* get(LinkList* list, int index) {
	return node_index(list, index)->data;
}



