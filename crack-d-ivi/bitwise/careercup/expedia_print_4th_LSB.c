/*
 * You are given an  integer, print its 4th Least Significant Bit(LSB).
 * Shift right 3 spaces to get 4th bit into 1st least significant bit.
 * Bitwise & with 0001 to get result.
 *
 * Date : 10/Jan/2020
 * Place : San Diego, CA, USA
*/
#include <stdio.h>
#include <stdlib.h>

int bitAtPos(int num) {
  return (1 & (num >> 3));
}

int main () {
  int i = 7;
  printf ("O/P - %d \n ", bitAtPos(i));
}
