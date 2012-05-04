#include<stdio.h>
#include<stdlib.h>
int main()
{
	char buff[20], ch;
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
			if(ch  != ' ' || ch != '\n')							
				buff[i] = ch;
			i++;
			if(ch == ' ' ||  ch == '\n')
				{
					for(j=i-2; j>=0; j--)
						fputc(buff[j], fs);
					if(ch == ' ')
						fputc(' ', fs);
					if(ch == '\n')
						fputc('\n', fs);
					i = 0;
				}
		}
	printf("Each word in the file reverces sucessfully\n\n");
	return 1;
}
