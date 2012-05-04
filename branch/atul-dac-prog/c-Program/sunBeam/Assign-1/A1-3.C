#include<stdio.h>
#include<conio.h>
void main()
{
	int n, a, b, c, d,temp;
	clrscr();
	printf("\n Pls Enter no 4 digit:");
	scanf("%4d",&n);
	temp = n;
	a = n/1000;
	n = n%1000;
	b = n/100;
	n = n%100;
	c = n/10;
	d = n%10;
	printf("\n%d = %d + %d + %d + %d",temp,(a*1000),(b*100),(c*10),d);
	getch();
}