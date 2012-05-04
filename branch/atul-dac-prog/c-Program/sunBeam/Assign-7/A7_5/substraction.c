#include<stdio.h>
#include<conio.h>
void subtraction(int a[][10],int b[][10],int n,int m)
{
	int temp[10][10],i,j;
	for(i=0; i<n; i++)
	{
		for(j=0; j<m; j++)
		{
			temp[i][j] = a[i][j] - b[i][j];
			printf("%d  ",temp[i][j]);
		
		}
		printf("\n");
	}
}