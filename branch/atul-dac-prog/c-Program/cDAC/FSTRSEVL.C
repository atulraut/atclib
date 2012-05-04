/*IN THIS PRO. WE READ THE DATA FROM ONE FILE AND STORED IT IN ANOTHER FILE IN REVERSE PATERN*/

#include<stdio.h>
#include<conio.h>
void main()
{
	FILE *fp,*ft;
	char buff[250],ch;
	int i;
	clrscr();
	fp=fopen("c:\\seed\\mugdha.txt","r");
	if(fp==NULL)
	{
		puts("the file cannot open");
		getch();
		exit();
	}
	ft=fopen("c:\seed\kasturi.txt","w");
	if(ft==NULL)
	{
		puts("the file cannot open");
		fclose(fp);
		getch();
		exit();
	}
	while(fgets(buff,sizeof(buff),fp)!=NULL)
	{
		strrev(buff);
		fprintf(ft,"%s",buff);
		/*fputs("\n",ft);   */
	}
	fclose(fp);
	fclose(ft);
	ft=fopen("c:\seed\kasturi.txt","r");
	while((ch=fgetc(ft))!=EOF)
	{
		/*if(ch=='\n')
		  printf("\n");*/
		putchar(ch);
	}
	fclose(ft);
	getch();
}