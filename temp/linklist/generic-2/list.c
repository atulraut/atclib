#include <stdio.h>
#include "list.h"

/* Function declaration */
list_t list_init () {
  list_t atclib_list;

  /* Allocate, initialize & return a new list */
  atclib_list = (list_t)malloc(sizeof(struct list));
  if (atclib_list == NULL)
    return;
  atclib_list->size = 0;
  atclib_list->pFirst = NULL;
  atclib_list->pLast  = NULL;
  atclib_list->pCurr  = NULL;
  return (atclib_list);
} 

list_element_t create_Element (void *_data, size_t len) {
  list_element_t new;
  new = (list_element_t)malloc(sizeof(struct list_element));
  if (new == NULL)
    return(NULL);
  /* Allocate storage for the data only if requested; i.e. if len > 0.
   * Then either copy the data or just the reference into the node.*/
  if (len > 0) {
    new->data = (char *) malloc (len);
    if (new->data == NULL) {
      free(new);
      return (NULL);
    }
  } else
    new->data = (char *)_data;
  return new;
}

int m_Add (list_t list, void *data, int len) {
  list_element_t new = NULL;
  new = create_Element (data, len);
  if (new == NULL)
    return (NULL);
  /* Now insert the element after the current, considering the cases:
       *    1) List is empty
       *    2) Inserting at last
       *    3) Otherwise
       * We handle them directly, in order.
  */
  /* 1) List empty */
  if (list == NULL) {
    new->next = new->prev = NULL;
    list->pFirst = list->pLast = list->pCurr = new;
  }
  if (list == list->pFirst) {

  }
  /* 2) Inserting at last */
  if (list == list->pLast) {

  }
}

void m_Display () {

}

int print_element (char *input, char*curr) {
  printf ("-->%d", *(int *) curr);
  return (1);
}

void m_Free_List () {

}
