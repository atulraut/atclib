#include<stdio.h>   /* ----HEADER FILES FOR STANDARD I/O---- */
#include<conio.h>
#include<stdlib.h>

typedef struct node  /* ----DEFINING THE STRUCTURE---- */
{
	int data;
	struct node *next;
}NODE;
typedef struct list
{
	NODE *head;
}LIST;

int buff=0; /*GLOBAL DECLERATION*/

NODE *createnode(int val)       /* ----FOR CREATE NEW NODE---- */
{
	NODE *nn=(NODE*)malloc(sizeof(NODE));
	nn->data=val;
	nn->next=NULL;
	return nn;
}


void display(LIST *p)           /* ----FOR DISPLAY THE LINK LIST---- */
{
	NODE *trav=p->head;

	if(p->head==NULL)
	{
		printf("the node is empty");
		getch();

	}
	else
	{
        	trav=p->head;
		while(trav!=NULL)
		{
			printf("\t%d",trav->data);
			trav=trav->next;

		}
	}
}

void freenode(LIST *p)    /* ----FOR FREE THE MEMORY---- */
{
	NODE *trav=p->head;
	if(p->head==NULL)
	{
		printf("the node is empty");
		getch();
	}
	else
	{
		trav=p->head;
		while(trav!=NULL)
		{
			p->head=trav->next;
			free(trav);
			trav=p->head;
		}
	}
	buff=0;

}
void addlast(LIST *p,int val)  /* ----FOR ADDLAST---- */
{
	NODE *trav=p->head;
	NODE *nn=createnode(val);

	if(p->head==NULL)
		p->head=nn;
	else
	{
		while(trav->next!=NULL)
			trav=trav->next;
		trav->next=nn;
	}
}
void action(LIST *p1,LIST *p2)   /* ----FOR ADD TWO---- */
{                                /*IN THIS WE ADD 1st 2 NUMBER AND PLACE IT */
	NODE *trav=p1->head;     /*IN NEXT POSITION IN LINKLIST*/
	int n1,n2,sum;           /*THEN WE ADD THE NEXT 2 NUM. AND PLACE AFTER THAH*/
	if(p1->head==NULL)
	{
		printf("\n\nthe link is empty");
		getch();
	}
	else
	{
		trav=p1->head;
		while(trav!=NULL)
		{
			n1=trav->data;
			trav=trav->next;
			n2=trav->data;
			trav=trav->next;
			sum=n1+n2;
			addlast(p2,n1);
			addlast(p2,n2);
			addlast(p2,sum);
		}
	}
}



void main()      /* ----MANE FUNCTION OF PRPGRAM---- */
{
	LIST l1,l2;
	int ch,val;
	l1.head=NULL;
	l2.head=NULL;
	clrscr();
	printf("\nFILE PATH    : %s",__FILE__);
	printf("\nCURRENT DATE : %s",__DATE__ );
	printf("\nTOTAL LINES  : %d",__LINE__);
	printf("\nCURRENT TIME : %s",__TIME__);
	printf("\n\n\n\n");
	while(1)
	{
		printf("\nplease enter the choice");
		printf("\n1> DISPLAY");
		printf("\n2> ADDLAST");
		printf("\n3> ACTION");
		printf("\n0> EXIT");

		scanf("%d",&ch);
		switch(ch)
		{
			case 1:/*----display----*/
				display(&l1);
				break;
			case 2:/*----addlast----*/
				printf("\nplease enter the value");
				scanf("%d",&val);
				addlast(&l1,val);
				if(buff==1)
				{
					freenode(&l2);
				}

				break;
			case 3:/*----action----*/
				action(&l1,&l2);
				display(&l2);
				buff=1;
				break;

			case 0:
				exit(0);
		}
	}
}