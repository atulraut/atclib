#include<stdio.h>
#include<string.h>
int main()
{
	char str[30],temp[30];
	int i=0,n=0,j;
	printf("Enter the string : ");	
	gets(str);
	while(str[i] != '\0')
	{
		n++;
		i++;
	}
	for(i=n-1,j=0;i>=0;i--,j++)
	{
		temp[j] =  str[i];
	}
	temp[ j ] = '\0';
	if(strcmp(temp,str) == 0)
		printf("\n\nEntered string is palindrome\n\n");
	else
		printf("\n\nEntered string is not palindrome\n\n");
}