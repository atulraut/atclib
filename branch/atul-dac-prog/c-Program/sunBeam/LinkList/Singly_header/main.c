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
void init();

struct linklist
{
	int data;
	struct linklist *next;
};

typedef struct linklist NODE;

NODE * head;

NODE * create(int);

int main()
{
	int  ch, val,pos;
	printf("\nEnter to the world of Link List:");
	getch();
	init();
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

void init()
{
	head = create(0);
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
	nn->next = head->next;
	head->next = nn;
	head->data++;
	printf("\nFirst node inserted ");
}
void insert(int val, int pos)
{
	NODE *nn,*trav;
	int i;
	trav = head;
	nn = create(val);
	for(i=1; i<pos; i++)
		trav = trav->next;
	nn->next = trav->next;
	trav->next = nn;
	head->data++;
	printf("\nNode at %d position inserted ",pos);
}
void addlast(int val)
{
	int i;
	NODE *nn ,*trav;
	nn = create(val);
	trav = head;
	for(i=0;i<head->data;i++)
		trav = trav->next;
	trav->next = nn;
	head->data++;
	printf("\nNode at last position inserted ");
}
void delfirst()
{
	NODE *temp;
	temp = head->next;
	head->next = temp->next;
	free(temp);
	head->data--;
	printf("\nFirst Node Deleted ");
}
void deletenode(int pos)
{
	int i;
	NODE *trav,*temp;
	trav = head;
	for(i=1; i<pos; i++)
		trav = trav->next;
	temp = trav->next;
	trav->next = temp->next;
	free(temp);
	head->data--;
	printf("\nNode at %d position deleted ",pos);
}
void dellast(int val)
{
	int i;
	NODE *trav,*temp;
	trav = head;
	for(i=1;i<head->data;i++)
		trav = trav->next;
	temp = trav->next;
	trav->next = NULL;
	free(temp);
	head->data--;
	printf("\nNode at last position inserted ");
}
void display()
{
	int i;
	NODE *trav;
	trav = head->next;
	for(i=0;i<head->data;i++)
	{
		printf("%d->", trav->data);
		trav = trav->next;
	}
	printf("\nTotal Number of nodes are : %d \n",head->data);
}