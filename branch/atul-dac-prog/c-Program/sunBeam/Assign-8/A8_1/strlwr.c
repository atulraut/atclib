#include<stdio.h>
void lower(char *p)
{   
	while(*p != '\0')			
	{
		if(*p>=65 && *p<=90)
		{
			*p = *p + 32;
			p++;
		}
		else
			p++;
	}	
}