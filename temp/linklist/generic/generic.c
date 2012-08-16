#include <assert.h>
#include "list.h"

int main () {
  
    printf ("\nlist is NULL\n");
}

static void *get_data (void *obj) {
  return ((lnode *)obj)->_data;
}

static void *move_next (void *obj) {
  return ((lnode *)obj)->_next;
}

static void *set_data (void *obj) {
  lnode *node = obj;
  void *old_data = node->_data;

  node->_data = data;
  return old_data;
}

static lnode *new_node(void *data, lnode *init_next) {
  lnode *nn = malloc (sizeof (*nn));
  if (nn == NULL)
    return 0;
  nn->_data = data;
  nn->_next = init_next;
  nn->get = get_data;
  nn->next = move_next;
  nn->set = set_data;
  
  return nn;
}

