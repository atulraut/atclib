#include<stdio.h>
#include<stdlib.h>

#define MAX 5

int queue[MAX];
int front ,rear;
front = -1;
rear = -1;

void insert(int val)
{
	if((front == -1 && rear ==MAX-1) || (rear == front && rear != -1))
		printf("\nQueue is full \n");
	else
	{
		if(rear == MAX-1)
			rear = -1;
		else
		{
			rear++;
			queue[rear] = val;
		}
	}
}

int removeq()
{
	int val;
	if(front == rear)
		front = rear = -1;
	if(rear == front && front == -1)
		printf("\nQueue is empty \n");
	else
	{
		if(front ==MAX-1)
			front = 0;
		else
		{
			front++;
			val = queue[front];
			return val;
		}
	}
	return 0;
}

void main()
{
	int val;
	insert(10);
	printf("\nValue inserted is 10 \n");
	insert(20);
	printf("\nValue inserted is 20 \n");
	insert(30);
	printf("\nValue inserted is 30 \n");
	insert(40);
	printf("\nValue inserted is 40 \n");
	val = removeq();
	printf("\nValue removed is %d \n",val);
	val = removeq();
	printf("\nValue removed is %d \n",val);
	val = removeq();
	printf("\nValue removed is %d \n",val);
	val = removeq();
	printf("\nValue removed is %d \n",val);
}