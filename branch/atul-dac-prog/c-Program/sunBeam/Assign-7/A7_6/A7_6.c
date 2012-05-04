#include<stdio.h>

int main()
{
	int arr[10][10],n,m,i,j;

	printf("\nEnter the dimension of 1st matrix : ");
	scanf("%d%d",&n,&m);
	
	printf("\nEnter the elements of 1st matrix : ");
	for(i=0;i<n;i++)
		for(j=0;j<m;j++)
				scanf("%d",&arr[i][j]);
	
	printf("\nOriginal Matrix is : \n");
	for(i=0;i<n;i++)
	{
		for(j=0;j<m;j++)
		{
			printf("%d  ",arr[i][j]);
		}
		printf("\n");
	}

	printf("\nTranspose of Matrix is : \n");
	for(i=0;i<m;i++)
	{
		for(j=0;j<n;j++)
		{
			printf("%d  ",arr[j][i]);		}
		printf("\n");
	}
	return 0;
}