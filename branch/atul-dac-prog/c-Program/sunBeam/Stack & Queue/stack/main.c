#include<stdio.h>
#include<stdlib.h>

#define MAX 5

int stack[MAX];
int top = -1;

void push(int val)
{
	if(top == MAX-1)
		printf("\nStack is full \n");
	else
	{
		top++;
		stack[ top] = val;
	}
}

int pop()
{
	int val;
	if(top == -1)
		return -1;
	else
	{
		val = stack[top];
		top--;
		return val;
	}
}

int topele()
{
	return stack[top];
}

void isempty()
{
	if(top == -1)
		printf("\nStack is empty \n");
	else
		printf("\nStack is not empty \n");
}

void main()
{
	int a;
	push(10);
	printf("\nValue inserted = 10");
	push(20);
	printf("\nValue inserted = 20");
	push(30);
	printf("\nValue inserted = 30");
	a = pop();
	printf("\nThe poped element is %d \n",a);
	isempty();
	a = pop();
	printf("\nThe poped element is %d \n",a);
	a = topele();
	printf("\nTop element is %d \n",a);
	a = pop();
	printf("\nThe poped element is %d \n",a);
	isempty();
	a = pop();
	printf("\nThe poped element is %d \n",a);
}
