/***
    Double Linked List

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Tue Sep 22 21:09:51 PDT 2026
    Folsom, CA.
 */

/*----------------------------------- Header --------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h> // va_arg
#include <ctype.h>
#include <limits.h>
#include <string.h>  /* malloc */
#include <stdbool.h>
#include <math.h>
#include <assert.h>
#include <stdint.h> /* uint32_t */
#include <unistd.h> /* sleep */

#define debug(str,args...) printf("L=[%d][%s]->[%s] :| "str"\n",__LINE__,__FILE__, __func__, ##args)

struct node {
  int data;
  struct node* prev;
  struct node* next;
};

struct list {
  struct node* head;
};

struct list* init_list(struct list* ll) {
  ll = malloc(sizeof(struct list));
  if(NULL == ll)
    return NULL;
  ll->head = NULL;
  return ll;
}

struct node* create_node(int data) {
  struct node* nn = malloc(sizeof(struct node));
  nn->data = data;
  nn->prev = NULL;
  nn->next = NULL;
  return nn;
}

void m_add(struct list* ll, int val) {
  struct node* nn = create_node(val);
  if(ll->head == NULL) {
    ll->head = nn;
    nn->next = ll->head;
    nn->prev = ll->head;;
  } else {
    struct node* trav = ll->head;
    while(trav->next != ll->head)
      trav = trav->next;
    trav->next = nn;
    nn->prev = trav;
    nn->next = ll->head;
   }
}

void m_free(struct list* ll) {
  struct node* trav = ll->head;
  struct node* temp = NULL;
  if(NULL != ll->head) {
    debug("Empty list!");
    return;
  }
  while(trav != NULL) {
    if(trav->next == ll->head) {
      trav->next = NULL;
      trav->prev = NULL;
      free(trav);
      trav = NULL;
    } else {
      temp = trav;
      trav = trav->next;
      temp->next = NULL;
      temp->prev = NULL;
      free(temp);
      temp = NULL;
    }
    ll->head = NULL;
    free(ll);
    ll = NULL;
  }
}

void m_reverse_linkedlist(struct list* ll) {
  struct node* trav = ll->head;
  struct node* temp = ll->head;
  struct node* save = ll->head;
  if(NULL == ll->head) {
    debug("Empty ll!");
    return;
  }
  while(trav->next != ll->head)
    trav = trav->next;
  ll->head = trav;

  while(trav != save) {
    debug("save =[%d] trav = [%d] temp = [%d] head = [%d]",save->data, trav->data,  temp->data, ll->head->data);
    trav = temp->next;
    temp->next = ll->head;
    temp->prev = trav;
    ll->head = temp;
    temp = trav;
  }

}

void m_display(struct list* ll) {
  struct node* trav = ll->head;
  while(trav->next != ll->head) {
    debug("->[%d]", trav->data);
    trav = trav->next;
  }
  debug("->[%d]", trav->data);
}

void test() {

  debug("Welcome to Double Linked List!");
  struct list l;
  struct list* ll = init_list(&l);
  m_add(ll, 10);
  m_add(ll, 20);
  m_add(ll, 30);
  //  m_add(ll, 40);
  //  m_add(ll, 50);
  m_display(ll);
  debug("*** Reverser Linked List! ***");
  m_reverse_linkedlist(ll);
  m_display(ll);
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**
   L=[130][doubly-circular-ll-IVI.c]->[test] :| Welcome to Double Linked List!
   L=[122][doubly-circular-ll-IVI.c]->[m_display] :| ->[10]
   L=[122][doubly-circular-ll-IVI.c]->[m_display] :| ->[20]
   L=[125][doubly-circular-ll-IVI.c]->[m_display] :| ->[30]
   L=[139][doubly-circular-ll-IVI.c]->[test] :| *** Reverser Linked List! ***
   L=[109][doubly-circular-ll-IVI.c]->[m_reverse_linkedlist] :| save =[10] trav = [30] temp = [10] head = [30]
   L=[109][doubly-circular-ll-IVI.c]->[m_reverse_linkedlist] :| save =[10] trav = [20] temp = [20] head = [10]
   L=[109][doubly-circular-ll-IVI.c]->[m_reverse_linkedlist] :| save =[10] trav = [30] temp = [30] head = [20]
   L=[122][doubly-circular-ll-IVI.c]->[m_display] :| ->[30]
   L=[122][doubly-circular-ll-IVI.c]->[m_display] :| ->[20]
   L=[125][doubly-circular-ll-IVI.c]->[m_display] :| ->[10]
**/
