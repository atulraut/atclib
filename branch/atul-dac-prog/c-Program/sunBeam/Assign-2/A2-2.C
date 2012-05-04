#include<stdio.h>
#include<conio.h>
void main()
{
	int n, a, b, c, d,sum,temp;
	clrscr();
	printf("\n Pls Enter no 4 digit:");
	scanf("%4d",&n);
	temp = n;
	printf("\nYou have Entered = %d\n",n);
	a = n/1000;
	n = n%1000;
	b = n/100;
	n = n%100;
	c = n/10;
	d = n%10;
	sum = (d*1000) + (c*100) + (b*10) + a;
	printf("\nReverse of number is : %d \n",sum);
	if(temp==sum)
		printf("\nReverse of number is same");
	else
		printf("\nReverse of number is not same");
	getch();
}