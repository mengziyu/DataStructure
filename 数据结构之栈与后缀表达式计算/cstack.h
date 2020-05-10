#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


struct Node
{
	void* data;
	Node* next=NULL;
};

struct Stack
{
	Node* top = NULL;
	int count = 0;
};

void copy_data2(void* dst, void* src, size_t sizeof_t) {
	char* tmp_dst = (char*)dst;
	char* tmp_src = (char*)src;
	//复制每个字节数据
	int i = 0;
	for (; i < sizeof_t; i++) {
		*(tmp_dst + i) = *(tmp_src + i);
	}
}

void release(Stack* stack) {

	while (stack->top != NULL) {
		Node* tmp_top = stack->top;
		stack->top = tmp_top->next;
		free(tmp_top);
		tmp_top = NULL;
	}
}

void* peek(Stack* stack) {
	if (stack->count == 0) {
		//printf("stack is empty\n");
		return NULL;
	}
	return stack->top->data;
}

void* pop(Stack* stack) {
	if (stack->count == 0) {
		//printf("stack is empty\n");
		return NULL;
	}
	Node* tmp_top = stack->top;
	stack->top = stack->top->next;
	tmp_top->next = NULL;
	stack->count--;
	return tmp_top->data;
}

bool push(Stack* stack,size_t sizeof_t,void* v) {
	Node* new_node = (Node*)malloc(sizeof(Node));
	new_node->data = malloc(sizeof_t);
	copy_data2(new_node->data,v,sizeof_t);
	new_node->next = stack->top;
	stack->top = new_node;
	stack->count++;
	return true;
}
