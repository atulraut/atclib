#include<stdio.h>
#include<conio.h>
void main()
{
	int no,i;
	clrscr();
        printf("\nEnter the number : ");
	scanf("%d",&no);
	while(no<0)
	{
		clrscr();
		printf("\nPlease enter positive number : ");
		scanf("%d",&no);
	}
	for(i=2;i<no;i++)
	{
		if(no%i==0)
			break;
	}
	if(no==i)
		printf("\nPrime Number ");
	else
		printf("\nNot a Prime Number ");
	getch();
}