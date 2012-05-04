#include<stdio.h>
#include<conio.h>
void main()
{
	int no,i,j,temp,cnt = 1;
	clrscr();
	printf("\nEnter the number whose factors to find : ");
	scanf("%d",&no);
	printf("%d = ",no);
	temp = no;
	for(i=0;i<temp;i++)
	{
		for(j=2;j<=no;j++)
		{
			if(no%j==0)
			{
				if(cnt == 1)
				{
					printf("%d ",j);
					no = no/j;
					cnt++;
					break;
				}
				else
				{
					printf("* %d ",j);
					no = no/j;
					break;
				}
			}
		}
	}
	getch();
}