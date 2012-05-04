#include<stdio.h>
#include<conio.h>
#include<string.h>
int slength(char *);
void sconcat(char*,char* );
void main()
{
	char a[80],b[80];
	int i;
	clrscr();
	printf("pleae enter two string");
	gets(a);
	gets(b);
	puts(a);
	puts(b);
	i=slength(a);
	printf("\n\nlength = %d\n",i);
	sconcat(a,b);
	puts(a);
	getch();
}
int slength(char *aa)
{
	int i;
	for(i=0;*aa!='\0';i++)
	{
	aa++;
	}
	return(i);
}
void sconcat(char *aa,char* bb)
{
	int i;
	i=0;
	while(*aa!='\0')
	{
		aa++;i++;
	}

	i=0;
	while(*bb!='\0')
	{
		*aa=*bb;
		aa++;bb++;i++;
       }
}