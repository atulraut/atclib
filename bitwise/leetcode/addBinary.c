/***
    67. Add Binary
    Given two binary strings a and b, return their sum as a binary string.
    Example 1:
    Input: a = "11", b = "1"
    Output: "100"
    Example 2:
    Input: a = "1010", b = "1011"
    Output: "10101"
    Constraints:
    1 <= a.length, b.length <= 104
    a and b consist only of '0' or '1' characters.
    Each string does not contain leading zeros except for the zero itself.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../at_lib.h"

char * addBinary(char * a, char * b){
  int i = strlen(a);
  int j = strlen(b);

  if(i < j)
    return addBinary(b, a);

  char *res = (char *)calloc(i + 2, 1);
  res[i+1] = '\0';

  int carry = 0;
  int k = i;

  while(i || j){
    debug ("res = %d carry = %d", res[k],  carry);
    if(i)
      carry += a[--i] - '0';
    if(j)
      carry += b[--j] - '0';
    res[k--] = carry % 2 + '0'; /* 0 + 0 = 0 [as 0 == 48 (ASIC)]*/
    int q = k;
    debug ("res = %d carry1 = %d carry2 = %d", res[q], (carry % 2 + '0'), carry);
    carry /= 2;
    debug ("res = %d carry = %d", res[q],  carry);
  }
  res[0] = carry+'0';
  if(!carry)
    return NULL;
  res+1;
  return res;
}

int main () {
  char a[] = "11";
  char b[] = "1";
  char *ret;
  ret = addBinary(a, b);
  printf ("[%s] ret-> %s L=%d\n",__func__, ret, __LINE__);
}

/**
    => ./a.out
    [addBinary] L=41 :res = 0 carry1 = 48 carry2 = 2
    [addBinary] L=41 :res = 0 carry1 = 48 carry2 = 2
    [main] ret-> 100 L=56
**/
