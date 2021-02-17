/***
 * Program to check at given position bit is set or NO.
 * 5 - 0101
 * set_bits(5, 0) - 1
 * set_bits(5, 1) - 0
 * set_bits(5, 2) - 1
 */

#include <stdio.h>
#include <stdbool.h>
#include <math.h>

int set_bits (int bit, int pos) {
  if (bit & (1 << (pos)))
    return 1;
  else
    return 0;
}

int main() {
  printf("[%s] --> %d \n",__func__, set_bits(5, 0));
  printf("[%s] --> %d \n",__func__, set_bits(5, 1));
  printf("[%s] --> %d \n",__func__, set_bits(5, 2));
  return 0;
}
