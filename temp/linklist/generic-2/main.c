/***
Reference : http://hg.ohnopub.net/hg/liblist/file/0b24e078e22e 
*/
#include <stdio.h>
#include "list.h"

int main () {
  /**/
  list_t list;
  /* Allocate new list */
  list = list_init ();
  m_Add (list, 10, 2);
  m_Add (list, 'A', 1);
  m_Display ();
}

