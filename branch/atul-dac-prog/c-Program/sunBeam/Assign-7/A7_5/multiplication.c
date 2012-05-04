#include<stdio.h>
multiplication(int arr[][10],int n, int m,int brr[][10],int a,int b)
{
	int i,j,k,sum=0;
	int c[10][10];
	for(i=0;i<n;i++)
	{
		for(j=0;j<b;j++)
		{
			sum =0;
			for(k=0;k<m;k++)
			{
				sum = sum + arr[i][k] * brr[k][j];
			}
			c[i][j] = sum;
		}
	}
	for(i=0;i<n;i++)
	{
		for(j=0;j<b;j++)
		{
			printf("%d ",c[i][j]);
		}
		printf("\n");
	}
}
