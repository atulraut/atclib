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

  int main () {
    int num = 5;
    //  printf ("\n -> %d \n", findComplement(num));
    printf ("\n Output -> %d \n", findComplement(num));
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
