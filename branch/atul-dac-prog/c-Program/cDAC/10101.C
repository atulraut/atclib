#include<stdio.h>
#include<conio.h>
void main()
{
	int i,j,m,n;
	clrscr();
	m=0,n=1;
	for(i=0;i<7;i++)
	{
		printf("\n\t\t");
		for(j=1;j<=i+1;j++)
		{
			if(i%2!=0)
			{
				if(j%2!=0)
				printf("%d",m);
				else
				printf("%d",n);

			}
			else
			{
				if(j%2!=0)
				printf("%d",n);
				else
				printf("%d",m);
			}
		}
	}
	getch();

}