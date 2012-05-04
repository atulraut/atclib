#include<iostream.h>
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>

class NODE;

class LIST
{
	NODE * head;
public:
	LIST();
	void addfirst(NODE *temp);
	void display();
	void insert(NODE *nn,int pos);
	void addlast(NODE *nn);
	void delfirst();
	void deletenode(int val);
	void dellast();
	void freelist();
};

LIST::LIST()
{
	head = NULL;
}

class NODE
{
	int data;
	NODE *next;
public:
	NODE();
	NODE(int val);
	friend class LIST;
};
NODE::NODE()
{
	data = 0;
	next = NULL;
}
NODE::NODE(int val)
{
	next = new NODE;
	data = val;
}

void LIST::addfirst(NODE *temp)
{
	if(head == NULL)
		head = temp;
	else
	{
		temp->next = head;
		head = temp->next;
	}
	printf("\nFirst node inserted ");
}
void LIST::insert(NODE *nn,int pos)
{
	NODE *trav;
	int i;
	trav = head;
	if(head == NULL || pos == 1)
		this->addfirst(nn);
	else
	{
		for(i=1; i<pos-1; i++)
			trav = trav->next;
		nn->next = trav->next;
		trav->next = nn;
		printf("\nNode at %d position inserted ",pos);
	}
}
void LIST::addlast(NODE *nn)
{
	NODE *trav;
	trav = head;
	if(head == NULL)
		head = nn;
	else
	{
		while(trav->next != NULL)
			trav = trav->next;
		trav->next = nn;
		printf("\nNode at last position inserted ");
	}
}
void LIST::delfirst()
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
void LIST::deletenode(int pos)
{
	int i;
	NODE *trav,*temp;
	if(head == NULL || pos == 1)
	{
		this->delfirst();
		return;
	}
	trav = head;
	for(i=1; i<pos-1; i++)
		trav = trav->next;
	temp = trav->next;
	trav->next = temp->next;
	free(temp);
	printf("\nNode at %d position deleted ",pos);
}
void LIST::dellast()
{
	NODE *trav,*temp;
	trav = head;
	if(head == NULL)
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
void LIST::display()
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
void LIST::freelist()
{
	NODE *temp;
	
	while(head != NULL)
	{
		temp = head;
		head = head->next;
		free(temp);
		head = NULL;
	}
	printf("\nThe List is Freed \n");
} 


int main()
{
	LIST l1;
	NODE *temp;
	temp = new NODE(5);
	l1.addfirst(temp);
	temp = new NODE(10);
	l1.insert(temp,2);
	temp = new NODE(12);
	l1.addlast(temp);
	cout<<endl;
	l1.display();
	cout<<endl;
	return 0;
}
