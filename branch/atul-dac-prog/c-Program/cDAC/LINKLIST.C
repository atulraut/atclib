#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
typedef struct node
{
	int data;
	struct node *next;
}NODE;

NODE *head=NULL;
NODE* creatnode(int val)
{
	NODE *newnode=(NODE*)malloc(sizeof(NODE));
	newnode->data=val;
	newnode->next=NULL;
	return newnode;
}

void addfirst(int val)
{
	NODE *newnode=creatnode(val);
	newnode->next=head;
	head=newnode;
}

void display()
{
	NODE *trav=head;
	if(head==NULL)
	printf("\nThe loop is empty");
	while(trav!=NULL)
	{
		  printf("\t%d",trav->data);
		  trav=  trav->next;
	}
}

void addlast(int val)
{
	 NODE  *newnode=creatnode(val);
	 NODE *trav;
	 if(head==NULL)
	 head=newnode;
	 else
	 {
		 trav=head;
		 while(trav->next!=NULL)
		 trav=trav->next;
		 trav->next=newnode;
	  }

}

void insert(int val,int pos)
{
	  NODE *newnode =creatnode(val);
	  NODE *trav=head;
	  int i;
	  if(head==NULL|| pos==1)
	  {
		  newnode->next=head;
		  head=newnode;
	  }
	  else
	  {
		   for(i=1;i<pos-1;i++)
		   trav=trav->next;
		   newnode->next=trav->next;
		   trav->next=newnode;
	  }
}

int delfirst()
{
	NODE *temp=head;
	int val;
	if(head==NULL)
	printf("list is empty");
	else
	{
	      head= head->next;
	      val= temp->data;
	      free(temp);
	}
	       return val;
}

void del(int pos)
{
      NODE *trav=head,*temp;
      int i;
      if(head==NULL||pos==1)
      printf("list is empty");
      else
      {
		for(i=1;i<pos-1;i++)
		trav=trav->next;
		temp=trav->next;
		trav->next=temp->next;
		free(temp);
      }
}



void main()
{
	int num,ch,pos;
	clrscr();
	do
	{
	    printf("\n0.exit\n1. display \n2.addfirst\n3.addlast\n4.insert\n5.dellfirst\n6.dell\n");
	    printf("\nenter the  choice");
	    scanf("%d",&ch);
	    switch(ch)
		{
		 case 0:
			exit(0);
			break;
		 case 1:
			display();
			break;

		 case 2:
			printf("Enter the num");
			scanf("%d",&num);
			addfirst(num);
			break;
		case 3:

			printf("Ener the num");
			scanf("%d",&num);
			addlast(num);
			break;
		case 4:
			printf("Ener the num& position");
			scanf("%d %d",&num,&pos);
			insert(num,pos);
			break;
		case 5:
			num=delfirst();
			printf("deleted num =%d",num);
			break;
		case 6:
			printf("Enter rhe position");
			scanf("%d",&pos);
			del(pos);
			break;
		}
	     }  while(ch!=0);

   }