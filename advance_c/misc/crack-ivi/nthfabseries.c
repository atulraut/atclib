/*
* Function to compute Nth fibonacci number
*/
#include <stdio.h> 
#include <string.h>

int main () {
  int ret = 0;
  ret = fib (5);
  printf ("\nret = %d \n", ret);
}
  
static long fib (int n) {
  return n <= 1 ? n : fib (n-1) + fib (n-2);
}
