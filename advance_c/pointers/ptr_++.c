#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/***
    The postfix ++ and -- operators essentially have higher precedence than the
    prefix unary operators. Therefore, *p++ is equivalent to *(p++); it increments p,
    and returns the value which p pointed to before p was incremented. To increment
    the value pointed to by p, use (*p)++ (or perhaps ++*p, if the evaluation order
    of the side effect doesn't matter).
*/
void foo1 () {
  int *ip;
  int i = 10;
  ip = &i;
  printf ("--> %d \n", *ip);
  printf ("--> %d \n", *ip++);
}

void foo2 () {
  int *ip;
  int i = 12;
  ip = &i;
  printf ("--> %d \n", *ip);
  printf ("--> %d \n", ++*ip);
  printf ("--> %d \n", ++(*ip));
}


int main () {
  foo1();
  foo2();
  return 0;
}
