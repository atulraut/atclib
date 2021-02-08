/*
  Write a program to swap odd and even bits in an integer with as
  few instructions as possible (e.g., bit 0 and bit 1 are swapped,
  bit 2 and bit 3 are swapped, etc).
*/
#include <stdio.h>
#include <stdlib.h>

/*
  SOLUTION
  Mask all odd bits with 10101010 in binary (which is 0xAA), then shift them
  left to put them in the even bits. Then, perform a similar operation for
  even bits. This takes a total 5 instructions.

  Using 0x55 : As mask clears bits in position 1/3/5/ etc.
  Using 0xaa : As mask clears bits in position 0/2/4/6 etc.
  https://web.stanford.edu/class/archive/cs/cs107/cs107.1194/lab1/practice.html
*/	
int swapOddEvenBits(int x) {
  unsigned char odd_bits = x & 0xAA;	/* Get all Odd bits of X  */
  unsigned char even_bits = x & 0x55;	/* Get all Even bits of X */
  printf ("[%s] odd  = %d L=%d \n", __func__, odd_bits, __LINE__);
  printf ("[%s] even = %d L=%d \n", __func__, even_bits, __LINE__);
  odd_bits >>= 1;
  even_bits <<= 1;
		
  printf ("[%s] odd  = %d L=%d \n", __func__, odd_bits, __LINE__);
  printf ("[%s] even = %d L=%d \n", __func__, even_bits, __LINE__);

  return ( ((x & 0xaaaaaaaa) >> 1) | ((x & 0x55555555) << 1) );
}

unsigned char swapOddEvenBits2(unsigned char num) {
  unsigned char odd_bits = num & 0xAA;	/* Get all Odd bits of X  */
  unsigned char even_bits = num & 0x55;	/* Get all Even bits of X */

  odd_bits >>= 1;
  even_bits <<= 1;

  /* Union(merge) Odd_bits with Even_bits */
  return (odd_bits | even_bits);
}

int main() {
  int ret = 0;
  ret = swapOddEvenBits2(6);
  printf ("--> %d \n", ret);
}

/*
  => ./a.out
  [swapOddEvenBits] odd  = 2 L=22
  [swapOddEvenBits] even = 4 L=23
  [swapOddEvenBits] odd  = 1 L=27
  [swapOddEvenBits] even = 8 L=28
  --> 9
*/
