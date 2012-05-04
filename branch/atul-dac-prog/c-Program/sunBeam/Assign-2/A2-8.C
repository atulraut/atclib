#include<stdio.h>
#include<conio.h>
void main()
{
	char ch;
	clrscr();
	printf("\nEnter the character :");
	scanf("%c",&ch);
	if(ch>=0 && ch<=47)
		printf("\n The Character is a Special Character");
	else if(ch>=48 && ch<=57)
		printf("\n The Character is a Digit");
	else if(ch>=58 && ch<=64)
		printf("\n The Character is a Special Character");
	else if(ch>=65 && ch<=90)
		printf("\n The Character is a Capital Alphabets");
	else if(ch>=91 && ch<=96)
		printf("\n The Character is a Special Character");
	else if(ch>=97 &&  ch<=122)
		printf("\n The Character is a Small Alphabets");
	else if(ch>=123 && ch<=127)
		printf("\n The Character is a Special Character");
	else if(ch>=128 && ch<=255)
		printf("\n The Character is a Exteded Special Character");
	else
		printf("\nU have enter outof range character...");
		getch();
}