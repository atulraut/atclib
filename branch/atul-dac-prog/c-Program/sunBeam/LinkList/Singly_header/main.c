/*
* Aim : Singly Linked List.
* Date : Monday, March 21 2014 10:38 PM
* Place: SanJose, CA, US
* Reference : http://cslibrary.stanford.edu/105/LinkedListProblems.pdf 
* By : Atul R. Raut
* 
***/
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include <assert.h>

int getNth (int);
void display();
void addfirst(int);
void insert(int,int);
void addlast(int);
void delfirst();
void deletenode(int);
void dellast();
void init();

struct linklist {
  int data;
  struct linklist *next;
};

typedef struct linklist NODE;

NODE * head;

NODE * create(int);
int getPop(NODE **this);
int getCount (NODE *, int);
int getCount (NODE *, int);
int GetNth(NODE *, int) ; // University Implementation
void deleteList(NODE **headRef);
void SortedInsert2(int);

int main() {
  int  ch, val,pos;
  printf("\nEnter to the world of Link List:");
  getch();
  init();
  while(1) {
    system("cls");
    printf("\n0 >Eixt\n1 >AddFirst \n2 >Insert \n3 >AddLast \n4 >DeleteFirst \n5 >DeleteNode \n6 >DeleteLast\n7 >Display :   \
                        \n8 >getNth \n9 >getNTH \n10 >DeleteList \n11 >getCount \n12 >getPop \n13 > SortedInsert \
                        \n14 > \n");
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
      case 8:
	printf("\nEnter the position :");
	scanf("%d", &pos);
	printf ("Pos[%d] = [%d]\n", pos, getNth(pos));
	break;
      case 9:
	printf("\nEnter the position :");
	scanf("%d", &pos);
	printf ("Pos[%d] = [%d]\n", pos, GetNth(head, pos));
	break;
      case 10:
	deleteList(&head);
	break;
      case 11:
	printf("\nEnter the position :");
	scanf("%d", &pos);
	printf ("::==> [%d] occur [%d] time\n", pos, getCount(head, pos));
	break;
      case 12:		
	printf ("data = [%d] \n", getPop(&head));
	break;
      case 13:
	printf("\nEnter the data to be inserted :--> ");
	scanf("%d", &pos);
	SortedInsert2(pos);
      default :
	printf("\nEnter the correct choice ");
      }
    getch();
  }
  return 0;
}

void init() {
  // Do Nothing
}

NODE * create(int val) {
  NODE *nn;
  nn = (NODE *)malloc(sizeof(NODE));
  nn->data = val;
  nn->next = NULL;
  return nn;
}
void addfirst(int val) {
  NODE *nn;
  NODE *trav;
  nn = create(val);
  if (NULL == head) {	 
    printf ("Got It..\n");
    head = nn;
    nn->next = NULL;
  } else {
    printf ("Second note head\n");
    nn->next = head;
    head = nn;
  }
  printf("\nFirst node inserted ");
}
void insert(int val, int pos) {
  NODE *nn = NULL;
  NODE *trav = NULL;
  NODE *temp = NULL;
  int i;
  trav = head;
  nn = create(val);
  if (pos < 0) {
    printf ("Enter correnct Position !\n");
    return;
  }
  if (NULL == head || pos <= 1) {
    addfirst(val);
  } else {
    for(i=1; i<pos-1; i++) // 2<2 --> false, wll break loop
      trav = trav->next;
    nn->next = trav->next;
    trav->next = nn;
  }
  printf("\nNode at %d position inserted ",pos);
}
void addlast(int val) {
  int i;
  NODE *nn = NULL;
  NODE *trav = NULL;
  nn = create(val);
  if (NULL == head) {	 
    addfirst(val);
  } else {
    trav = head;
    while (trav->next != NULL)
      trav = trav->next;
    trav->next = nn;
  }
  printf("\nNode at last position inserted ");
}
void delfirst() {
  NODE *temp;
  temp = NULL;
  if (NULL == head) {
    printf ("\nreturning..list is empty\n");
    return;
  }
  temp = head;
  head = temp->next;
  temp->next = NULL;
  free(temp);
  temp = NULL;
  printf("\nFirst Node Deleted ");
}
void deletenode(int pos) {
  int i;
  NODE *trav,*temp;
  if (NULL == head) {
    printf ("\nreturning..list is empty\n");
    return;
  }
  trav = head;
  if (pos <= 1)
    delfirst();
  else {
    for(i=1; i<pos-1; i++)
      trav = trav->next;
    temp = trav->next;
    trav->next = temp->next;
    free(temp);
    temp = NULL;
  }
  printf("\nNode at %d position deleted ",pos);
}
void dellast(int val) {
  int i;
  NODE *trav,*temp;
  if (NULL == head) {
    printf ("\nreturning..list is empty\n");
    return;
  }
  trav = head;
  if(trav->next == NULL) {
    delfirst();
  } else {
    while (trav->next->next != NULL)
      trav = trav->next;
    temp = trav->next;
    trav->next = NULL;
    free(temp);
    temp = NULL;
  }
  printf("\nNode at last position inserted ");
}

int getNth (int pos) {
  int i=0;
  NODE *temp = NULL;
  if (NULL == head) {
    printf ("\nreturning..list is empty\n");
    return;
  }
  if (0 == pos)
    return head->data;
  temp = head;
  for (i=1; i<=pos; i++)
    temp = temp->next;
  return temp->data;
}

void display(){
  int i;
  NODE *trav;
  trav = head;
  if (NULL == head) {
    printf ("\nreturning..list is empty\n");
    return;
  }
  while (trav != NULL) {
    printf ("->[%d]", trav->data);
    trav = trav->next;
  }
  printf("\nTotal Number of nodes are : %d \n",head->data);
}

/***
 * 1. listCount : Write a getCount() function that counts the number of times a given int occurs in a list. The
 *code for this has the classic list traversal structure as demonstrated in Length().
 */
int getCount (NODE *thisNodePtr, int searchFOR) {
  NODE *current = thisNodePtr;
  int count = 0;
  if (NULL == head) {
    printf ("Empty link list, returning..\n");
    return 0;
  }
    
  while(NULL != current) {
    if (searchFOR == current->data)
      count++;
    current = current->next;
  }
  return count;
}

/***
 *2  GetNth() : Write a GetNth() function that takes a linked list and an integer index and returns the data
 * value stored in the node at that index position. 
 */
int GetNth(NODE* thisNodePtr, int index) {
  NODE* current = thisNodePtr;
  int count = 0; // the index of the node we're currently looking at
  if (NULL == head) {
    printf ("\nreturning..list is empty\n");
    return;
  }

  while (current != NULL) {
    if (count == index) 
      return(current->data);
    count++;
    current = current->next;
  }
  assert(0); // if we get to this line, the caller was asking
  // for a non-existent element so we assert fail.
}

/*** 
 * 3  DeleteList() : Write a function DeleteList() that takes a list, deallocates all of its memory and sets its
 *head pointer to NULL (the empty list).
 */
void deleteList(NODE **headRef) {
  NODE *current = *headRef;
  if (current == NULL){
    printf ("\nreturning..list is empty\n");
    return;
  }
  NODE *temp = NULL;
  while(current != NULL) {
    temp = current->next;
    free(current);
    current = temp;
  }
  *headRef = NULL;  // Again, deref headRef to affect the real head back in the caller.
  printf ("List is Empty !\n");
}
/***
 * 4  getPop():Write a Pop() function that is the inverse of Push(). Pop() takes a non-empty list, deletes
 * the head node, and returns the head node's data
 * head = createList();// build {1, 2, 3}
 * int a = Pop(&head); // deletes "1" node and returns 1
 * int b = Pop(&head); // deletes "2" node and returns 2
 * Solution : Extract the data from the head node, delete the node, advance the head pointer to point at
 * the next node in line. Uses a reference parameter since it changes the head pointer.
 */
int getPop(NODE **headRef) {
  int thisData;
  NODE *current = NULL;
  if (head == NULL){
    printf ("\nreturning..list is empty\n");
    return;
  }
  /*  current = *headRef;
      thisData = current->data;
      *headRef = current->next;
      current->next = NULL;
      free(current);
      current = NULL;
  */
  current = head;//->next;
  thisData = current->data;
  //printf ("thisData = %d \n", thisData);
  head = current->next;
  current->next = NULL;
  free(current);
  current = NULL;
  return (thisData);
}

/***
* 6  SortedInsert() : Write a SortedInsert() function which given a list that is sorted in increasing order, and a
* single node, inserts the node into the correct sorted position in the list. While Push()
* allocates a new node to add to the list, SortedInsert() takes an existing node, and just
* rearranges pointers to insert it into the list. There are many possible solutions to this problem.
* void SortedInsert()
*/
void SortedInsert2(int val) {
  NODE *nn = NULL;
  NODE *trav = NULL;
  nn = create(val);
  // Special case for the head end
  if(head == NULL || head->data >= nn->data) {
    nn->next = head;
    head = nn;
  }else {
    trav = head;
    // Locate the node before the point of insertion
    while (trav->next != NULL && trav->next->data < nn->data) {
      trav = trav->next;
    }
    nn->next = trav->next;
    trav->next = nn;
  }
}


