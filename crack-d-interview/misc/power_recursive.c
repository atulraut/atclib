#include<stdio.h>
#include<stdlib.h>

int power(int x, int y) {
  int ret = 0;

  if(y == 0)
    return 1;

  ret = x * power(x, y-1);
  return ret;
}

int main() {
  int ans;
  ans = power(3,3);
  printf ("\npower of Num = %d \n", ans);
}
