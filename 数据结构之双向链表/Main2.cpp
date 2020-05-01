#pragma  warning (disable:4996) 
#include<stdio.h>
#include"clinklist.h"

#define COUNT 12

struct Student
{
	char name[20];
	int age;
	int score;
};

void print_list(LinkList list) {
	Node* tmp_node = list.first;
	int i = 0;
	while (tmp_node != NULL)
	{
		Student* stu = (Student*)tmp_node->data;
		printf("stu%d: \t%s\t%d\t%d\n", i++, stu->name, stu->age, stu->score);
		tmp_node = tmp_node->next;
	}
}

void main() {
	int sizeof_stu = sizeof(Student);
	LinkList link_list;

	//add
	printf("======add======\n");
	int i = 0;
	for (; i < COUNT; i++) {
		Student* stu = (Student*)malloc(sizeof_stu);
		char n[4];
		itoa(i, n, 10);
		char tmp[10] = "stu";
		strcat(tmp, n);
		strcpy(stu->name, tmp);
		stu->age = 18 + i;
		stu->score = 60 + i;
		add(&link_list,sizeof_stu, stu);
		//add_first(&link_list, sizeof_stu, stu);
	}
	//add index
	Student* new_stu = (Student*)malloc(sizeof_stu);
	strcpy(new_stu->name, "new_name");
	new_stu->age = 100;
	new_stu->score = 100;
	add_index(&link_list, sizeof_stu,2 , new_stu);
	printf("count:%d\n", link_list.count);

	print_list(link_list);

	//remove
	printf("======remove======\n");
	remove(&link_list,9);
	print_list(link_list);


	//set
	printf("======set======\n");
	Student* new_stu2 = (Student*)malloc(sizeof_stu);
	strcpy(new_stu2->name, "set_name");
	new_stu2->age = 110;
	new_stu2->score = 110;
	set(&link_list,1,new_stu2);
	print_list(link_list);

	//get
	printf("======get======\n");
	Student* get_stu = (Student*)get(&link_list,1);
	printf("get stu: \t%s\t%d\t%d\n", get_stu->name, get_stu->age, get_stu->score);

	release(&link_list);
}