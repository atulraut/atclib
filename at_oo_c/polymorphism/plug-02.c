/***
* Aim : Implement Polymorphism using C.
* Date : Thursday, December 20 2012, 11:50 PM
* File : plug-02.c
*/

#include "plug-02.h"

int plug_2_init ();
int plug_2_close ();

at_base_type plug_2_handle = {
  plug_2_init,
  plug_2_close,
};

int plug_2_init () {
  printf ("\nHi plug_2_init\n");
  return 0;
}

int plug_2_close () {
  printf ("\nHi plug_2_close\n");
  return 0;
}

