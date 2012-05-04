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
void reverse();
void freelist();

struct linklist
{
	int data;
	struct linklist *next;
	struct linklist *prev;
};

typedef struct linklist NODE;
NODE *head = NULL;

NODE * create(int);
void printrev(NODE *);

int main()
{
	int  ch, val,pos;
	printf("\nEnter to the world of Link List:");
	getch();
	while(1)
	{
		system("cls");
		printf("\n0 >Eixt\n1 >AddFirst \n2 >Insert \n3 >AddLast \n4 >DeleteFirst \n5 >DeleteNode \n6 >DeleteLast\n7 >Display \n8 >Reverse \n9 >Print Reversly \n10 >Freelist \n");
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
		/*	case 8:
					reverse();
					break;
			case 9:
					printrev(head->next);
					break;
			case 10:
					freelist();
					break;*/
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
	nn->next = nn;
	return nn;
}
void addfirst(int val)
{
	NODE *nn;
	nn = create(val);
	if(head == NULL)
		head = nn;
	else
	{
		nn->next = head->next;
		head->next = nn;
	}
	printf("\nFirst node inserted \n");
}
void insert(int val, int pos)
{
	NODE *nn,*trav;
	int i;

	nn = create(val);
	if(head == NULL || pos == 1)
		addfirst(val);
	else
	{
		trav = head->next;
		for(i=1; i<pos-1; i++)
			trav = trav->next;
		nn->next = trav->next;
		trav->next = nn;
		if(trav == head)
			head = nn;
		printf("\nNode at %d position inserted ",pos);
	}
}
void addlast(int val)
{
	NODE *nn ,*trav;
	nn = create(val);
	trav = head;
	if(head == NULL)
		head = nn;
	else
	{
		nn->next = head->next;
		head->next = nn;
		head = nn;
		printf("\nNode at last position inserted ");
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
	temp = head->next;
	head->next = temp->next;
	free(temp);
	if(temp == head)
		head = NULL;
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
	trav = head->next;
	for(i=1; i<pos-1; i++)
		trav = trav->next;
	temp = trav->next;
	if(temp == head)
		head = trav;
	trav->next = temp->next;
	free(temp);
	printf("\nNode at %d position deleted ",pos);
}
void dellast(int val)
{
	NODE *trav;
	if(head == NULL)
		printf("\nList is empty ");
	else
	{
		trav = head->next;
		while(trav->next != head)
			trav = trav->next;
		trav->next = head->next;
		if(head == trav)
			trav = NULL;
		free(head);
		head = trav;
		printf("\nNode at last position inserted ");
	}
}
void display()
{
	NODE *trav;

	if(head == NULL)
		printf("\nList is empty ");
	else
	{
		trav = head->next;
		while(trav != head)
		{
			printf("%d->", trav->data);
			trav = trav->next;
		}
		printf("%d->", trav->data);
	}
}

void reverse()
{
	NODE * temp,*trav;
	temp = head;
	head = NULL;
	while(temp != NULL)
	{
		trav = temp->next;
		temp->next = head;
		head = temp;
		temp = trav;
	}
}

void printrev(NODE * trav)
{
	if(trav == head)
		return;
	printrev(trav->next);
	printf("->%d",trav->data);
}

void freelist()
{
	NODE *temp;

	while(head != NULL)
	{
		temp = head;
		head = head->next;
		free(temp);
	}
	printf("\nThe List is Freed \n");
}
