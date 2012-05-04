#include<stdio.h>
#include<conio.h>

int main()
{
	FILE *fp;
	int arr[10][10],i,j,n,m;
	fp = fopen("array.txt","w");
	if(fp == NULL)
	{
		printf("\nFile cannot open ");
		return 1;
	}
	printf("\nEnter the dimension of array : ");
	scanf("%d%d",&n,&m);
	printf("\nEnter the elements of the array : ");
	for(i-0;i<n;i++)
	{
		for(j=0;j<m;j++)
		{
			
		}
	}
	return 0;
}