#include <stdio.h>
#include <stdlib.h>
#include <string.h>
union {
  char str[4];
  unsigned int ui;
} u;

int main() {
  unsigned int i = 0x1122;
  unsigned char c[2];
  unsigned int d;
  c[0] = i & 0xFF;
  c[1] = (i>>8) & 0xFF;

  printf("c[0] = %x \n", c[0]);
  printf("c[1] = %x \n", c[1]);
  printf("i    = %x \n", i);


  char str[4]="abc";
  unsigned int a = *(unsigned int*)str;
  unsigned int b = str[0]<<24 | str[1]<<16 | str[2]<<8 | str[3];

  memcpy(&d, str, 4);
  printf("a=%u08x b=%08x  d=%08x\n", a, b, d);
  printf("d=%x\n", d);

  strcpy(u.str, "abc");
  printf("%u\n", u.ui);
  return 0;

}
