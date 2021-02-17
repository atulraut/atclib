/***
    Sizes of different data tyeps in C
*/
#include <stdio.h>
#include <stdlib.h>
#include "../at_lib.h"

void foo1() {
  debug ("char=%lu short=%lu int=%lu long=%lu size_t=%lu ", sizeof(char), sizeof(short), sizeof(int), sizeof(long), sizeof(size_t) );
}

int main () {
  foo1();
  return 0;
}

/**
   => ./a.out
   [foo1] L=9 :char=1 short=2 int=4 long=8 size_t=8
**/
