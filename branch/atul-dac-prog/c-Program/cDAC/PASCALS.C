#include<stdio.h>
#include<conio.h>
void main()
{
	int row,num,i,j,space;
	char ch;
	clrscr();
	do
	{
		printf("\n Enter no. of rows: ");
		scanf("%d",&row);
		num=1;
		i=0;
		printf("\n\t\t\t*** PASCALS TRIANGLE***\n");
		while(i<row)
		{
			printf("\n");
			/*print space on lrft side*/
			for(space=(30-3*i);space>0;space--)
			printf(" ");
			/*calculate value of num & print*/
			for(j=0;j<=i;j++)
			{
				if(j==0||i==0)
					num=1;
				else
					num=(num*(i-j+1)/j);
				printf("%6d",num);
			}
			i++;
		}
	printf("\nif u want to continue then press 'y' else press 'n'");
	scanf("%c",&ch);
	}while(ch=='y'||ch=='Y');

	getch();
}