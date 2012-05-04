#include<stdio.h>
#include<stdlib.h>
#include<conio.h>

struct emp
{
	char name[10];
	int no;
	float bs;
};

void AcceptEmpDetails(struct emp *);
float CalculateSal(float );
void DisplayEmpDetails(struct emp *);	


  int main()
	{
	  struct emp e;
	int ch;				
	while(1)
		{
			system("cls");
			printf("\n0 >Exit\n1 >Accept Details\n2 >Display\n");	
			scanf("%d", &ch);
			switch(ch)
			{
				case 0 :
						return 1;
						break;
				case 1 :
					    AcceptEmpDetails(&e);
						break;
				case 2 :
						 DisplayEmpDetails(&e);
						 break;
				default :
					{
						printf("Enter correct choice...");
					}
				
			}
		}
	return 1;
  }


void AcceptEmpDetails(struct emp *p)
{
		printf("Enter employee name :");
			scanf("%s",p->name);
		printf("\nEnter employee no :");
			scanf("%d",&(p->no));
		printf("\nEnter employee  basic salary :");
			scanf("%f",&(p->bs));
}

void DisplayEmpDetails(struct emp *p)
{
	float sal = CalculateSal(p->bs);
	printf("\nEmployee name : %s\n",p->name);

	printf("\nEmployee no : %d\n",p->no);

	printf("\nEmployee  basic salary : %f\n",p->bs);
			
	printf("\nEmployee  Salary : %f\n",sal);
	getch();
}


float CalculateSal(float bs)
{
	float sal,hra,da,cf;
	hra = (float)(0.1 * bs);
	da = (float)(0.2 * bs);
	cf = (float)(0.02 * bs);
	sal = bs + hra + da - cf;
	return sal;
}
	

