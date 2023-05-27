#include<stdio.h>
#include<stdlib.h>

static const int mod = 1e9 + 7;
int calculate_power(long long a, long long b) {
  if (a == 0) {
    return 0;
  }

  if (b == 0 || a == 1) {
    return 1;
  }

  a = a % mod;

  long long tmp = calculate_power(a, b/2);
  long long res = tmp * tmp % mod;;
  if ((b & 1) != 0) {
    res = a * res % mod;
  }
  return (int)res;
}

int power_optmz(int x, int y) {
  int temp = 0;

  temp = power_optmz(x, y/2);
  if(y%2 == 0)
    return temp * temp;
  else
    return temp * temp * temp;
}

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
  ans = calculate_power(13,13);
  printf ("\npower of Num = %d \n", ans);
}
