#include<stdio.h>
#include<conio.h>

int main()
{
	char str[30],alpha[10];
	char *p1,*p2;
	p1 = str;
	p2 = alpha;
	printf("\nEnter the string : ");
	gets(str);
	while(*p1 != '\0')
	{
		*p2 = *p1;
		while(*p1 != ' ')
			p1++;
		p2++;
		p1++;
	}
	*p2 = '\0';
	printf("\nAcromatic string is :- %s \n\n",alpha);
	return 0;
}