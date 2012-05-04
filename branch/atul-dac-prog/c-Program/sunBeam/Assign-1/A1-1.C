#include<stdio.h>
#include<conio.h>
void main()
{
	int len,breadth,area;
	clrscr();
	printf("Enter the length and breadth : ");
	scanf("%d%d",&len,&breadth);
	area = len * breadth;
	printf("\nArea is %d ",area);
	getch();
}