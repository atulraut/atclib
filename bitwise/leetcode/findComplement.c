/*
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

int findComplement (int num) {
  int i = 0;
  int flag = 0;
  for(i=32; i>0; --i) {
    if(num & (1 << i)) { // check if bit is set or not
      flag = 1;
    }
    if(flag) { // if bit is set toggle the bit
      num = num ^ (1 << i);
    }
  }
  return num;
}

int getCompliment(int num) {
  if(num == 0)
    return 1;
  int sol = 0;
  int nextbit = 1;
  while (num != 0) {
    int lastBit = (num & 1); // check bit is set of not
    if (lastBit == 0) {
      sol = sol | nextbit;
    }
    nextbit = nextbit << 1;
    num = num >> 1;
  }
  return sol;


  int main () {
    int num = 5;
    //  printf ("\n -> %d \n", findComplement(num));
    printf ("\n -> %d \n", getCompliment(num));
  }
