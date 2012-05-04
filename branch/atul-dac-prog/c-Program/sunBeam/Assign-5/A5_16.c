#include<stdio.h>
#include<conio.h>
int gcd(int ,int );
void main()
{
	int a,b,n;
	printf("\nEnter the numbers : ");
	scanf("%d%d",&a,&b);
	n = gcd(a,b);
	printf("\nGCD of %d and %d is : %d \n",a,b,n);
}

