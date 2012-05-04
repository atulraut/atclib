#include<stdio.h>
#include<conio.h>
void main()
{
	int a[3][3],b[3][3],c[3][3],i,sum,k,j;
	clrscr();
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			printf("Please enter the value of a[%d][%d] = ",i,j);
			scanf("%d",&a[i][j]);
		}
	}
	for(i=0;i<3;i++)
	{

		for(j=0;j<3;j++)
		{
			printf("Please enter the value of b[%d][%d] = ",i,j);
			scanf("%d",&b[i][j]);
		}
	}

	printf("\n\n"); printf("a[2][3] = ");
	for(i=0;i<3;i++)
	{       printf("\n");
		for(j=0;j<3;j++)
		{
			printf("\t%d",a[i][j]);
		}
	}
	printf("\n\n"); printf("b[3][3] = ");
	for(i=0;i<3;i++)
	{       printf("\n");
		for(j=0;j<3;j++)
		{
			printf("\t%d",b[i][j]);
		}
	}
	printf("\n\n");
	 for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			sum=0;

			for(k=0;k<3;k++)
			{
				sum=sum+a[i][k]*b[k][j];
			}
			c[i][j]=sum;

		}
	}
	printf("\n\n"); printf("The product of matrix a and b is ");
	for(i=0;i<3;i++)
	{       printf("\n");
		for(j=0;j<3;j++)
		{
			printf("\t%d",c[i][j]);
		}



}

       getch();
}
