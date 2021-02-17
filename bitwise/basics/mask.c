#include<stdio.h>

/***
    Set/Assign requested mask bit, apart from bit which is already set.

*/
void mask2() {
  int val = 1;
  int mask = 16;
  val |= mask;
  printf("--> val = %d \n", val);
}

void mask() {
  char c = 48;
  int i, mask = 01;
  for(i=1; i <= 5; i++) {
    printf("--> %c %c \n", c, c | mask);
    mask = mask << 1;
  }
}

int main() {
  mask();
  mask2();
  return 0;
}

/***
    mask() ::-->
    => ./a.out
    --> 0 1
    --> 0 2
    --> 0 4
    --> 0 8
    --> 0 0
*/

/***
    mask2() ::-->
    mask = 4
    O/P--> val = 5
    mask = 8
    O/P--> val = 9
    mask = 16
    O/P--> val = 17
*/
