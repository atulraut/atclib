#include <stdio.h>
#include <stdlib.h>
#include "../../at_lib.h"

int multiply(int x, int y) {
  debug(" x = %d y = %d", x, y);

  if (y == 0)
    return 0;

  if(y > 0)
    return (x + multiply(x, y-1));

  if(y < 0)
    return -multiply(x, -y);
}

int main () {
  printf ("multiplication --> %d\n\n", multiply(5, -11));
}

/***
    => ./a.out
    [multiply] L=6 : x = 5 y = -11
    [multiply] L=6 : x = 5 y = 11
    [multiply] L=6 : x = 5 y = 10
    [multiply] L=6 : x = 5 y = 9
    [multiply] L=6 : x = 5 y = 8
    [multiply] L=6 : x = 5 y = 7
    [multiply] L=6 : x = 5 y = 6
    [multiply] L=6 : x = 5 y = 5
    [multiply] L=6 : x = 5 y = 4
    [multiply] L=6 : x = 5 y = 3
    [multiply] L=6 : x = 5 y = 2
    [multiply] L=6 : x = 5 y = 1
    [multiply] L=6 : x = 5 y = 0

    multiplication --> -55
*/
