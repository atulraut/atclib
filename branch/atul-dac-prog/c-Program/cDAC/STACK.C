/*IN THIS PROG. WE WRITE THE FUNCTION OF STACK LIKE POP-UP, PUSH, PEEP,
 DUPLICATE, DISPLAY, AND CLEAR THE STACK*/

#include<stdio.h>
#include<conio.h>
#define MAX 6
int stack[MAX],top=-1;

void push(int val)
{
	if(top==MAX)
	{
		printf("the stack is full");
		getch();
	}
	else
	{
		stack[++top]=val;
	}
}

int pop()
{
	int val;
	if(top==-1)
	{
		printf("\nthe stack is empty\n");
		getch();
	}
	else
	{
		val=stack[top--];
		return val;
	}
}
void peep()
{
	int val;
	if(top==-1)
	{
		printf("\nthe stack is empty\n");
		getch();
	}
	else
	{
		val=stack[top--];
		printf("\nThe peep item/number is %d",val);
	}
}
void duplicate()
{
	int val;
	if(-1<top && top<MAX-1)
	{
		val=stack[top];
		stack[++top]=val;
	}
	else
		printf("\nduplicate is not created\n");
}
void swap()
{
	 int val;
	if(top==-1)
		printf("\nswaping is not posible\n");
	else
	{
		val=stack[top];
		stack[top]=stack[top-1];
		stack[top-1]=val;
	}
}
void display()
{
	int val;
	printf("\n");
	if(top==-1)
	{
		printf("\nthe stack is empty\n");
		getch();
		return;
	}
	else
	{
		while(top!=-1)
		{
			val=stack[top--];
			printf("\t%d",val);
		}
	}
}
void clear()
{
	if(top==-1)
	{
		printf("\nthe stack is empty\n");
		getch();
		return;
	}
	else
	{
		while(top!=-1)
		{
			stack[top--]=0;
		}
	}
}



void main()
{
	int val,ch;
	clrscr();
	do
	{
		printf("\n1> push\n2> pop\n3> peep\n4> duplicate\n5> swap\
		\n6> display\n7> clear\n0> exit");
		printf("\nplease enter the choice");
		scanf("%d",&ch);
		switch(ch)
		{
			case 0:/*----EXIT----*/
				exit();
			case 1:/*----push----*/
				printf("\nplease enter the number\n");
				scanf("%d",&val);
				push(val);
				break;
			case 2:/*----POP----*/
				val=pop();
				printf("\nThe pop-up item/number is %d",val);
				break;
			case 3:/*----peep----*/
				peep();
				break;
			case 4:/*----DUPLICATE----*/
				duplicate();
				break;
			case 5:/*----swap----*/
				swap();
				break;
			case 6:/*----DISPLAY----*/
				display();
				break;
			case 7:/*----CLEAR-----*/
				clear();
				break;
		}
	}while(ch!=0);
getch();
}
