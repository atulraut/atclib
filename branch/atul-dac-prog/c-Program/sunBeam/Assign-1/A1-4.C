#include<stdio.h>
#include<conio.h>
void main()
{
	int n, a, b, c, d,sum;
	clrscr();
	printf("\n Pls Enter no 4 digit:");
	scanf("%4d",&n);
	printf("\nYou have Entered = %d\n",n);
	a = n/1000;
	n = n%1000;
	b = n/100;
	n = n%100;
	c = n/10;
	d = n%10;
	printf("\nReverse is: %d%d%d%d",d,c,b,a);
	getch();
}