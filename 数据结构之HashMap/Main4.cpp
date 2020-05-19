#pragma  warning (disable:4996) 
#include<stdio.h>
#include <string.h>
#include <stdlib.h>
#include"cmap.h"


char* build_name(const char* name, int i) {
	char n[10];
	itoa(i, n, 10);
	int len = strlen(name);
	char* new_name = (char*)malloc(len);
	strcpy(new_name, name);
	strcat(new_name, n);
	return new_name;
}

struct Student
{
	char* name;
	int score;
	int age;
};

void main()
{
	Map map;
	printf("==========put=========\n");
	int i = 0;
	for (; i < 25; i++)
	{
		char* key = build_name("name",i);
		int score = i * 10;
		printf("%s:\t%d\n",key,score);
		put(&map, key, get_hash(key), sizeof(key), &score, sizeof(int));
	}

	printf("==========修改和查询=========\n");
	char* n=build_name("name",1);
	int score = 99;
	put(&map, n, get_hash(n), sizeof(n), &score, sizeof(int));
	int* sc = (int*)get(&map,n,get_hash(n),sizeof(n));
	printf("%s:\t%d\n",n,*sc);

	printf("==========删除=========\n");
	char* remove_name = build_name("name", 3);
	printf("rmove %s\n", remove_name);
	remove(&map, remove_name, get_hash(remove_name), sizeof(remove_name));

	printf("==========遍历=========\n");
	Itr itr = get_itr(&map);
	while (itr.has_next(&map,&itr)) {
		char* key = (char*)(itr.entry->key);
		int* sc = (int*)(itr.entry->value);
		printf("%s:\t%d\n",key,*sc);
	}


	printf("==========put Student=========\n");
	Map stu_map;
	i = 0;
	for (; i < 17; i++) {
		Student stu;
		stu.name = build_name("stu",i);
		stu.score = i + 10;
		stu.age = i;
		put(&stu_map,stu.name,get_hash(stu.name),sizeof(stu.name),&stu,sizeof(stu));
	}

	printf("==========遍历Student=========\n");
	Itr stu_itr = get_itr(&stu_map);
	while (stu_itr.has_next(&stu_map, &stu_itr)) {
		char* key = (char*)(stu_itr.entry->key);
		Student* sc = (Student*)(stu_itr.entry->value);
		printf("%s:\t%d\t%d\n", key, sc->age,sc->score);
	}

	release(&map);
	release(&stu_map);
}