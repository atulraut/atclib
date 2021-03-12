/***
  Write a function to determine the number of bits required to convert
  integer A to integer B.
  Input: 31, 14
  Output: 2
*/
#include <stdio.h>
#include <stdlib.h>
#include "../../at_lib.h"

/*
   SOLUTION
   This seemingly complex problem is actually rather straightforward.
   To approach this, ask yourself how you would figure out which bits
   in two numbers are different.
   Simple: with an XOR.
   Each 1 in the xor will represent one different bit between A and B.
   We then simply need to count the number of bits that are 1.
*/

int bitSwapRequired(int a, int b) {
  int count = 0, i=0;
  for (int c = a ^ b; c != 0; c = c >> 1) {
    debug ("i=[%d]--> c %d ",++i, c);
    count += c & 1;
    debug ("--> cnt=%d (c&1) = %d ", count, (c&1));

  }
  return count;
}

int main() {
  int ret = 0;
  ret = bitSwapRequired(31, 14);
  printf ("--> %d \n", ret);
}

/*
  ---------------
  16 8 4 2 1
  ---------------
  4  3 2 1 0
  ----------------
  1  1 1 1 1 - 31
  0  1 1 1 0 - 14
  ----------------
^ 1  0 0 0 1 - 17
  -----------------
  - Diff is 2 Hence ans is 2.
*/

/**
   => ./a.out
   [bitSwapRequired] L=24 :i=[1]--> c 17
   [bitSwapRequired] L=26 :--> cnt=1 (c&1) = 1
   [bitSwapRequired] L=24 :i=[2]--> c 8
   [bitSwapRequired] L=26 :--> cnt=1 (c&1) = 0
   [bitSwapRequired] L=24 :i=[3]--> c 4
   [bitSwapRequired] L=26 :--> cnt=1 (c&1) = 0
   [bitSwapRequired] L=24 :i=[4]--> c 2
   [bitSwapRequired] L=26 :--> cnt=1 (c&1) = 0
   [bitSwapRequired] L=24 :i=[5]--> c 1
   [bitSwapRequired] L=26 :--> cnt=2 (c&1) = 1
   --> 2
**/
