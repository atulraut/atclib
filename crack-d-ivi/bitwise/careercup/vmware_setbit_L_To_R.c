/*
 * VMWare: Implement a function, set_bit_l_to_R(x,y,l,r)
 * For bit L to R(both inclusive), if they are set in x, also set
 * them in y. Do not change bits of y, if they are not in range
 * L To R, or those bits are not set in x. L and R are 0-based.
 * operators.
 * Date : 10/Jan/2020
 * Place : San Diego, CA, USA 
*/
#include <stdio.h>
#include <stdlib.h>

int get_bit(int x, unsigned int b) {
  return (x & (1 << b));
}

int set_bit(int y, unsigned int b) {
  return (y | (1 << b));
}
int set_bit_L_To_R (int x, int y, int l, int r) {
  int j;
  for(j=l; j<=r; j++) {
    if(get_bit(x, j))
      y = set_bit(y, j);
  }
  return y;
}

int main () {
  int i = 14;
  int j = 1;
  int L = 1;
  int R = 2;
  printf ("O/P - %d \n ", set_bit_L_To_R(i, j, L, R));
}
