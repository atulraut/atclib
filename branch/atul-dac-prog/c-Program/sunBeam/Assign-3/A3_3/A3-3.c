#include<stdio.h>
#include<conio.h>
void print(int,char *,char);
void main()
{
	int eid,deptno;
	char desgcode;
	char deptname[4][20] = {"Marketing","Management","Sales","Designing"};
	printf("\nEnter the Employee id, Dept No. and Desgination code : ");
	scanf("%d%d",&eid,&deptno);
	fflush(stdin);
	scanf("%c",&desgcode);
	switch(deptno)
	{
		case 10:
			print(eid,deptname[0],desgcode);
			break;
		case 20:
			print(eid,deptname[1],desgcode);
			break;
		case 30:
			print(eid,deptname[2],desgcode);
			break;
		case 40:
			print(eid,deptname[3],desgcode);
			break;
		default :
			printf("Please enter valid Dept No \n");
	}
}

void print(int id,char * name,char code)
{
	switch(code)
	{
		case 'M':
			printf("\nEmployee with employee id %d is working in \"%s\" department as \"Manager\".\n",id,name);
			break;
		case 'S':
			printf("\nEmployee with employee id %d is working in \"%s\" department as \"Supervisor\".\n",id,name);
			break;
		case 's':
			printf("\nEmployee with employee id %d is working in \"%s\" department as \"Security Officer\".\n",id,name);
			break;
		case 'c':
			printf("\nEmployee with employee id %d is working in \"%s\" department as \"Clerk\".\n",id,name);
			break;
		default :
			printf("\nPlease enter valid Designation code \n");
	}
}