#include<stdio.h>
#include<conio.h>
void main()
{
	long int n,a;
	int i,j;
	clrscr();
	printf("\nEnter the number : ");
	scanf("%ld",&n);
	for(i=10;i>0;i--)
	{
		a = n%10;
		if(a==0)
		{
			n = n/10;
			continue;
		}
		else
			printf("%d",a);
		n = n/10;
	}
	getch();
}