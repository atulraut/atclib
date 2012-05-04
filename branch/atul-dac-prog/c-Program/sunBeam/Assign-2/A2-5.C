#include<stdio.h>
#include<conio.h>
void main()
{
	int year;
	clrscr();
	printf("\nEnter the year :");
	scanf("%d",&year);
	if(year%400==0 || year%4==0)
		printf("The year is Leap Year and no of days are = 366");
	else
		printf("The year is not a Leap Year and no of days are = 365");
	getch();
}