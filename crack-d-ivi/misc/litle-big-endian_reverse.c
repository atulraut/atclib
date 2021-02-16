/*
 * https://www.geeksforgeeks.org/little-and-big-endian-mystery/
 * Little and big endian are two ways of storing multibyte data-types ( int, float, etc).
 * In little endian machines, last byte of binary representation of the multibyte
 * data-type is stored first. On the other hand, in big endian machines,
 * first byte of binary representation of the multibyte data-type is stored first.
 * Little endian: Lower byte is stored on lower address.
 * Big endian: Lower byte is stored on higher address.

*/

#include <stdio.h>
#include "../../at_lib.h"

/***
 * Reverse Endianness :
 */
int reverse(int a) {
  int x = a;
  char *p = (char *) &x;
  char *q = p + sizeof(a) - 1;
  while (p < q) {
    char t = *p;
    *p = *q;
    *q = t;
    p++;
    q--;
  }
  return x;
}

int rev2(int num) {
  unsigned int i = num;//0x12345678;//0xfafbfcfd;
  unsigned int j;
  j= ((i & 0xff000000) >> 24) | ((i & 0xff0000)>>8) | ((i & 0xff00) << 8) | ((i & 0xff) << 24);
  debug ("Big endian  a = 0x%x\n", j);
  return num;
}

int main() {
  unsigned int a = 0x12345678;
  printf("Big endian  a = 0x%x\n", a);
  printf("Big endian  a = 0x%x\n", reverse(a));
  debug ("Big endian  a = 0x%x\n", rev2(a));

  return 0;
}

/*
  => ./a.out
  Big endian  a = 0x12345678
  Big endian  a = 0x78563412
  [rev2] L=36 :Big endian  a = 0x78563412

  [main] L=44 :Big endian  a = 0x12345678
*/
