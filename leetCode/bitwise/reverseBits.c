/*
  Reverse bits of a given 32 bits unsigned integer.
  Example 1:
  Input: 00000010100101000001111010011100
  Output: 00111001011110000010100101000000
  Explanation: The input binary string 00000010100101000001111010011100 represents the unsigned integer 43261596,
  so return 964176192 which its binary representation is 00111001011110000010100101000000.
  Example 2:
  Input: 11111111111111111111111111111101
  Output: 10111111111111111111111111111111
  Explanation: The input binary string 11111111111111111111111111111101 represents the unsigned integer 4294967293,
  so return 3221225471 which its binary representation is 10101111110010110010011101101001.
**/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/* Key: L(r)+A(n)R(n) */
uint32_t reverseBits(uint32_t n) {
	uint32_t r = 0;
	uint32_t t = 32;
	while (t > 0) {
		r = (r<<1) + (n&1);
		n = n>>1;
		t--;
	}
	return r;
}

int main () {
  uint32_t res = 4294967293;
  printf ("num = %d\n", reverseBits(res));
}
