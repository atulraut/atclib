#include<stdio.h>
#include<conio.h>
void main()
{
	int i,j,k;
	clrscr();
	for(i=1;i<=50;i++)
	{
		for(j=i;j<=50;j++)
		{
			for(k=j;k<=50;k++)
			{
				if((i*i) + (j*j) == (k*k))
					printf("\n%2d * %2d + %2d * %2d = %2d * %2d",i,i,j,j,k,k);
			}
		}
	}
	getch();
}
