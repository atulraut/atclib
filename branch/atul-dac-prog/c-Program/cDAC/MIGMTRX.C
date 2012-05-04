/*IN THIS PROGRAM WE INSERT THE VALUE OF MATRIX AT EACH POSITION AND THE
 PROG. TELS US THAT THE MATRIX IS MAGIC MATRIX OR NOT
 MAGIC MATRIX: The matrix in which the addition of each rows element,
 each colloms element, and the addition of each digonal element is same
 IN THIS PROGRAM WE USE THE MACRO*/

#include<stdio.h>
#include<conio.h>
#define max 4    /*MACRO*/
void main()
{
	int a[10][10],i,j,k,d1,d2,row[10],colm[10];
	clrscr();
	for(i=0;i<max;i++)
	{
		for(j=0;j<max;j++)
		{
			printf("please enter the value of a[%d][%d] = ",i,j);
			scanf("%d",&a[i][j]);
		}
	}
	printf("\nyour matrix is as follows:\n");
	for(i=0;i<max;i++)
	{
		for(j=0;j<max;j++)
		{
			printf("  %4d",a[i][j]);
		}
		printf("\n");
	}

	for(i=0;i<max;i++)
	{
		k=0;
		for(j=0;j<max;j++)
		{
			k=k+a[i][j];
		}
		row[i]=k;
	}
	k=row[0];
	for(i=0;i<max;i++)
	{
		if(k==row[i])
		continue;
		else
		{
			printf("This matrix is not a magic matrix");
			getch();
			exit();
		}
	}

	for(i=0;i<max;i++)
	{
		k=0;
		for(j=0;j<max;j++)
		{
			k=k+a[j][i];
		}
		colm[i]=k;
	}
	k=colm[0];
	for(i=0;i<max;i++)
	{
		if(k==colm[i])
		continue;
		else
		{
			printf("This matrix is not a magic matrix");
			getch();
			exit();
		}
	}
	 d1=0;
	 for(i=0;i<max;i++)
	{
			d1=d1+a[i][i];
	}
	if(k==d1)
	{

		 for(i=0;i<max;i++)
		{
			d2=0;
			for(j=max-1;j>=0;j--)
			{
				d2=d2+a[i][j];
			}

		}
		if(d1==d2 && colm[0]==row[0]  && row[0]==d1)
		     puts("your matrix is a MAGIC MATRIX");

	}
	else
	puts("your matrix is NOT A MAGIC MATRIX");

	getch();




}
