#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../at_lib.h"

void foo4() {
  int p[2];
  int *q = p;
  p[0] = 10;
  p[1] = 100;
  debug("%d", *q++);
  debug("%d", *q);
}

/***
    4.5 : http://c-faq.com/ptrs/castincr.html
    In C, a cast operator does not mean ``pretend these bits have a different type, and
    treat them accordingly''; it is a conversion operator, and by definition it yields
    an rvalue, which cannot be assigned to, or incremented with ++.
*/
void foo3 () {
  int i = 1;
  char *p = &i;
  //  ((int *)p)++; /* error: lvalue required as increment operand */
  printf ("[%s] *p = %d \n", __func__, *p);
}

/***
    4.3 : http://c-faq.com/ptrs/unopprec2.html
    The postfix ++ and -- operators essentially have higher precedence than the
    prefix unary operators. Therefore, *p++ is equivalent to *(p++); it increments p,
    and returns the value which p pointed to before p was incremented. To increment
    the value pointed to by p, use (*p)++ (or perhaps ++*p, if the evaluation order
    of the side effect doesn't matter).
*/

void foo2 () {
  int *ip;
  int i = 12;
  ip = &i;
  debug ("--> %d ", *ip);
  debug ("--> %d ", ++*ip);
  debug ("--> %d ", ++(*ip));
}

void foo1 () {
  int *ip;
  int i = 10;
  ip = &i;
  debug ("--> %d ", *ip);
  debug ("--> %d ", *ip++);
}

int main () {
  foo1();
  foo2();
  foo3();
  foo4();
  return 0;
}

/**
   => ./a.out
   [foo1] L=31 :--> 10
   [foo1] L=32 :--> 10
   [foo2] L=39 :--> 12
   [foo2] L=40 :--> 13
   [foo2] L=41 :--> 14
   [foo3] *p = 1
   foo4] L=11 :10
   [foo4] L=12 :100
**/
