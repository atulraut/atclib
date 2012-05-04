#include<stdio.h>
void upper(char *p)
{   
	while(*p != '\0')			
	{
		if(*p>=97 && *p<=122)
		{
			*p = *p - 32;
			p++;
		}
		else
			p++;
	}	
}