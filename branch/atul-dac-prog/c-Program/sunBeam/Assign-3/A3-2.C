#include<stdio.h>
#include<conio.h>
void funct(int);
void funct1(int);
void main()
{
	int n,a,b;
	clrscr();
	printf("\nEnter the 2 digit no : ");
	scanf("%d",&n);
	if(n>=1 && n<=10)
		funct(n);
	else if(n>=11 && n<=19)
		funct1(n);
	else if(n>=20 && n<=29)
	{
		a = n%10;
		printf("Twenty ");
		if(a!=0)
			funct(a);
	}
	else if(n>=30 && n<=39)
	{
		a = n%10;
		printf("Thirty ");
		if(a!=0)
			funct(a);
	}
	else if(n>=40 && n<=99)
	{
		a = n/10;
		funct(a);
		printf("ty ");
		b = n%10;
		if(b!=0)
			funct(b);
	}
	else
		printf("\nPls enter 2 digit no ");
	getch();
}
void funct(int a)
{
	switch(a)
	{
		case 1 :
			printf("One");
                        break;
		case 2 :
			printf("Two");
                        break;
		case 3 :
			printf("Three");
                        break;
		case 4 :
			printf("Four");
                        break;
		case 5 :
			printf("Five");
                        break;
		case 6 :
			printf("Six");
                        break;
		case 7 :
			printf("Seven");
			break;
		case 8 :
			printf("Eight");
			break;
                case 9 :
			printf("Nine");
			break;
		case 10 :
			printf("Ten");
			break;
		default :
			printf("Out of Range");
	}
}
void funct1(int a)
{
	switch(a)
	{
		case 11 :
			printf("Eleven");
                        break;
		case 12 :
			printf("Twelve");
                        break;
		case 13 :
			printf("Thirteen");
                        break;
		case 14 :
			printf("Fourteen");
                        break;
		case 15 :
			printf("Fifteen");
                        break;
		case 16 :
			printf("Sixteen");
                        break;
		case 17 :
			printf("Seventeen");
			break;
		case 18 :
			printf("Eighteen");
			break;
		case 19 :
			printf("Nineteen");
			break;
		default :
			printf("Out of Range");
	}
}