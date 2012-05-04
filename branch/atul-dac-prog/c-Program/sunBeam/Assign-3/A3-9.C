#include<stdio.h>
#include<conio.h>
void main()
{
	int temp,no,a,b,c;
	clrscr();
	printf("\nEnter the number :");
	scanf("%d",&no);
	temp = no;
	a=no/100;
	no=no%100;
	b=no/10;
	c=no%10;
	if(temp == ((a*a*a) + (b*b*b) + (c*c*c)))
		printf("\n %d = %d*%d*%d +%d*%d*%d + %d*%d*%d ",temp,a,a,a,b,b,b,c,c,c);
	else
		printf("\nEntered no is not armstrong no ");
	getch();
}
