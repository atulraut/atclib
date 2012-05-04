#include<stdio.h>
#include<conio.h>
void fibo(int);
void main()
{
	int no;
	clrscr();
	printf("\nEnter the number : ");
	scanf("%d",&no);
	fibo(no);
	getch();
}
void fibo(int n)
{
	int i,a=0,b=1,c;
	printf("1  ");
	for(i=1;i<n;i++)
	{
		c = a + b;
		printf("%d  ",c);
		a = b;
		b = c;
	}
}