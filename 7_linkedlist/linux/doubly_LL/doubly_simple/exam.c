/***

    Ref : https://stackoverflow.com/questions/10262017/difference-between-list-head-init-and-init-list-head

    LIST_HEAD_INIT is a static initializer, INIT_LIST_HEAD is a function.
    They both initialise a list_head to be empty.

    If you are statically declaring a list_head, you should use
    LIST_HEAD_INIT, eg:

    static struct list_head mylist = LIST_HEAD_INIT(mylist);
    You should use INIT_LIST_HEAD() for a list head that is dynamically
    allocated, usually part of another structure. T

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm
    Date: Sat Jul 16 11:59:13 PM PDT 2022
    Folsom, CA.
*/

/*----------------------------------- Header --------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>
#include <string.h>  /* malloc */
#include <stdbool.h>
#include <math.h>
#include <assert.h>
#include <stdint.h> /* uint32_t */
#include <unistd.h> /* sleep */
#include "list.h"
/*----------------------------------- Micro --------------------------------------*/
#define debug(str,args...) printf("[%s] L=%d :"str"\n", __func__, __LINE__, ##args)
#define atsizeof(object) (char *)(&object+1) - (char*)(&object)
#define arrsz(x)  (sizeof(x) / sizeof((x)[0]))
#define max(a,b)		\
  ({ __typeof__ (a) _a = (a);	\
    __typeof__ (b) _b = (b);	\
    _a > _b ? _a : _b; })
#define min(a,b)		\
  ({ __typeof__ (a) _a = (a);	\
    __typeof__ (b) _b = (b);	\
    _a < _b ? _a : _b; })
/*----------------------------------- Micro --------------------------------------*/

struct edge_node {
  int d;                   // data
  struct list_head list;   // *prev, *next
};

struct edge_list {
  struct edge_node *attributes;
};

int main () {
  int i;
  struct list_head *pos;
  struct edge_node *new_node;
  struct edge_list *edge_LIST = (struct edge_list*)malloc(sizeof(struct edge_list));

  debug("Enter! \n");
  edge_LIST->attributes = (struct edge_node*) malloc(sizeof(struct edge_node));

  /* They both initialise a list_head to be empty! */
  /* LIST_HEAD_INIT is a static initializer */
  INIT_LIST_HEAD(&edge_LIST->attributes->list);
  /**
     INIT_LIST_HEAD is a function.
     static struct list_head mylist = LIST_HEAD_INIT(mylist);
   */
  for (i=0; i<5; ++i) {
    new_node = (struct edge_node*)malloc(sizeof(struct edge_node));
    new_node->d = i;
    /***
     * Add new node to attributes->list(per edge_node).
     * list_add(struct list_head *new, struct list_head *head);
    */
    list_add(&new_node->list, &edge_LIST->attributes->list);
  }

  list_for_each(pos, &(edge_LIST->attributes->list)) {
    new_node = list_entry(pos, struct edge_node, list);
    printf("->[%d] ", new_node->d);
  }
  printf ("\n");
  return 0;
}
