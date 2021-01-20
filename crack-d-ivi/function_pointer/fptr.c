/***
* Aim : Sample function pointer example.
* Date : Thursday, December 20 2012, 10:11 PM
*
*/
#include <stdio.h>
#include <stdlib.h>

void my_int_func (int);
int sum (int, int);
int sub (int, int);
int mul (int, int);
int dit (int, int);

void my_int_func (int x) {
  printf ("\n\n:: my_int_func --> %d\n", x);
}

int main () {
  int i, t;
  void (*foo) (int);   // Function Pointer
  int (*arr[4]) (int, int);// Array of Function Pointer
  
  // use of function pointer
  foo = &my_int_func;
  foo(2);
  //or
  (*foo)(2);
  
  // use of array of function pointer
  arr[0] = sum;
  arr[1] = sub;
  arr[2] = mul;
  arr[3] = dit;
  for (i=0; i<4; i++) {
    t = (*arr[i])(4,2);  // OR arr[i](4,2);
    printf ("\n t = %d\n", t);
  }
  return 0 ;
}

int sum (int a, int b) {
  int t = a + b;
  return t;
}
int sub (int a, int b) {
  int t = a - b;
  return t; 
}

int mul (int a, int b) {
  int t = a * b;
  return t; 
}

int dit (int a, int b) {
  int t = a/b;
  return b;
}
