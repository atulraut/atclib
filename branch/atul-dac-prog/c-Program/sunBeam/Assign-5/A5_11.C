#include<stdio.h>
#include<conio.h>
void main()
{
	unsigned int n;
	int i, bin[16];
	clrscr();
	printf("\nEnter the number :");
	scanf("%u",&n);
	for(i=15; i>=0; i--)
	{
		bin[i] = n%2;
		n = n/2;
	}
	for(i=0; i<=15; i++)
		printf("%d ",bin[i]);
	getch();
}
