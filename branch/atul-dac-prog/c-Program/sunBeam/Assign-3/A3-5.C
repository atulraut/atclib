#include<stdio.h>
#include<conio.h>
void main()
{
	int i, n, prime[100],j=0;
	clrscr();
	printf("\nThe prime no are (1-100):\n");
	for(i=0; i<=100; i++)
	{
		for(n=2; n<i; n++)
		{
			if(i%n==0)
				break;
		}
		if(i==n)
		{
			prime[j] = i;
			j++;
		}
	}
	for(i=0;i<j;i++)
		printf("  %d",prime[i]);
	printf("\nTwin Prime Numbers are :\n");
	for(i=0;i<j;i++)
	{
		if(prime[i+1] - prime[i] == 2)
			printf("\n%2d - %2d ",prime[i],prime[i+1]);
	}
	getch();
}
