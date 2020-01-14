/*
  Given an integer number n, return the difference between the product of its digits and the sum of its digits.
  Example 1:
   Input: n = 234
   Output: 15
   Explanation:
    Product of digits = 2 * 3 * 4 = 24
    Sum of digits = 2 + 3 + 4 = 9
    Result = 24 - 9 = 15
  Example 2:
   Input: n = 4421
   Output: 21
   Explanation:
    Product of digits = 4 * 4 * 2 * 1 = 32
    Sum of digits = 4 + 4 + 2 + 1 = 11
    Result = 32 - 11 = 21
*/

#include <stdio.h>

int subtractProductAndSum(int n){
  int final =0, p =0,m =0, product =0, mul =1;

  while (n > 0) {
    p = m = n % 10;
    printf ("p = %d n=%d \n", p, n);
    n /= 10;
    product  += p;
    mul *= m;
    printf ("m = %d mul=%d \n", m, mul);
  }
  printf ("pr=%d mul = %d \n", product, mul);
  final = mul - product;
  return final;
}

int main() {
    int n = 234;
    int res = subtractProductAndSum(n);
    printf("O/P = %d \n", res);

    return 0;
}
