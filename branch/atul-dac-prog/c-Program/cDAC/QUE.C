#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
typedef struct que
{
	int arr[80];
	int rear,front;
}que;
void insert(que *p,int val)
{
	if(p->rear>=6)
	printf("que is full");
	else
	{
		p->arr[p->rear]=val;
		p->rear++;
	}
}
int remov(que *p)
{
	int val=0;
	if(p->front==p->rear)
	printf("\n que is empty");
	else
	{
		val=p->arr[p->front];
		p->front++;
	}
	return val;
}
void display(que *p)
{
	while(p->front!=p->rear)
	{
		printf("\t%d",p->arr[p->front]);
		p->front++;
	}
	p->front=0;
}
void main()
{
	que q;
        int ch,val;
	q.rear=0;
	q.front=0;
	clrscr();
	while(1)
	{
		printf("\n 1->insert");
		printf("\n 2->display");
		printf("\n 3->remove");
		printf("\n 0->exit");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1:
				printf("\nenter the value to b insert");
				scanf("%d",&val);
				insert(&q,val);
				break;
			case 2:
				display(&q);
				break;
			case 3:
				val=remov(&q);
				printf("\n data retrieved is %d",val);
				break;
			case 0:
				exit(0);
		}
	}
	getch();
}