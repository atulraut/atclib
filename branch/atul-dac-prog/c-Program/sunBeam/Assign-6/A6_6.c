#include<stdio.h>
#include<conio.h>
void main()
{
	int i,a=0,j;
	int arr[10],temp[10];
	printf("\n Enter 10 number : ");
	for(i=0; i<5; i++)
	{
		scanf("\t%d",&arr[i]);
	}
	temp[0] = arr[0];
	for(i=1; i<5; i++)
	{		
		for(j=i+1;j<5;j++)
		{
			if(arr[i]==arr[j])
				temp[j] = 0;	
			else
				temp[j] = arr[j]; 
		}

	}	
	for(i=0;i<5;i++)
	{
		if(temp[i] == 0)
			continue;
		//arr[a] = temp[i];
		printf("\t%d",temp[i]);
		a++;
	}
	printf("\n\n");
}