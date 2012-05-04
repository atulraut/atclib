/*IN THIS PROG. WE ASK THE DATA TO USER IT 1st COLLECT IN STRUCTURE AND
 THEN IT WRITE ON FILE.
 IN THIS THE FILE IS IN BINARY MODE */

#include<stdio.h>
#include<conio.h>

typedef struct employ
{
	char fname[20];
	char lname[20];
	int age;
}e;
void main()
{
	e e1;
	int ch,f=1;
	FILE *fp,*ft;
	long int sz=sizeof(e);
	char name[20];
	clrscr();
	fp=fopen("f:\\practise\\seed\\vish.dat","wb");
	fclose(fp);
	fp=fopen("f:\\practise\\seed\\vish.dat","rb+");

	if(fp==NULL)
	{
		printf("\ncannot open the file");
		getch();
	}

	while(1)
	{
		printf("\n0> EXIT\n1> ADD\n2> DISPLAY\n3> MODIFY\n4> DILIT\n");
		printf("\nplease enter the choich");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1:/*----ADD----*/
			       printf("\nplease enter the 1st name last name and age");
			       scanf("%s%s%d",e1.fname,e1.lname,&e1.age);
			       fwrite(&e1,sz,1,fp);
			       break;
			case 2:/*----DISPLAY----*/
				fseek(fp,0L,SEEK_SET);
				printf("\nFIRST NAME	LAST NAME	AGE");
				while(fread(&e1,sz,1,fp)==1)
				{
					printf("\n");
					printf("%s\t\t%s\t\t%d",e1.fname,e1.lname,e1.age);
				}
				break;
			case 3:/*----MODIFY----*/
				f=1;
				printf("\nenter the name");
				scanf("%s",name);
				fseek(fp,0L,SEEK_SET);
				while(fread(&e1,sz,1,fp)==1)
				{
					if(strcmp(e1.fname,name)==0)
					{
						printf("\nplease enter the name last name and age");
						scanf("%s%s%d",e1.fname,e1.lname,&e1.age);
						fseek(fp,-sz,SEEK_CUR);
						fwrite(&e1,sz,1,fp);
						f=0;
						break;

					}
					else
						continue;
				}
				if(f==1)
				printf("\nthe name is not found");
				break;
			case 4:/*----DILIT----*/
				 f=1;
				 ft=fopen("d:\\vishal\\vish1.dat","wb+");
				printf("\nenter the name");
				scanf("%s",name);
				fseek(fp,0L,SEEK_SET);
				while(fread(&e1,sz,1,fp)==1)
				{
					if(strcmp(e1.fname,name)==0)
					{
						f=0;
						continue;
					}
					else
					{
						fwrite(&e1,sz,1,ft);
					}
				}
				fclose(ft);
				fclose(fp);
				remove("d:\\vishal\\vish.dat");
				rename("d:\\vishal\\vish1.dat","d:\\vishal\\vish.dat");
				fp=fopen("d:\\vishal\\vish.dat","rb+");
				if(f==0)
					printf("\nthe data is remove sucessifully");
				else
					printf("\nthe name is not found");
				getch();
				break;
			case 0:
				fclose(fp);
				exit(0);
		}
	}
	/*getch();*/
}