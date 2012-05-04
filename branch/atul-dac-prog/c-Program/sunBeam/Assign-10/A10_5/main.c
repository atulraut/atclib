#include<stdio.h>
#include<stdlib.h>

int main()
{
	char chr;
	int ch,line,space,tab;
	FILE *fp;
	ch = line = space = tab = 0;
	
	fp = fopen("D:\\wimc\\Assign-10\\abc.txt","r");
	if(fp == NULL)
	{
		printf("File cannot be open ");
		return 1;
	}
	while((chr = fgetc(fp)) != EOF)
	{
		if(chr == ' ')
			space++;
		if(chr == '\n')
			line++;
		if(chr == '\t')
			tab++;
		ch++;
	}
	printf("\nNo of Spaces = %d",space);
	printf("\nNo of Lines = %d",line);
	printf("\nNo of Character = %d",ch);
	printf("\nNo of Tabs = %d",tab);
	printf("\nNo of words = %d\n",space+line+1);
	return 1;
}