#include <stdio.h>
#include <setjmp.h>

jmp_buf buf;

#define MAX 2

typedef struct stack
{
	int arr[MAX];
	int top;
}STACK;

void push(STACK *p, int val)
{
	if(p->top==MAX-1)
	{
		printf("\nStack is full");
	}
	else
	{
		p->top++;
		p->arr[p->top]=val;
	}
}
int pop(STACK *p)
{
	int val=0;
	if(p->top==-1)
	{
		longjmp(buf, 1);
	}
	else
	{
		val = p->arr[p->top];
		p->top--;
	}
	return val;
}
int topele(STACK *p)
{
	return p->arr[p->top];
}
int isEmpty(STACK *p)
{
	if(p->top==-1)
		return 1;
	else
		return 0;
}
int isFull(STACK *p)
{
	if(p->top==MAX-1)
		return 1;
	else
		return 0;
}

void init(STACK *p)
{
	p->top = -1;
}
void main()
{
	STACK s;
	int val;
	init(&s);
	push(&s, 10);
	printf("\nValue inserted = 10\n");
	push(&s, 20);
	printf("\nValue inserted = 20\n");

	if(setjmp(buf)==0)
	{
		val = pop(&s);
		printf("\nValue Removed = %d\n", val);
		val = pop(&s);
		printf("\nValue Removed = %d\n", val);

		val = pop(&s);
		printf("\nValue Removed = %d\n", val);
	}
	else
	{
		printf("\nStack is Empty\n");
	}
}