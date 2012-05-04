

#include<stdio.h>
#include<conio.h>
void main()
{
	FILE *fp;
	char buff[20],flag[20]="\0";
	int i=0;
	clrscr();
	fp=fopen("c:\seed\vish1.txt","r");
	if(fp==NULL)
	{
		puts("the file is not open");
		getch();
		exit();
	}
	while(fscanf(fp,"%s",buff)!=EOF)
	{
		if(strcmp(flag,buff)==0)
		{	i++;
			printf("Double word = %s\nhow many times = %d",buff,i);
		}
		else
			strcpy(flag,buff);

	}
       fclose(fp);
       getch();


}