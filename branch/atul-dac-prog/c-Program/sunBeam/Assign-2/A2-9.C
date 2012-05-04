#include<stdio.h>
#include<conio.h>
void main()
{
	int std, eng, math, sci,hin,mar;
	float per,pems,ems,total;
	clrscr();
	printf("\nEnter the standard of the student :");
	scanf("%d",&std);
	printf("\nEnter the Marks of the Student :");
	printf("\nEnglish = ");
	scanf("%d",&eng);
	printf("\nMath = ");
	scanf("%d",&math);
	printf("\nScience = ");
	scanf("%d",&sci);
	printf("\nHindi = ");
	scanf("%d",&hin);
	printf("\nMarathi = ");
	scanf("%d",&mar);
	ems = eng + math + sci;
	pems = (float)(ems/300)*100;
	total = eng + math + sci + hin + mar;
	per = (float)(total/500)*100;
	if(std==10)
	{
		if(pems>60)
		{
			if(eng>50 && mar>50 && hin>50)
			{
				if(per>40)
					printf("\nAddmission Granted ");
				else
					printf("\nAggregate marks must be minimum 40%");
			}
			else
				printf("\nMarks in  each language must be 50%");
		}
		else
			printf("\nTotal marks in English, Maths & Science must be > 60%");
	}
	else
		printf("\nStudent must be Xth std passed.");
	getch();
}



