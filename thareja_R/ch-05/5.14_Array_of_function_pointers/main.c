/*
 * Aim : WAP that uses an array of function pointers.
 * Date : August 05th, 2012, 2:48pm
 *
***/

#include <stdio.h>
#include <stdlib.h>

int sum (int, int);
int sub (int, int);
int mul (int, int);
int divi (int, int);
int (*fp[4]) (int, int);

int main () {
  int i;
  fp[0] = &sum;
  fp[1] = &sub;
  fp[2] = &mul;
  fp[3] = &divi;
 
  for (i=0; i<4; i++) {
       printf ("\nRaje ==>> %d \n", (*fp[i])(3,2) );
  }
  return 0;
}

int sum (int a, int b) {
  int temp;
  temp = a + b;
  return temp;
}

int sub (int a, int b) {
  int temp;
  temp = a - b;
  return temp;
}

int mul (int a, int b) {
  int temp;
  temp = a * b;
  return temp;
}

int divi (int a, int b) { 
  int temp;
  temp = a / b;
  return temp;
}
