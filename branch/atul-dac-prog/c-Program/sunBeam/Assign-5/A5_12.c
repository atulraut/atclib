#include<stdio.h>
#include<conio.h>
void funct(int,int,int*,int*);
void main()
{
	int a,b,sum,prod;
	printf("\nEnter the value of a and b : ");
	scanf("%d%d",&a,&b);
	funct(a,b,&sum,&prod);
	printf("Sum = %d and Product = %d \n",sum,prod);
}
void funct(int a,int b,int *ps,int *pp)
{
	*ps = a + b;
	*pp = a * b;
}