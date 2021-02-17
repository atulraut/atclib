/***
    Program : Swap individual (adjacent) bits in INT32 using C.
    Using 0xaa : As mask clears bits in position 0/2/4/6 etc.
    0xAAAAAAAA - 1010 1010 1010 1010 1010 1010 1010 1010
    Using 0x55 : As mask clears bits in position 1/3/5/ etc.
    0x55555555 - 0101 0101 0101 0101 0101 0101 0101 0101
    https://mdrach.github.io/cs107-apps/
*/

#include <stdio.h>
#define debug(str,args...) printf("[%s] L=%d :"str"\n", __func__, __LINE__, ##args)
/**
   Function to swap adjacent bits of a given number
**/
int swapAdjacentBits(int n) {
  return (((n & 0xAAAAAAAA) >> 1) | ((n & 0x55555555) << 1));
}

int main() {
  debug("o/p = %d \n", swapAdjacentBits(85));
  debug("o/p = %d \n", swapAdjacentBits(64));
  return 0;
}
/**
   i/p 1 0 1 0 1 0 1 0 - 85
   o/p 0 1 0 1 0 1 0 1 - 170
   i/p 0 1 0 0 0 0 0 0 - 64
   o/p 1 0 0 0 0 0 0 0 - 128
   => ./a.out
   [main] L=20 :o/p = 170
   [main] L=21 :o/p = 128
**/
