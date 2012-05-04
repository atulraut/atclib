#include<stdio.h>
#include<conio.h>
void main()
{
	long int n,m=1,a;
	int i,sum=0,j;
	clrscr();
	printf("\nEnter the number : ");
	scanf("%ld",&n);
	for(i=10;i>0;i--)
	{
		for(j=0;j<i;j++)
			m = m * 10;
		a = n/m;
		sum = sum + a;
		n = n%m;
		m = 1;
	}
	sum = sum + n;
	printf("\nSum is : %d ",sum);
	getch();
}