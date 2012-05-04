#include<stdio.h>
#include<stdlib.h>
#include<conio.h>

struct linklist
{
	int data;
	struct linklist *next;
};

typedef struct linklist NODE;

struct list
{
	NODE * head;
};

typedef struct list LIST;

void init(LIST *p)
{
	p->head = NULL;
}

void display(LIST *);
void addfirst(LIST * , int);
void insert(LIST * , int,int);
void addlast(LIST *,int);
void delfirst(LIST *);
void deletenode(LIST *,int);
void dellast(LIST *);
void reverse(LIST *);
void freelist(LIST *);
NODE * create(int);
void printrev(LIST *,NODE *);

int main()
{
	int  ch, val,pos;
	LIST l1 , l2;
	init(&l1);
	init(&l2);
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
					addfirst(&l1,val);
					break;
			case 2:
					printf("\nEnter the number and position :");
					scanf("%d%d", &val,&pos);
					insert(&l1,val,pos);
					break;
			case 3:
					printf("\nEnter the number : ");
					scanf("%d", &val);
					addlast(&l2,val);
					break;
			case 4:
					delfirst(&l1);
					break;
			case 5:
					printf("\nEnter the position :");
					scanf("%d",&pos);
					deletenode(&l1,pos);
					break;
			case 6:
					dellast(&l1);
					break;
			case 7:
					display(&l1);
					break;
			case 8:
					reverse(&l1);
					break;
			case 9:
					printrev(&l2,l2.head);
					break;
			case 10:
					freelist(&l1);
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
void addfirst(LIST *p1, int val)
{
	NODE *nn;
	nn = create(val);
	if(p1->head == NULL)
		p1->head = nn;
	else
	{
		nn->next = p1->head;
		p1->head = nn;
	}
	printf("\nFirst node inserted ");
}
void insert(LIST *p1,int val, int pos)
{
	NODE *nn,*trav;
	int i;
	trav = p1->head;
	nn = create(val);
	if(p1->head == NULL || pos == 1)
		addfirst(p1,val);
	else
	{
		for(i=1; i<pos-1; i++)
			trav = trav->next;
		nn->next = trav->next;
		trav->next = nn;
		printf("\nNode at %d position inserted ",pos);
	}
}
void addlast(LIST *p1, int val)
{
	NODE *nn ,*trav;
	nn = create(val);
	trav = p1->head;
	if(p1->head == NULL)
		p1->head = nn;
	else
	{
		while(trav->next != NULL)
			trav = trav->next;
		trav->next = nn;
		printf("\nNode at last position inserted ");
	}
}
void delfirst(LIST *p1)
{
	NODE *temp;
	if(p1->head == NULL)
	{
		printf("\nList is empty ");
		return;
	}
	temp = p1->head;
	p1->head = p1->head->next;
	free(temp);
	printf("\nFirst Node Deleted ");
}
void deletenode(LIST *p1, int pos)
{
	int i;
	NODE *trav,*temp;
	if(p1->head == NULL || pos == 1)
	{
		delfirst(p1);
		return;
	}
	trav = p1->head;
	for(i=1; i<pos-1; i++)
		trav = trav->next;
	temp = trav->next;
	trav->next = temp->next;
	free(temp);
	printf("\nNode at %d position deleted ",pos);
}
void dellast(LIST *p1)
{
	NODE *trav,*temp;
	trav = p1->head;
	if(p1->head == NULL)
		printf("\nList is empty ");
	else
	{
		while(trav->next->next != NULL)
			trav = trav->next;
		temp = trav->next;
		trav->next = NULL;
		free(temp);
		printf("\nNode at last position inserted ");
	}
}
void display(LIST *p1)
{
	NODE *trav;
	trav = p1->head;
	if(p1->head == NULL)
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

void reverse(LIST *p1)
{
	NODE * temp,*trav;
	temp = p1->head;
	p1->head = NULL;
	while(temp != NULL)
	{
		trav = temp->next;
		temp->next = p1->head;
		p1->head = temp;
		temp = trav;
	}
}

void printrev(LIST *p1, NODE * trav)
{
	if(trav == NULL)
		return;
	printrev(p1,trav->next);
	printf("->%d",trav->data);
}

void freelist(LIST *p1)
{
	NODE *temp;
	
	while(p1->head != NULL)
	{
		temp = p1->head;
		p1->head = p1->head->next;
		free(temp);
	}
	printf("\nThe List is Freed \n");
}