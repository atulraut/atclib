#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
typedef struct node
{
  int sal;
  char name[30];
  struct node *next;

}NODE;

NODE *head=NULL;

/*NODE * createnode(NODE*);
void addlast(NODE *);
void addfirst(NODE *);
void display();
void insert(NODE*,int);
void delfirst();
void delmid(int);
void reverse();*/

NODE * createnode(NODE*temp1)
{
  NODE *newnode;
  newnode=malloc(sizeof(NODE));
  newnode->next=NULL;
  newnode->sal=temp1->sal;
  strcpy(newnode->name,temp1->name);
  return newnode;
}
void display()
{
  NODE *trav;
  trav=head;
  if(head==NULL)
    printf("\nno node and data is available");
  else
  {
     /*clrscr();*/
     printf("\n=====================================");
     printf("\n NAME               SALARY           ");
     printf("\n======================================");
     while(trav!=NULL)
     {
       printf("\n%s",trav->name);
       printf("\t\t\t%d",trav->sal);
       trav=trav->next;
     }
     printf("\n======================================\n");
  }

}
void addlast(NODE* temp1)
{
  NODE *trav,*newnode;
  trav=head;
  newnode=createnode(temp1);
  newnode->next=NULL;
  if(head==NULL)
      head=newnode;
  else
  {
    while(trav->next!=NULL)
      trav=trav->next;
    trav->next=newnode;
  }
}

void addfirst(NODE *temp1)
{
  NODE *trav,*newnode;
  trav=head;
  newnode=createnode(temp1);
  newnode->next=head;
  head=newnode;

}

void insert(NODE*temp1,int n)
{
  NODE *trav,*newnode;
  int i;
  trav=head;
  newnode=createnode(temp1);
  newnode->next=NULL;
  if(n==1)
   addfirst(temp1);
  else
  {
     for(i=1;i<n-1;i++)
      trav=trav->next;
    newnode->next=trav->next;
    trav->next=newnode;
  }
}

void delmid(int n)
{
  NODE *trav,*temp;
  int i;
  trav=head;
  if(head==NULL )
   printf("\nlist is empty");
  else
  {
      for(i=1;i<n-1;i++)
	 trav=trav->next;
      temp=trav->next;
    trav->next=temp->next;
    free(temp);
  }
}

void delfirst()
{
  NODE *temp;
  temp=head;
  if(head==NULL )
   printf("\nlist is empty");
  else
  {
    head=head->next;
    free(temp);
  }
}
void reverse()
{
 NODE *trav,*temp,*p;
 p=head;
 trav=head;
 head=head->next;
 while(temp->next!=NULL)
   {

	temp=head->next;
	head->next=trav;
	trav=head;
	head=temp;
   }
	head->next=trav;
	p->next=NULL;
}
void main()
{
	 int choice,sal=0,pos;
	 NODE *temp1;
	 char ch;
	 clrscr();
	 while(1)
	 {
	    printf("\n1---->addlast");
	    printf("\n2---->addfirst");
	    printf("\n3---->display");
	    printf("\n4---->exit");
	    printf("\n5---->insert");
	    printf("\n6---->delfirst");
	    printf("\n7---->delmid");
	    printf("\n8---->reverse");
	    printf("\n enter your choice");
	    fflush(stdin);
	    scanf("%d",&choice);
	    switch(choice)
	    {
		case 1:
			printf("\nenter the salary & name to be inseted in node");
			fflush(stdin);
			scanf("%d%s",&(temp1->sal),temp1->name);
			addlast(temp1);
			break;
		case 2:
			printf("\nenter the salary and name to be inserted in node");
			scanf("%d%s",&temp1->sal,temp1->name);
			addfirst(temp1);
			break;
		case 3:
			display();
			getch();
			break;
		case 4:
			exit(1);
		case 5:
			printf("\nenter the salary,name and position of node to be inseted ");
			fflush(stdin);
			scanf("%d%s",&temp1->sal,temp1->name,&pos);
			insert(temp1,pos);
			break;
		case 6:
			delfirst();
			getch();
			break;
		case 7:
			printf("\nenter the position at which node to be deleted");
			scanf("%d",&pos);
			delmid(pos);
			break;
		case 8:
			reverse();
			break;
		default :
			printf("\n you have entered wrong choice");
	      }
	  }
/*getch();*/
}

/*NODE * createnode(NODE*temp1)
{
  NODE *newnode;
  newnode=malloc(sizeof(NODE));
  newnode->next=NULL;
  newnode->sal=temp1->sal;
  strcpy(newnode->name,temp1->name);
  return newnode;
}
void display()
{
  NODE *trav;
  trav=head;
  if(head==NULL)
    printf("\nno node and data is available");
  else
  {* /
     /*clrscr();*/
    /* printf("\n=====================================");
     printf("\n NAME               SALARY           ");
     printf("\n======================================");
     while(trav!=NULL)
     {
       printf("\n%s",trav->name);
       printf("\t\t\t%d",trav->sal);
       trav=trav->next;
     }
     printf("\n======================================\n");
  }

}
void addlast(NODE* temp1)
{
  NODE *trav,*newnode;
  trav=head;
  newnode=createnode(temp1);
  newnode->next=NULL;
  if(head==NULL)
      head=newnode;
  else
  {
    while(trav->next!=NULL)
      trav=trav->next;
    trav->next=newnode;
  }
}

void addfirst(NODE *temp1)
{
  NODE *trav,*newnode;
  trav=head;
  newnode=createnode(temp1);
  newnode->next=head;
  head=newnode;

}

void insert(NODE*temp1,int n)
{
  NODE *trav,*newnode;
  int i;
  trav=head;
  newnode=createnode(temp1);
  newnode->next=NULL;
  if(n==1)
   addfirst(temp1);
  else
  {
     for(i=1;i<n-1;i++)
      trav=trav->next;
    newnode->next=trav->next;
    trav->next=newnode;
  }
}

void delmid(int n)
{
  NODE *trav,*temp;
  int i;
  trav=head;
  if(head==NULL )
   printf("\nlist is empty");
  else
  {
      for(i=1;i<n-1;i++)
	 trav=trav->next;
      temp=trav->next;
    trav->next=temp->next;
    free(temp);
  }
}

void delfirst()
{
  NODE *temp;
  temp=head;
  if(head==NULL )
   printf("\nlist is empty");
  else
  {
    head=head->next;
    free(temp);
  }
}
void reverse()
{
 NODE *trav,*temp,*p;
 p=head;
 trav=head;
 head=head->next;
 while(temp->next!=NULL)
   {

	temp=head->next;
	head->next=trav;
	trav=head;
	head=temp;
   }
	head->next=trav;
	p->next=NULL;
} */