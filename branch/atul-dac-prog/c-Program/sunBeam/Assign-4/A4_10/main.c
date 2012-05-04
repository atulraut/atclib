#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
void main()
{
	int i,j,a,b = 1;
	printf("\nEnter the number : ");
	scanf("%d",&a);
	for(i=1;i<=a;i++)
	{
		printf("\n");
		for(j=1;j<=i;j++)
		{
			printf("%2d ",b);
                        if(a==b)
			{
				printf("\n");
				exit(0);
			}
			
			b++;
		}
	}
}