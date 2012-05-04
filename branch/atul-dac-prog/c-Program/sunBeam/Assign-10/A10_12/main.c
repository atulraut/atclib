#include<stdio.h>
#include<stdlib.h>

struct student
{
	char name[20];
	int rollno;
	int sclass;
};
typedef struct student stud;

FILE *fp;
stud s;

int main()
{
	int ch;
	while(1)
	{
		system("cls");	
		printf("\n1.Enter Data \n2. Update \n3. Display \n0. Exit");
		printf("\nPlease enter the choice ");
		scanf("%d",&ch);
		switch(ch)
		{
			
		}
	}
}