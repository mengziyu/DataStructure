#pragma  warning (disable:4996) 
#include<stdio.h>
#include <string.h>
#include <stdlib.h>
#include"cstack.h"

#define SIZEOF_INT sizeof(int)
#define SIZEOF_DOUBLE sizeof(double)
#define SIZEOF_CHAR sizeof(char)
#define MID_EXP "9+(3-1)*3+10/2"
#define MID_EXP2 "(9+3)*3+10.5/2"
#define MID_EXP3 "9+3*(3+10.5)/2"
#define MID_EXP4 "3+1000.5/2*(9+3)"

int num_index = 0;
//后缀表达式栈
Stack* suffix_stack;
//运算符栈
Stack* op_stack;
//计算栈
Stack* cal_stack;


bool is_op(char c) {
	switch (c)
	{
	case '+':
	case '-':
	case '*':
	case '/':
	case '(':
	case ')':
		return true;
	default:
		break;
	}
	return false;
}

double calculate(double num1,double num2,char op) {
	switch (op)
	{
	case '+':
		return num2 + num1;
	case '-':
		return num2 - num1;
	case '*':
		return num2 * num1;
	case '/':
		return num2 / num1;
	default:
		break;
	}
	return 0;
}

void print_stack(Stack* stack) {
	if (stack->count == 0) {
		return;
	}
	Node* top = stack->top;
	int i = 0;
	for (; i < stack->count; i++) {
		char* cc = (char*)top->data;
		if (is_op(*cc)) {
			printf("%c", *cc);
		}
		else {
			printf("%g", *(double*)cc);
		}
		top = top->next;
	}
}

//把栈逆向
void reverse_stack(Stack* stack) {
	if (stack->count == 0) {
		return;
	}
	int len = stack->count;
	//用一个指针数组缓存数据
	char** tmp;
	tmp = (char**)malloc(sizeof(char*) * len);
	int i = 0;
	for (; i < len; i++) {
		tmp[i]= (char*)malloc(sizeof(char) * 20);
	}
	
	char* top = NULL;
	i = 0;
	while ((top = (char*)pop(stack)) != NULL) {
		tmp[i++] = top;
	}
	i = 0;
	for (; i <len; i++) {
		if (is_op(*tmp[i])) {
			push(stack,SIZEOF_CHAR,tmp[i]);
		}
		else {
			push(stack, SIZEOF_DOUBLE, tmp[i]);
		}
		free(tmp[i]);
	}
	free(tmp);

}

void push_suffix_op(char op) {
	push(suffix_stack, SIZEOF_CHAR, &op);
}


void pop_op_stack() {
	char* top_op = NULL;
	while ((top_op = (char*)pop(op_stack)) != NULL)
	{
		push(suffix_stack, SIZEOF_CHAR, top_op);
	}

}

void push_suffix_num(char* number) {
	if (number != NULL) {
		double val = atof(number);
		push(suffix_stack, SIZEOF_DOUBLE, &val);
		free(number);
		num_index = 0;
	}
}



int compare_op(char op1,char op2) {
	int result = 0;
	if (op2 == '+'|| op2 =='-') {
		switch (op1)
		{
		case '+':
			result = 0;
			break;
		case '-':
			result = 0;
			break;
		case '*':
			result = -1;
			break;
		case '/':
			result = -1;
			break;
		default:
			break;
		}
	}
	else if (op2 == '*'|| op2 =='/') {
		switch (op1)
		{
		case '+':
			result = 1;
			break;
		case '-':
			result = 1;
			break;
		case '*':
			result = 0;
			break;
		case '/':
			result = 0;
			break;
		default:
			break;
		}
	}

	return result;
}

//转成后缀表达式
void suffix_exp(char* exp) {
	int i = 0;
	int len = strlen(exp);
	
	char* top_op = NULL;
	char* number=NULL;
	for (; i < len; i++) {
		
		switch (exp[i])
		{
		case ' ':
			break;
		case '+':
		case '-':
			push_suffix_num(number);
			number = NULL;

			//比较当前符号和栈顶符号优先级
			top_op = (char*)peek(op_stack);
			if (top_op != NULL && compare_op(*top_op, exp[i]) < 0) {
				top_op = (char*)pop(op_stack);
				push(suffix_stack, SIZEOF_CHAR, top_op);
			}
			push(op_stack, SIZEOF_CHAR, &exp[i]);
			break;
		case '*':
		case '/':
			push_suffix_num(number);
			number = NULL;
			push(op_stack, SIZEOF_CHAR, &exp[i]);
			break;
		case '(':
			push(op_stack, SIZEOF_CHAR, &exp[i]);
			break;
		case ')':
			push_suffix_num(number);
			number = NULL;

			top_op = NULL;
			while ((top_op =(char*)pop(op_stack))!=NULL)
			{
				if (*top_op == '(') {
					break;
				}
				else {
					push(suffix_stack, SIZEOF_CHAR, top_op);
				}
			}
			if (i == len - 1) {
				pop_op_stack();
			}
			break;
		default:
			if (!number) {
				number = (char*)malloc(sizeof(char)*20);
			}
			number[num_index++] = exp[i];
			if (i == len - 1) {
				push_suffix_num(number);
				number = NULL;
				pop_op_stack();
			}
			break;
		}
	}
}


void cal_exp() {
	Stack tmp;
	char* top = NULL;
	while ((top = (char*)pop(suffix_stack)) != NULL) {
		if (is_op(*top)) {
			double n1 = *(double*)pop(&tmp);
			double n2 = *(double*)pop(&tmp);
			double result = calculate(n1,n2,*top);
			push(&tmp, SIZEOF_DOUBLE, &result);
		}
		else {
			push(&tmp, SIZEOF_DOUBLE,top);
		}
	}
	double result = *(double*)pop(&tmp);
	printf("result:%g\n",result);
}


void main() {
	
	char* exp = (char*)MID_EXP4;
	Stack stack1;
	Stack stack2;
	Stack stack3;
	suffix_stack = &stack1;
	op_stack = &stack2;
	cal_stack = &stack3;
	
	printf("表达式:%s\n", exp);
	suffix_exp(exp);
	printf("\n=========后缀表达式========\n");
	reverse_stack(suffix_stack);
	print_stack(suffix_stack);
	printf("\n\n=========计算结果========\n");
	cal_exp();

	release(cal_stack);
	release(suffix_stack);
	release(op_stack);
}