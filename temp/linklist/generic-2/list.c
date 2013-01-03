#include <stdio.h>
#include "list.h"

/* Function declaration */
list_t list_init () {
  
  /* Allocate, initialize & return a new list */
  atclib_list = (list_t) malloc (sizeof (struct list));
  //  if (atclib_list == NULL)
  //  return;
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
   print_list (atclib_list);
   int rc;
   rc = list_traverse(atclib_list, (char *) 0, print_element, LIST_SAVE);
   switch (rc) {
      case LIST_EMPTY:
         printf("(empty).\n");
         break;
      case LIST_OK:
         printf(".\n");
         break;
      case LIST_EXTENT:
         printf(". (extent reached)\n");
         break;
      default:
         printf("%c not recognized.  Returning to main menu.\n");
  }
	
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
    if (list->pFirst == NULL)
      return (LIST_EMPTY);

    /* Decide where to start. */
    if ((opts & LIST_CURR) == LIST_CURR) {
      lp = list->pCurr;
    }

  else if ((opts & LIST_REAR) == LIST_REAR) {
      lp = list->pLast;
  } else {
      lp = list->pFirst;
    }

    /* Now decide if to update the current element pointer. */
    if ((opts & LIST_ALTR) == LIST_ALTR)
    list->pCurr = lp;

    /* Now go until 0 is returned or we hit the extent of the list. */
    rc = LIST_OK;
  status = TRUE;
  while (status)
    {
     status = (*func) (data, lp->data);
     if (status) {
  	if ((((opts & LIST_BACK) == LIST_BACK) ? (lp->prev) : (lp->next)) == NULL) {
		/* Tried to go beyond extent of list. */
		status = FALSE;
  	    	rc = LIST_EXTENT;
  	} else {
		/* Decide where to go next. */
		lp = (((opts & LIST_BACK) == LIST_BACK) ? (lp->prev) : (lp->next));
		/* Now decide if to update the current element pointer. */
		if ((opts & LIST_ALTR) == LIST_ALTR)
		list->pCurr = lp;
   	} // 2nd if end
     } // 1st if end
  } // while loop end
  return (rc);
}

int list_empty(list_t list) {
/* Return 1 if the list is empty.  0 otherwise. */
   return((list->pFirst == NULL) ? TRUE : FALSE);
}

void m_Free_List () {
}
