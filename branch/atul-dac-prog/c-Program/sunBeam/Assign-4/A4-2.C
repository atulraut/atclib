#include<stdio.h>
#include<conio.h>
void main()
{
	int n,i,j,cnt;
	clrscr();
	printf("\nEnter the number : ");
	scanf("%d",&n);
	for(i=0,cnt=1;cnt<=20;i++)
	{
		n = n + 1;
		for(j=2;j<n;j++)
		{
			if(n%j==0)
				break;
		}
		if(j==n)
		{
			printf("\t%d",n);
			cnt++;
		}
	}
	getch();
}