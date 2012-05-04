#include<stdio.h>
#include<conio.h>
int fact(int );
void main()
{
	int i, n,a,b,c;
	printf("Strong Number between (1-500) are :");
	for(i=1;i<=500;i++)		
	{
		a = i/100;
		n = i%100;
		b = n/10;
		c = n%10;
		if(i == fact(a) + fact(b) + fact(c))
			printf("\n%d = factorial(%d) + factorial(%d) + factorial(%d)\n",i,a,b,c);
	}
}
