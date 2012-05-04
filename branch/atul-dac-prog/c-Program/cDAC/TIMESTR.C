#include<stdio.h>
#include<conio.h>
void main()
{
	typedef struct time
	{
		int hrs,min,sec;

	}TIME;
	TIME *t;
	clrscr();
	printf("please enyer the time in hrs,min,and sec.");
	scanf("%d%d%d",&t->hrs,&t->min,&t->sec);

	printf("%d:%d:%d",t->hrs,t->min,t->sec);
getch();
}
