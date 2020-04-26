/*
  Given a range [m, n] where 0 <= m <= n <= 2147483647, return the
  bitwise AND of all numbers in this range, inclusive.
  Explain: https://www.youtube.com/watch?v=-qrpJykY2gE
*/
#include <stdio.h>
#include <stdlib.h>

int rangeBitwiseAnd(int m, int n) {
  int count = 0;
  while (m!=n) {
    m >>= 1;
    n >>= 1;
    count += 1;
  }
  return (m <<= count);
}

int main () {
  int m = 5;
  int n = 7;
  int ret = 0;
  ret = rangeBitwiseAnd(m, n);
  printf ("[%s] ret-> %d L=%d\n",__func__, ret, __LINE__);
}
