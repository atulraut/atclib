#include<stdio.h>
#include<conio.h>
void main()
{
	int i, j, ch;
	clrscr();
	printf("\nEnter the no :");
	scanf("%d",&ch);
	for(i=1; i<=10; i++)
		printf("\n%d * %d = %d",ch,i,(ch*i));
	getch();
}