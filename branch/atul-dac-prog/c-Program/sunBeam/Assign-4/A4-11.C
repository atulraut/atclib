#include<stdio.h>
#include<conio.h>
void main()
{
	char ch;
	int i, j;
	clrscr();
	for(i=4; i>=1; i--)
	{
		ch = 'A';
		printf("\n");
		for(j=i; j>=1; j--)
		{
			printf("%c ",ch);
			ch++;
		}
		ch--;
		for(j=(4-i);j>0;j--)
			printf("    ");
		for(j=1;j<=i;j++)
		{
			printf("%c ",ch);
			ch--;
		}
	}
	getch();
}