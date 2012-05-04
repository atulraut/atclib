#include<stdio.h>
#include<stdlib.h>
int main()
{
	char buff[100], ch;
	int i=0, j;
	FILE *fp, *fs;
	
	fp = fopen("ooo.txt", "r");	
	if(fp == NULL)
	{
		printf("Source file content nothing");
		return 1;
	}
	
	fs = fopen("www.txt", "w");
	if(fs == NULL)
	{
		printf("Target File content nothing");
		return 1;
	}
	
	while((ch=fgetc(fp)) != EOF)
	{
		buff[i] = ch;
		i++;
	}
	for(j=i-2; j>=0; j--)
		fputc(buff[j], fs);
	
	printf("Entire content of the file are revesed \n\n");
	return 1;
}
