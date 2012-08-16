/*
* http://compsci.ca/v3/viewtopic.php?t=14254
***/

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  void *_data;
  struct node *_next;

  void *(*data) (void *obj);
  void *(*next) (void *obj);
  void *(*set) (void *obj, void *data);
} lnode;

/*
static void *get_data (void *obj);
static void *move_data (void *obj);
static void *set_data (void *obj);
static lnode *new_node(void *data, lnode *init_next);
*/
