#include<stdio.h>
#include<conio.h>
#include<string.h>
void main()
{
	char a[80],b[80],c[80];
	int i;

	clrscr();
	printf("please enter the string");
	gets(a);
	printf("please enter the string");
	gets(b);
	i=strlen(a);
	printf("\n\nyour string is = %s\n length = %d",a,i);
	i=strlen(b);
	printf("\n\nyour string is = %s\n length = %d",b,i);
	i=strcmpi(a,b);
	printf("\n\n%d",i);
	if(i==0)

	printf("\n\nstrings are equal");

	else
	printf("not equal");
	strcat(a," ");
	strcat(a,b);
	printf("\n\nThe concat string is = %s ",a);
	strrev(a);
	printf("\n\nThe riverse string is = %s ",a);
	getch();
}