#include<stdio.h>
#include<conio.h>
void main()
{
	FILE *fp,*ft;
	char buff[80];
	clrscr();
	fp=fopen("c:\seed\vish1.txt","r");
	if(fp==NULL)
	{
		puts("The file cannot open");
		getch();
		exit();
	}

	ft=fopen("c:\seed\vish2.txt","w");
	if(ft==NULL)
	{
		puts("The file cannot open");
		fclose(fp);
		exit();
	}
	while(strlen(gets(buff))>0)
	{
		fputs(buff,ft);
		printf("%s",buff);
	}
	fclose(fp);
	fclose(ft);
	ft=fopen("c:\seed\vish2.txt","r");
	while(fgets(buff,sizeof(buff),ft)!=NULL)
	puts(buff);
	fclose(ft);
	getch();
}

