#include<stdio.h>
#include<string.h>
#include<stdlib.h>
void findreplace(char *, char *, char *);
void main()
{

	char string[50]; 
	char find[50];
	char replace[50];
	printf("\nEnter the string :");
	gets(string);	
	fflush(stdin);
	printf("\nEnter the string to be find:");
	gets(find);
	fflush(stdin);
	printf("\nEnter the string to be replace :");
	gets(replace);
	findreplace(string, find, replace);
	printf("The new string is =%s \n", string);
}