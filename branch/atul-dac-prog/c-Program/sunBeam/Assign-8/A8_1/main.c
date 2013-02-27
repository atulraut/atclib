/*
* Aim : Sunbeam assignment for string operation.
* Date : Thurday, 07/02/2013 09:23:37PM
*
***/
#include<stdio.h>

void upper(char *);
char * mystrstr(char *,char *);
void lower(char *);
int mystrcmp(char *, char *);

int main() {
	char str[30],find[20];
	int temp;
//	char *ptr;
	printf("\nEnter 1st the string : ");
	gets(str);
	fflush(stdin);	
	printf("\nEnter  2nd the string : ");
	gets(find);


/*	printf("\nEnter the string to find : ");
	gets(find);
	ptr = mystrstr(str,find);
	printf("\n\nThe \"%s\" string is present at %d position\n\n",find,(ptr - str));
	printf("\n\n%d\n\n",str);
	printf("\n\n%d\n\n",ptr);
	upper(str);
	printf("The upper case string now is = %s\n\n", str);	
	lower(str);
	printf("The lower case string now is = %s\n\n", str);*/
	temp = mystrcmp(str, find );
	printf("The differance in string is = %d\n\n",temp);

	return 0;
}
