#pragma  warning (disable:4996) 
#include<stdio.h>
#include"clist.h"

#define COUNT 12

struct Student
{
	char name[20];
	int age;
	int score;
};

void main() {
	int sizeof_int = sizeof(int);
	List m_list = create_list(sizeof_int);
	//add
	printf("======add======\n");
	int i = 0;
	for (; i < COUNT; i++) {
		int d = i * 10;
		add(&m_list,sizeof_int,&d);
	}
	printf("count:%d\n",m_list.count);

	i = 0;
	int* p_data = (int*)m_list.data;
	for (; i < m_list.count; i++) {
		printf("value%d: \t%d\n", i,*(p_data++));
	}
	//remove
	printf("======remove======\n");
	remove(&m_list,sizeof_int,1);
	remove(&m_list,sizeof_int,1);
	printf("count:%d\n", m_list.count);
	i = 0;
	int* p_data2 = (int*)m_list.data;
	for (; i < m_list.count; i++) {
		printf("value%d: \t%d\n", i, *(p_data2++));
	}

	//set 
	printf("======set======\n");
	int value = 1000;
	set(&m_list, sizeof_int, 1,&value);
	i = 0;
	int* p_data3 = (int*)m_list.data;
	for (; i < m_list.count; i++) {
		printf("value%d: \t%d\n", i, *(p_data3++));
	}
	//get
	printf("======get======\n");
	int index = 2;
	int* val = (int*)get(&m_list, sizeof_int,index);
	printf("value%d: \t%d\n", index, *(val));

	////////////////////////////////////////////////////////////////////////////////////

	printf("\n\n======Student list======\n");
	int sizeof_student = sizeof(Student);
	List stus = create_list2(sizeof_student,COUNT);

	//add
	printf("======add======\n");
	i = 0;
	for (; i < COUNT; i++) {
		Student stu;
		char n[4];
		itoa(i, n, 10);
		char tmp[10] = "stu";
		strcat(tmp,n);
		strcpy(stu.name, tmp);
		stu.age = 18 + i;
		stu.score = 60 + i;
		add(&stus, sizeof_student, &stu);
	}
	printf("count:%d\n", stus.count);

	i = 0;
	Student* stu_data = (Student*)stus.data;
	for (; i < stus.count; i++) {
		printf("value%d: \t%s\t%d\t%d\n", i, stu_data->name,stu_data->age,stu_data->score);
		stu_data++;
	}
	//remove
	printf("======remove======\n");
	remove(&stus, sizeof_student, 1);
	remove(&stus, sizeof_student, 1);
	printf("count:%d\n", stus.count);
	i = 0;
	Student* stu_data2 = (Student*)stus.data;
	for (; i < stus.count; i++) {
		printf("value%d: \t%s\t%d\t%d\n", i, stu_data2->name, stu_data2->age, stu_data2->score);
		stu_data2++;
	}

	//set 
	printf("======set======\n");
	Student stu;
	strcpy(stu.name, "setname");
	stu.age = 100;
	stu.score = 100;
	set(&stus, sizeof_student, 1, &stu);
	i = 0;
	Student* stu_data3 = (Student*)stus.data;
	for (; i < stus.count; i++) {
		printf("value%d: \t%s\t%d\t%d\n", i, stu_data3->name, stu_data3->age, stu_data3->score);
		stu_data3++;
	}

	//get
	printf("======get======\n");
	index = 2;
	Student* stu_val = (Student*)get(&stus, sizeof_student, index);
	printf("value%d: \t%s\t%d\t%d\n", index, stu_val->name, stu_val->age, stu_val->score);


	//indexof
	Student* stu_data4 = (Student*)stus.data;
	printf("======indexof======\n");
	printf("indexof:%d",indexof(&stus,sizeof_student, stu_data4+2));

	release(&stus);
	release(&m_list);
}




