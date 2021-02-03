/***
    Number of 1 Bits :
    Write a function that takes an unsigned integer and returns
    the number of '1' bits it has (also known as the Hamming weight).

    Note:
    Note that in some languages such as Java, there is no unsigned
    integer type. In this case, the input will be given as a signed
    integer type. It should not affect your implementation, as the
    integer's internal binary representation is the same, whether it is signed or unsigned.

    Follow up: If this function is called many times, how would you optimize it?

    Example 1:Input: n = 00000000000000000000000000001011
    Output: 3
    Explanation: The input binary string 00000000000000000000000000001011 has
    a total of three '1' bits.

    Example 2:
    Input: n = 00000000000000000000000010000000
    Output: 1
    Explanation: The input binary string 00000000000000000000000010000000 has a
    total of one '1' bit.

    Example 3:
    Input: n = 11111111111111111111111111111101
    Output: 31
    Explanation: The input binary string 11111111111111111111111111111101 has a
    total of thirty one '1' bits.

    Date : 1/2/2021
    San Diego, CA
*/
#include <stdio.h>
#include "../../at_lib.h"

int hammingWeight(uint32_t n) {
  unsigned int o = 1;
  int count =0;
  for(int i=0;i<32;i++){
    if(n&o)
      count++;
    o<<=1;
  }
  return count;
}

/***
    Same as : crack-d-ivi/bitwise/countSetBits.c
*/
int hammingWeight2(uint32_t n) {
  int cnt = 0;
  while(n) {
    n &= (n-1);
    cnt++;
  }
  return cnt;
}

int main () {
  uint32_t n =  00000000000000000000000000001011;
  int ret =  hammingWeight(n);

  printf ("[%s] ret = %d \n", __func__, ret);

  return 0;
}

/***
    => ./a.out
    [main] ret = 3
*/
