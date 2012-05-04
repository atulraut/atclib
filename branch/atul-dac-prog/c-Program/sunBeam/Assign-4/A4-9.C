#include<stdio.h>
#include<conio.h>
void main()
{
	int i,j,a=4,n;
	clrscr();
	printf("\nEnter the number : ");
	scanf("%d",&n);
	a = n;
	for(i=1;i<=n;i++)
	{
		printf("\n");
		for(j=a;j>=0;j--)
			printf(" ");
		for(j=i;j>0;j--)
			printf("%d",j);
		for(j=1;j<=i;j++)
			printf("%d",j);
		a--;
	}
	getch();
}