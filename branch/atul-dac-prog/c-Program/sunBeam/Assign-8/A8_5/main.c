/*Write a function to delete a given character 
  from string without leaving any hole.*/

#include<stdio.h>
#include<stdlib.h>
void strdel(char *, char,char *);
int main()
{
	char ch;
	char str[20];
	char p[20] ;
	printf("\nEnter the string :");
	scanf("%[^\n]",str);
	printf("\nEnter the charcter to be delete :");
	fflush(stdin);
	scanf("%c",&ch);
	strdel(str, ch,p);
	printf("\nNew string will be:%s\n\n",p);
	printf("\nNew string will be:%s\n\n",str);
	return 0;
}


