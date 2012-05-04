#include<stdio.h>
#include<conio.h>
void main()
{
	int i, n,a,b,c;
	clrscr();
	printf("\nAmstrong No (1-500) Given Below :");
	for(i=1; i<=500; i++)
	{
		n = i;
		a=n/100;
		n=n%100;
		b=n/10;
		c=n%10;
		if(i == ((a*a*a) + (b*b*b) + (c*c*c)))
			printf("\n %d = %d*%d*%d +%d*%d*%d + %d*%d*%d ",i,a,a,a,b,b,b,c,c,c);
	}
	getch();
}
