/***
* Aim : Implement Polymorphism using C.
* Date : Thursday, December 20 2012, 11:50 PM
* File : plug-01.c
*/

#include "plug-01.h"

int plug_1_init ();
int plug_1_close ();

at_base_type plug_1_handle = {
  plug_1_init,
  plug_1_close, 
};

int plug_1_init () {
  printf ("\nHi plug_1_init\n"); 
  return 0;
}

int plug_1_close () {
  printf ("\nHi plug_1_close\n");
  return 0;
}

