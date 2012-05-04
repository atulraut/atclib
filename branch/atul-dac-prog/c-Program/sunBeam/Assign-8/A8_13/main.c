#include<stdio.h>
int main()
{
	char str[80];
	int i;
	printf("\nEnter the string : ");
	scanf("%[^\n]",str);
	for(i=0;str[i]!='\0';i++);
	printf("Addition of all elements is : %d \n\n",i);
}