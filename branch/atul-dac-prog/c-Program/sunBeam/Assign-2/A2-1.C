#include<stdio.h>
#include<conio.h>
void main()
{
	int a, b, max;
	clrscr();
	printf("\nEnter two no a and b :");
	scanf("%d %d",&a,&b);
	if(a>b)
		printf("\nThe Max No. is =%d",a);
	else
		printf("\nThe Max No. is =%d",b);
	getch();
}
