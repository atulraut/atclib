/***
    Basics :
    Pointers / Arrays : Arithmetic Test Code
    Date : 17 March 2021
    San Diego, CA
 */
#include <stdio.h>

void test_pointers_to_array() {
  int x[] = {2, 3, 4};
  //++x;
  printf ("--> *x = %d x = %pK \n", *x, x);
  // ++x; // <-- 3: error: lvalue required as increment operand
  printf ("--> *x = %d x = %pK \n", *x, x);
  // x++;  // <-- 15:4: error: lvalue required as increment operand
  x[0]++;
}

/*
  Below Code Wont even Compile.
  basics.c:15:7: error: lvalue required as increment operand
  *x++ = *y++;
  ^
  basics.c:15:14: error: lvalue required as increment operand
  *x++ = *y++;             ^
  */
void test_arr_ptr() {
  char x[10];
  char y[] = "Hello";
  /*
    34:7: error: lvalue required as increment operand
     *x++ = *y++;
       ^
     34:14: error: lvalue required as increment operand
     *x++ = *y++;
              ^
   */
  while(y != NULL)
    *x++ = *y++;
}
/*
  To Fix above Code :
  char x[10];
  char y[] = "Hello";
  char *p_x = &x[0];
  char *p_y = &y[0];
  while(*p_y != '\0') *p_x++ = *p_y++;
*/

void test_ptrs () {
  char * something = "something";
  printf("-> %c \n", *something++);  // s
  printf("-> %c \n", *something);    // o
  printf("-> %c \n", *++something);  // m
  printf("-> %c \n", *something++);  // m
}

int main () {
  //test_pointers_to_array();
  test_arr_ptr ();
  //test_ptrs();
  return 0;
}
