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

void show_mem_rep(char *start, int n) {
  int i;
  for (i = 0; i < n; i++)
    printf(" %.2x", start[i]);
  printf("\n");
}

int main() {
  unsigned int i = 0x01234567;
  char *c = (char*)&i;
  if (*c)
    printf ("Little endian = %c \n", *c);
  else
    printf("Big endian \n");

  show_mem_rep(c, sizeof(i));
  //  show_mem_rep((char *)&i, sizeof(i));
  return 0;
}
