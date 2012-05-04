#include<stdio.h>
#include<stdlib.h>
#include<conio.h>

void display();
void addfirst(int);
void insert(int,int);
void addlast(int);
void delfirst();
void deletenode(int);
void dellast();

struct linklist
{
	int data;
	struct linklist *next;
};

typedef struct linklist NODE;
NODE *head = NULL;

NODE *tail = NULL;

NODE * create(int);

int main()

{
	int  ch, val,pos;
	printf("\nEnter to the world of Link List:");
	getch();
	while(1)
	{
		system("cls");
		printf("\n0 >Eixt\n1 >AddFirst \n2 >Insert \n3 >AddLast \n4 >DeleteFirst \n5 >DeleteNode \n6 >DeleteLast\n7 >Display :\n");
		scanf("%d", &ch);
		switch(ch)
		{
			case 0:
					exit(0);
			case 1:
					printf("\nEnter the number : ");
					scanf("%d", &val);
					addfirst(val);
					break;
			case 2:
					printf("\nEnter the number and position :");
					scanf("%d%d", &val,&pos);
					insert(val,pos);
					break;
			case 3:
					printf("\nEnter the number : ");
					scanf("%d", &val);
					addlast(val);
					break;
			case 4:
					delfirst();
					break;
			case 5:
					printf("\nEnter the position :");
					scanf("%d",&pos);
					deletenode(pos);
					break;
			case 6:
					dellast();
					break;
			case 7:
					display();
					break;
			default :
					printf("\nEnter the correct choice ");
		}
		getch();
	}
	return 0;
}
NODE * create(int val)
{

	NODE *nn;
	nn = (NODE *)malloc(sizeof(NODE));
	nn->data = val;
	nn->next = NULL;
	return nn;
}

void addfirst(int val)
{
	NODE *nn;
	nn = create(val);
	if(head == NULL)
	{
		head = nn;
		tail = head;
	}
	else
	{
		nn->next = head;
		head = nn;
	}
	printf("\nFirst node inserted ");
}
void insert(int val, int pos)
{
	NODE *nn,*trav;
	int i;
	trav = head;
	nn = create(val);
	if(head == NULL || pos == 1)
		addfirst(val);
	else
	{
		for(i=1; i<pos-1; i++)
			trav = trav->next;
		nn->next = trav->next;
		trav->next = nn;
		if(trav->next == NULL)
			tail = nn;
		printf("\nNode at %d position inserted ",pos);
	}
}
void addlast(int val)
{
	NODE *nn;
	nn = create(val);
	if(head == NULL)
	{
		head = nn;
		tail = head;
	}
	else
	{
		tail ->next = nn;
		tail = nn;
	}
}
void delfirst()
{
	NODE *temp;
	if(head == NULL)
	{
		printf("\nList is empty ");
		return;
	}
	temp = head;
	head = head->next;
	free(temp);
	printf("\nFirst Node Deleted ");
}
void deletenode(int pos)
{
	int i;
	NODE *trav,*temp;
	if(head == NULL || pos == 1)
	{
		delfirst();
		return;
	}
	trav = head;
	for(i=1; i<pos-1; i++)
		trav = trav->next;
	if(trav->next->next == NULL)
	{
		free(tail);
		tail = trav;
		trav->next = NULL;
	}
	else
	{
		temp = trav->next;
		trav->next = temp->next;
		free(temp);
	}
	printf("\nNode at %d position deleted ",pos);
}
void dellast(int val)
{
	NODE *trav;
	trav = head;
	if(head == NULL)
		printf("\nList is empty ");
	else
	{
		if(trav->next == NULL)
		{
			free(trav);
			head = tail = NULL;
		}
		else
		{
			while(trav->next->next != NULL)
				trav = trav->next;
			trav->next = NULL;
			free(tail);
			tail = trav;
		}

		printf("\nNode at last position deleted ");
	}
}
void display()
{
	NODE *trav;
	trav = head;
	if(head == NULL)
		printf("The node is empty :");
	else
	{
		while(trav != NULL)
		{
			printf("%d->", trav->data);
			trav = trav->next;
		}
	}
}