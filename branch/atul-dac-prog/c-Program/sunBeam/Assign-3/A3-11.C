#include<stdio.h>
#include<conio.h>
void main()
{
	int  n, no;
	clrscr();
	printf("\nEnter the no : ");
	scanf("%d",&no);
	for(n=2; n<no; n++)
	{
		if(no%n==0)
			break;
	}
	if(no==n)
		printf("\nGiven no is Prime number ");
	else
		printf("\nGiven no is not a Prime number ");
	getch();
}
