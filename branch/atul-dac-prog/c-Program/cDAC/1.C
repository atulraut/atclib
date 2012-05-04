#include<stdio.h>
#include<conio.h>
void main()
{
	FILE *fp,*ft;
	char ch;
	clrscr();
	fp=fopen("d:\vishal\v1.txt","r");
	ft=fopen("d:\vishal\v2.txt","w");
	if(ch=fgetc(fp)!=EOF)
	{
		fputc(ch,ft);
	}
	fcloseall();
	ft=fopen("d:\vishal\v2.txt","r");
	if(ch=fgetc(ft)!=EOF)
	{
		putchar(ch);
	}
	fclose(ft);
	getch();
}

