/***

    Simple log function using function pointers.

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Sun Mar  8 10:39:41 PDT 2026
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

#define debug(str,args...) printf("L=[%d][%s]->[%s] :| "str"\n",__LINE__,__FILE__, __func__, ##args)

struct services {
  void (*log)(const char *);
};

static void stderr_log(const char* msg) {
  fprintf(stderr, "%s\n", msg);
}

void test_1() {
  struct services s = {.log = stderr_log};
  s.log("Hello, This is Atul Raut's Unix World!");

}

void test_2() {
  struct services s = {.log = stderr_log};
  struct services *sp = &s;
  sp->log("Hello, This is Atul Raut's Way of Life!");

}

int main (int argc, char **argv) {
  test_1();
  test_2();
  return 0;
}

/**
   $ ./a.out
   Hello, This is Atul Raut's Unix World!
   Hello, This is Atul Raut's Way of Life!
 **/

/*
  Note :
  --> struct services *s = {.log = stderr_log};
  funcptr-log.c:41:20: error: initialization of non-aggregate type
  'struct services *' with a designate   initializer list
  --> The error happens because designated initializers (.member = value)
  work only with structures, not with pointers to structures.
  --> Solution :
  You wrote something like:
  struct services *s = {.log = stderr_log};
  Here:
  s is a pointer
  {.log = stderr_log} is a structure initializer
  C cannot initialize a pointer with a struct initializer, so the compiler throws:
  initialization of non-aggregate type 'struct services *'
***/
