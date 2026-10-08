/***
    Explain thread code base

    Ref :
    https://chatgpt.com/c/6ac64f96-06d8-83e8-9413-110d6ffa8a0f

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Wed Oct  7 09:24:52 PDT 2026

    Folsom, CA.
 */

/*----------------------------------- Header --------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h> // va_arg
#include <ctype.h>
#include <limits.h>
#include <string.h>  /* malloc */
#include <stdbool.h>
#include <math.h>
#include <assert.h>
#include <stdint.h> /* uint32_t */
#include <unistd.h> /* sleep */
#include <pthread.h> /* thread rouintes */

#define debug(str,args...) printf("L=[%d][%s]->[%s] :| "str"\n",__LINE__,__FILE__, __func__, ##args)

int x = 0;

void* run(void* arg) {

  for (int i = 0; i < 100; i++)
    x++;
  return NULL;
}

int test(void) {
  pthread_t t1, t2;

  // Start two threads
  pthread_create(&t1, NULL, run, NULL);
  pthread_create(&t2, NULL, run, NULL);

  // Wait until both threads finish
  pthread_join(t1, NULL);
  pthread_join(t2, NULL);

  printf("x = %d\n", x);

  return 0;
}

int main() {
  //  thread_start(run);
  //  thread_start(run);
  int x = test();
  printf("%d\n", x);
  return x;
}

/**
   ./6_thread
   x = 200
   0
**/

/**
   Notes :
   Thread 1: x++ 100 times
   Thread 2: x++ 100 times

   Expected x = 200

   LOAD   R1, [x]      ; fetch/load x from memory/cache
   ADD    R1, R1, #1   ; increment
   STORE  [x], R1      ; write it back
**/
