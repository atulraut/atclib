#include <stdio.h>
#include "list.h"

/* Function declaration */
list_t list_init () {
  list_t atclib_list;

  /* Allocate, initialize & return a new list */
  atclib_list = (list_t) malloc (sizeof (struct list));
  if (atclib_list == NULL)
    return;
  atclib_list->size = 0;
  atclib_list->pFirst = NULL;
  atclib_list->pLast = NULL;
  atclib_list->pCurr = NULL;
  return (atclib_list);
}

list_element_t create_Element (void *_data, size_t len)
{
  list_element_t new;
  new = (list_element_t) malloc (sizeof (struct list_element));
  if (new == NULL)
    return (NULL);

  /* Allocate storage for the data only if requested; i.e. if len > 0.
  * Then either copy the data or just the reference into the node.*/ 
  if (len > 0) {
      new->data = (char *) malloc (len);
      if (new->data == NULL)
{
  free (new);
  return (NULL);
}
  } else
     new->data = (char *) _data;
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

int print_element (char *input, char *curr) {
  printf ("-->%d", *(int *) curr);
  return (1);
}


/*** Routine to print a list of integers, using the traversal function.
	In this example, we send NULL for the second parameter, which might be
* used to specify an element to search for.
*/
  print_list (list) {
  list * list;
  printf ("List:");
  if (list_empty (list))
    printf (" (empty).\n");
  else {
      list_traverse (list, (char *) 0, print_element,
      (LIST_FRNT | LIST_FORW | LIST_SAVE));
      printf (".\n");
  }
}

list_status_t list_traverse (list_t list, void *data,
      list_traverse_func_t func, int opts)
{
  list_element_t lp;
  int status, rc;

  /* Traverse the list according to opts, calling func at each element,
     * until func returns 0 or the extent of the list is reached.  We return
     * 0 if the list is empty, 2 if we tried to go beyond the extent of the
     * list, and 1 otherwise.  We may or may not affect the current element
     * pointer.
     */
    if (list->front == NULL)
      return (LIST_EMPTY);

    /* Decide where to start. */
    if ((opts & LIST_CURR) == LIST_CURR) {
      lp = list->curr;
    }

  else if ((opts & LIST_REAR) == LIST_REAR) {
      lp = list->rear;
  } else {
      lp = list->front;
    }

    /* Now decide if to update the current element pointer. */
    if ((opts & LIST_ALTR) == LIST_ALTR)
    list->curr = lp;

    /* Now go until 0 is returned or we hit the extent of the list. */
    rc = LIST_OK;
  status = TRUE;
  while (status)
    {
     status = (*func) (data, lp->data);
     if (status) {
  if ((((opts & LIST_BACK) ==
 LIST_BACK) ? (lp->prev) : (lp->next)) == NULL)
    {

/* Tried to go beyond extent of list. */
status = FALSE;
      rc = LIST_EXTENT;
    }

  else
    {

/* Decide where to go next. */
lp =
(((opts & LIST_BACK) == LIST_BACK) ? (lp->prev) : (lp->next));

/* Now decide if to update the current element pointer. */
if ((opts & LIST_ALTR) == LIST_ALTR)
list->curr = lp;
   }
}
    }
  return (rc);
}

void m_Free_List () {
}
