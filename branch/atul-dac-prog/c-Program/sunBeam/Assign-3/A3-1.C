#include<stdio.h>
#include<conio.h>
void main()
{
	int month;
	clrscr();
	printf("Enter the month ");
	scanf("%d",&month);
	switch(month)
	{
		case 1 :
			printf("\n\"January\" has 31 days ");
			break;
		case 2 :
			printf("\n\"Febuary\" has 28 days ");
			break;
		case 3 :
			printf("\n\"March\" has 31 days ");
			break;
		case 4 :
			printf("\n\"April\" has 30 days ");
			break;
		case 5 :
			printf("\n\"May\" has 31 days ");
			break;
		case 6 :
			printf("\n\"June\" has 30 days ");
			break;
		case 7 :
			printf("\n\"July\" has 31 days ");
			break;
		case 8 :
			printf("\n\"August\" has 31 days ");
			break;
		case 9 :
			printf("\n\"September\" has 30 days ");
			break;
		case 10 :
			printf("\n\"Octomber\" has 31 days ");
			break;
		case 11 :
			printf("\n\"November\" has 30 days ");
			break;
		case 12 :
			printf("\n\"December\" has 31 days ");
			break;
		default :
			printf("\nYou have entered wrong month ");
	}
	getch();
}