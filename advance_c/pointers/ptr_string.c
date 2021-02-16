#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../at_lib.h"

/**
    String Constant : segmentation fault.
    Segmentation fault (core dumped) Line-15
**/
void foo1() {
  char *str;
  /* Stored in read only part of data segment */
  str = "GfG";
  /* Problem:  trying to modify read only memory */
  *(str+1) = 'n';
}

int main () {
  foo1();

  return 0;
}

/**
   => ./a.out
   Segmentation fault (core dumped)
**/
