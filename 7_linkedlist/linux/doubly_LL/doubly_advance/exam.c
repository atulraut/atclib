/***

    Ref : https://stackoverflow.com/questions/10262017/difference-between-list-head-init-and-init-list-head

    LIST_HEAD_INIT is a static initializer, INIT_LIST_HEAD is a function.
    They both initialise a list_head to be empty.

    If you are statically declaring a list_head, you should use
    LIST_HEAD_INIT, eg:

    static struct list_head mylist = LIST_HEAD_INIT(mylist);
    You should use INIT_LIST_HEAD() for a list head that is dynamically
    allocated, usually part of another structure.

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm
    Date: Sun Jul 17 02:08:56 PM PDT 2022
    Folsom, CA.
*/

/*----------------------------------- Header --------------------------------------*/
#include "list.h"
#include "atlist.h"

/* Gloable variables for testing Only */
int j = 0;
int list_cnt = 0;

void at_list_add(void *ptr) {
  struct edge_node* new_node;
  struct edge_list* edge_LIST = (struct edge_list *)ptr;
  struct edge_node* this_edge_node_attributes = (struct edge_node*)edge_LIST->attributes;

  edge_LIST->list_name = (char *)malloc(sizeof(char) * 20 + 1);
  int k = snprintf(edge_LIST->list_name, 20+1, "%s-%d\n", "LIST", list_cnt++);

  for (int i=0; i<5; ++i) {
    new_node = (struct edge_node*)malloc(sizeof(struct edge_node));
    ++j;
    new_node->data = j + i;
    /***
     * Add new node to attributes->list(per edge_node).
     * list_add(struct list_head *new, struct list_head *head);
     */
    list_add(&new_node->list, &this_edge_node_attributes->list);
  }
}

void Display(void *ptr) {
  struct edge_node *new_node;
  struct list_head *pos;
  struct edge_list *edge_LIST = (struct edge_list *)ptr;

  debug ("Enter = %s", edge_LIST->list_name);
  list_for_each(pos, &(edge_LIST->attributes->list)) {
    new_node = list_entry(pos, struct edge_node, list);
    printf("->[%d] ", new_node->data);
  }
  printf ("\n");
  printf("__________________________________________\n\n");
}

void quit(void *ptr) {
  exit(0);
}

void make_DoublyLL(void *ptr) {
  struct edge_list *edge_LIST1 = (struct edge_list*)malloc(sizeof(struct edge_list));
  edge_LIST1->attributes = (struct edge_node*) malloc(sizeof(struct edge_node));
  INIT_LIST_HEAD(&edge_LIST1->attributes->list);

  struct edge_list *edge_LIST2 = (struct edge_list*)malloc(sizeof(struct edge_list));
  edge_LIST2->attributes = (struct edge_node*) malloc(sizeof(struct edge_node));
  INIT_LIST_HEAD(&edge_LIST2->attributes->list);

  at_list_add(edge_LIST1);
  Display(edge_LIST1);
  at_list_add(edge_LIST2);
  Display(edge_LIST2);

  free(edge_LIST1->attributes);
  free(edge_LIST1);
  free(edge_LIST2->attributes);
  free(edge_LIST2);
}
