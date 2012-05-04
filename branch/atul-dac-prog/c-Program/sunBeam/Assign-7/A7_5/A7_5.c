#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

void addition(int [][10],int [][10], int ,int);
void subtraction(int [][10],int [][10], int ,int);
void multiplication(int [][10],int ,int ,int [][10],int ,int);

void main()
{
	int arr[10][10],n,m=1,a=0,b,i,j,no=1,brr[10][10];

	printf("\nEnter the dimension of 1st matrix : ");
	scanf("%d%d",&n,&m);
	
	printf("\nEnter the elements of 1st matrix : ");
	for(i=0;i<n;i++)
		for(j=0;j<m;j++)
				scanf("%d",&arr[i][j]);
	
	while(m!=a)
	{
		printf("\nEnter the dimension of 2nd matrix : ");
		scanf("%d%d",&a,&b);
		if(m!=a)
			printf("Multiplication cannot be done  ");
	}
	
	printf("\nEnter the elements of 2nd matrix : ");
	for(i=0;i<a;i++)
		for(j=0;j<b;j++)
				scanf("%d",&brr[i][j]);
	
	while(no != 0 || no != 0) 
	{
		system("cls");
		printf("\n1.Addition \n2.Subtraction \n3.Multiplication \n0.Exit \n");
		printf("\nWhat you want to do ?");
		scanf("%d",&no);
		switch(no)
		{
			case 1:
				addition(arr,brr,n,m);
				break;
			case 2:
				subtraction(arr,brr,n,m);
				break;
			case 3:
				multiplication(arr,n,m,brr,a,b);
				break;
			case 0 :
				break;
			default :
				printf("\nPlease Enter valid choice ");
		}
		getch();
	}

	/*	for(i=0;i<n;i++)
			printf("\n\n%u ",*(arr+i));
		printf("\n\n %d  \n\n",*(*(arr+1)+1)+10);*/
}