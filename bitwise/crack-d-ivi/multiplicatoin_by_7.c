/*
 * Program to multiplication by 7 using bitwise operator.
 */

#include<stdio.h>

void multiplication_by_7 (int x) {
  int i;
  unsigned int y;
  for (i=1; i<=10; i++) {
    y = (i << 3) - (i << 0);
    printf ("\n Mul by 07 = ->[%d] ", y);
  }
  for (i=1; i<=10; i++) {
    y = (i << 3) + (i << 1);
    printf ("\n Mul by 10 = ->[%d] ", y);
  }
  x=1;
  printf ("\nx[0] = %d ", (x << 0));
  printf ("\nx[1] = %d ", (x << 1));
  printf ("\nx[2] = %d ", (x << 2));
  printf ("\nx[3] = %d ", (x << 3));
  printf ("\nx[4] = %d \n",(x << 4));
}

int main() {
  multiplication_by_7(2);
  return (0);
}
