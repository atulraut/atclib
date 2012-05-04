/*IN THIS PROGRAM WE ADD THE NUMBER BY ADDLAST FUN. IN L.L. AND DISPLAY IT
 AND WITH THE HELP OF SORTING FUN. WE ARRANGE IT IN ASSENDING ORDER*/



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
void sorting()
{
	NODE *trav=head;
	NODE *temp;
	int n1,n2;

	while(trav!=NULL)
	{
		temp=trav->next;
		while(temp!=NULL)
		{
			n1=trav->data;
			n2=temp->data;
			if(n1>n2)
			{
				trav->data=n2;
				temp->data=n1;
			}
			temp=temp->next;
		}
		trav=trav->next;
	}

}




void main()
{
	int num,ch,pos;
	clrscr();
	do
	{
	    printf("\n0.exit\n1. display \n2.addlast\n3.swaping\n");
	    printf("\nenter the  choice");
	    scanf("%d",&ch);
	    switch(ch)
		{
		 case 0:/*exit*/
			exit(0);
			break;
		 case 1:/*display*/
			display();
			break;

		case 2:/*addlast*/
			printf("Ener the num");
			scanf("%d",&num);
			addlast(num);
			break;
		case 3:/*sorting*/
			sorting();
			break;
		}
	     }  while(ch!=0);

   }