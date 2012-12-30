/***
* Aim : Implement Polymorphism using C.
* Date : Thursday, December 20 2012, 11:50 PM
* File : base.c
*/

#include "base.h"

int base_init(int v) {
  int i;
  printf ("\nHi base_init \n");

  at_v_table_type at_list[LAST] = {
    &plug_1_handle,
    &plug_2_handle
  };
 
  for (i=0; i<LAST; i++) {
    at_list[i].handle->init ();
  }
  return 0;
}
