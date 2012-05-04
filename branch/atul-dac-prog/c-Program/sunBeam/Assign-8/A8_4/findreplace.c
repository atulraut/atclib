#include<string.h>
#include<stdio.h>

void findreplace(char *string, char *find, char *replace)
{
	char *temp , str[50];	
	char *pstr = str;
	int n ,i;

		temp = strstr(string, find);/*Returnn 1st occurnce of f in s*/
									/*temp = address of find str*/
		if(temp == NULL)
		{
			printf("\n%s is not found in %s ",find,string);
			return;
		}
		n = temp - string;
		for(i=0;i<n;i++)
		{
			*pstr = *string;
			pstr++;
			string++;
		}
		for(i=0;*replace != '\0';i++)
		{
			*pstr = *replace;
			pstr++;
			replace++;
		}
		for(i=0;*find != '\0';i++)
		{
			string++;
			find++;
		}
		for(i=0;*string != '\0';i++)
		{
			*pstr = *string;
			pstr++;
			string++;
		}
		*pstr = '\0';
		strcpy(string,pstr);
}



