#include<stdio.h>
#include<conio.h>
void main()
{
	char ch;
	clrscr();
	printf("Enter the character :");
	scanf("%c",&ch);
	if(ch>=65 && ch<=90)
	{
		ch = ch + 32;
		printf("\nReverse case of alphabet is : %c ",ch);
	}
	else if(ch>=97 && ch<=122)
        {
		ch = ch - 32;
		printf("\nReverse case of alphabet is : %c ",ch);
	}
	else
		printf("\nEntered value is not alphabet");
	getch();
}