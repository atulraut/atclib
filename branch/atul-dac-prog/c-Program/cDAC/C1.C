#include<stdio.h>
#include<conio.h>
void main()
{

	char *s;
	char *fun();
	clrscr();
	s=fun();
	printf("%s",s);
        getch();
}
char *fun()
{
	static char buffer[30];
	strcpy(buffer,"RAM_Rarely adeq");
	return(buffer);
}
