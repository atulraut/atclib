/***
    Sizes of different data tyeps in C
*/
#include <stdio.h>
#include <stdlib.h>

#define debug(str,args...) printf("[%s] L=%d :"str"\n", __func__, __LINE__, ##args)


void foo2() {
  debug ("unsigned int=%lu long unsigned int =%lu ", sizeof(unsigned int), sizeof(long unsigned int) );
}

void foo1() {
  debug ("char=%lu short=%lu int=%lu long=%lu size_t=%lu ", sizeof(char), sizeof(short), sizeof(int), sizeof(long), sizeof(size_t) );
}

int main () {
  foo1();
  foo2();
  return 0;
}

/**
   => ./a.out
   [foo1] L=9 :char=1 short=2 int=4 long=8 size_t=8
   [foo2] L=10 :unsigned int=4 long unsigned int =8
**/
