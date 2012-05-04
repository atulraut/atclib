#include<stdio.h>
#include<conio.h>
void print(int , char );
void main()
{
	char ch;
	int no;
	clrscr();
	printf("\nEnter the character : ");
	scanf("%c",&ch);
	if(ch>=65 && ch<=90)
	{
		no = ch - 65;
		print(no+1,'A');
	}
	else if(ch>=97 && ch<=122)
	{
		no = ch - 97;
		print(no+1,'a');
	}
	else
		printf("\nYour entered character is not alphabet .....");
	getch();
}
void print(int no ,char temp)
{
	int i,j;
	char ch;
	for(i=no; i>=1; i--)
	{
		ch = temp;
		printf("\n");
		for(j=i; j>=1; j--)
		{
		/*	if(j==1 && i==no)
			{
				ch++;
				continue;
			}*/
			printf("%c ",ch);
			ch++;
		}
		ch--;
		for(j=(no-i);j>0;j--)
			printf("    ");
		for(j=1;j<=i;j++)
		{

			printf("%c ",ch);
			ch--;
		}
	}
}