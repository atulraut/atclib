#include<stdio.h>
#include<conio.h>
void maxmin(int *);
void main()
{
	int arr[10],i;
	printf("\nEnter 10 numbers : ");
	for(i=0;i<10;i++)
	{
		scanf("%d",&arr[i]);
	}
	maxmin(&arr[0]);
	for(i=0;i<10;i++)
	{
		printf("\t%d",arr[i]);
	}
}