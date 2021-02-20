/***
    One Line RTOS
    https://www10.edacafe.com/blogs/embeddedsoftware/2016/02/15/the-one-line-rtos/
    Ex - Array of function Pointers in C.
    Date : 19 Feb 2021
    San Dieog, CA
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> /* sleep */

#define NTASKS 3

void alpha() {
  printf ("[%s] Enter L=%d \n", __func__, __LINE__);
  sleep(2);
}

void beta() {
  printf ("[%s] Enter L=%d \n", __func__, __LINE__);
  sleep(2);
}

void gamma1() {
  printf ("[%s] Enter L=%d \n", __func__, __LINE__);
  sleep(2);
}

void (*tasklist[NTASKS])() = {alpha, beta, gamma1};

int taskcount;

void task () {
  while (1) {
    for (taskcount=0; taskcount<NTASKS; taskcount++)
      (*tasklist[taskcount])();

  }
}

int main () {
  task ();
  return 0;
}

/**
   Runs Forever :
   [alpha] Enter L=15
   [beta] Enter L=20
   [gamma1] Enter L=25
   [alpha] Enter L=15
   [beta] Enter L=20
**/
