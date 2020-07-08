#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/***
 * Whenever you are passing address of variable
 * basically you are passing copy of that address
 * passing pointer by value.
 * Remember pointers are passed by value.
 * i.e. the copy of address in pointer is created
 */
int a = 20;
/***
 * Bleow Code is Call by Value
 * https://www.youtube.com/watch?v=4Tv3uebRasg
 * 30 Sec.
 */
void ptr_pass_by_value(int *p) {
  p = &a;
}

/***
 * To fix, and make really call by address
 */
void ptr_pass_by_value_fix(int *p) {
  *p = a;
}

void foo () {
  int i, j;
  i = j = 0;
}
int main () {
  int x = 10;
  int *p = &x;
  ptr_pass_by_value_fix(p);
  foo();
  printf ("[%s] --> x = %d \n", __func__, x);
  return 0;
}
