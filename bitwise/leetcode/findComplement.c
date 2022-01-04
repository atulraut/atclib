/*
  https://leetcode.com/problems/number-complement/
 Given a positive integer, output its complement number. The complement strategy
  is to   flip the bits of its binary representation.
  Note:
    The given integer is guaranteed to fit within the range of a 32-bit signed integer.
    You could assume no leading zero bit in the integer’s binary representation.
Example 1: Input: 5 Output: 2
  Explanation: The binary representation of 5 is 101 (no leading zero bits), and
  its complement is 010. So you need to output 2.
Example 2: Input: 1 Output: 0
  Explanation: The binary representation of 1 is 1 (no leading zero bits), and its
  complement is 0. So you need to output 0.

*/

#include <stdio.h>
#include <stdlib.h>

#define debug(str,args...) printf("[%s] L=%d :"str"\n", __func__, __LINE__, ##args)

int findComplement(int num) {
  int temp, result = 0;
  temp = num;

  while(temp) {
    result = (result << 1);
    debug ("left result = %d", result);
    result |= 1;
    debug ("or result = %d", result);
    temp = temp >> 1;
    debug ("right temp = %d", temp);
  }
  debug ("result = %d temp=%d final=%d", result, temp, (result^num));
  return result^num;
}

/*
   OpenJDK Hacker Algo:
*/
 int findComplement2(int num) {
    // bitmask has the same length as num and contains only ones 1...1
    int bitmask = num;
    bitmask |= (bitmask >> 1);
    bitmask |= (bitmask >> 2);
    bitmask |= (bitmask >> 4);
    bitmask |= (bitmask >> 8);
    bitmask |= (bitmask >> 16);
    // flip all bits
    return bitmask ^ num;
  }

/**
   https://leetcode.com/problems/complement-of-base-10-integer/
   009. Complement of Base 10 Integer

   The complement of an integer is the integer you get when
   you flip all the 0's to 1's and all the 1's to 0's in its binary representation.

   For example, The integer 5 is "101" in binary and its complement is "010" which is the integer 2.
   Given an integer n, return its complement.

   Input: n = 5
   Output: 2
   Explanation: 5 is "101" in binary, with complement "010" in binary, which is 2 in base-10.

   Input: n = 7
   Output: 0
   Explanation: 7 is "111" in binary, with complement "000" in binary, which is 0 in base-10.

   Input: n = 10
   Output: 5
   Explanation: 10 is "1010" in binary, with complement "0101" in binary, which is 5 in base-10.

   Constraints:
   0 <= n < 10^9
   Date: Jan 3, 2022
   Folsom, CA
*/
int bitwiseComplement(int N) {
    if (N == 0) return 1;
    int todo = N, bit = 1;
    while (todo != 0) {
      // flip current bit
      N = N ^ bit;
      // prepare for the next run
      bit = bit << 1;
      todo = todo >> 1;
    }
    return N;
}

  int main () {
    int num = 5;
    //  printf ("\n -> %d \n", findComplement(num));
    printf ("\n Output -> %d \n", findComplement(num));

    debug ("bitwiseComplement = %d", bitwiseComplement(5));

    return 1;
  }

/**
   => ./a.out
   [findComplement] L=28 :left result = 0
   [findComplement] L=30 :or result = 1
   [findComplement] L=32 :right temp = 2
   [findComplement] L=28 :left result = 2
   [findComplement] L=30 :or result = 3
   [findComplement] L=32 :right temp = 1
   [findComplement] L=28 :left result = 6
   [findComplement] L=30 :or result = 7
   [findComplement] L=32 :right temp = 0
   [findComplement] L=34 :result = 7 temp=0 final=2

   Output -> 2
**/

/**
   [main] L=98 :bitwiseComplement = 2
**/
