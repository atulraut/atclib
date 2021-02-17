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

int main() {
  unsigned int i = 1;
  char *c = (char*)&i;
  if (*c)
    printf ("Little endian \n");
  else
    printf("Big endian \n");
  return 0;
}
