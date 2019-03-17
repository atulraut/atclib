#include <stdio.h>
#include <stdlib.h>

int main() {
  int x = -1;
  int y = 1;
  int ret;
  ret = ((x^y)<0);
  printf ("--> %d \n", ret);
}
