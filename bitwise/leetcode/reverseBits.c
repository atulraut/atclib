/*
  https://leetcode.com/problems/reverse-bits/

  Reverse bits of a given 32 bits unsigned integer.

  Note:
  Note that in some languages, such as Java, there is no unsigned integer type.
  In this case, both input and output will be given as a signed integer type.
  They should not affect your implementation, as the integer's internal
  binary representation is the same, whether it is signed or unsigned.
  In Java, the compiler represents the signed integers using 2's complement
  notation. Therefore, in Example 2 above, the input represents the signed
  integer -3 and the output represents the signed integer -1073741825.


  Input: 00000010100101000001111010011100
  Output: 00111001011110000010100101000000
  Explanation: The input binary string 00000010100101000001111010011100
  represents the unsigned integer 43261596,
  so return 964176192 which its binary representation is 00111001011110000010100101000000.


  Input: 11111111111111111111111111111101
  Output: 10111111111111111111111111111111
  Explanation: The input binary string 11111111111111111111111111111101
  represents the unsigned integer 4294967293,
  so return 3221225471 which its binary representation is 10101111110010110010011101101001.

  Tag=Cisco
  Fri Aug 16 07:53:27 2019 -0700
  San Diego, CA.
**/
/*----------------------------------- Header --------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>
#include <string.h>  /* malloc */
#include <stdbool.h>
#include <math.h>
#include <assert.h>
#include <stdint.h> /* uint32_t */
#include <unistd.h> /* sleep */
#include <inttypes.h> /* uint32_t: printf("%" PRIu32 "\n", ret); */

/*----------------------------------- Micro --------------------------------------*/
#define debug(str,args...) printf("[%s] L=%d :"str"\n", __func__, __LINE__, ##args)
#define atsizeof(object) (char *)(&object+1) - (char*)(&object)
#define arrsz(x)  (sizeof(x) / sizeof((x)[0]))
#define max(a,b)				\
  ({ __typeof__ (a) _a = (a);			\
    __typeof__ (b) _b = (b);			\
    _a > _b ? _a : _b; })
#define min(a,b)				\
  ({ __typeof__ (a) _a = (a);			\
    __typeof__ (b) _b = (b);			\
    _a < _b ? _a : _b; })
/*----------------------------------- Micro --------------------------------------*/


/**
   The key idea is that for a bit that is situated at the index i,
   after the reversion, its position should be 31-i (note: the index
   starts from zero).

   We iterate through the bit string of the input integer, from
   right to left (i.e. n = n >> 1).
   To retrieve the right-most bit of an integer,
   we apply the bit AND operation (n & 1).

   For each bit, we reverse it to the correct position (i.e. (n & 1) << power).
   Then we accumulate this reversed bit to the final result.

   When there is no more bits of one left (i.e. n == 0),
   we terminate the iteration.
**/

/* Key: L(r)+A(n)R(n) */
uint32_t reverseBits2(uint32_t num) {
  uint32_t r = 0;
  uint32_t power = 32;

  while (power > 0) {
    debug ("num=%d (num&1) = %d power = %d", num, (num&1), power);
    r = (r<<1) + (num&1);
    num = num>>1;
    power--;
  }
  return r;
}

uint8_t reverseBits(uint8_t n) {
  uint8_t r = 0;
  uint8_t power = 8;
  while (power > 0) {
    debug ("n=%d (n&1) = %d power = %d", n, (n&1), power);
    r = (r<<1) + (n&1);    // 0 * 2^1 (==2) + if bit is set 1 else 0
    n = n>>1;              // divide number by 2: 128 / 2^1: 128/2
    power--;
  }
  return r;
}

void test () {
  uint32_t res = 128;//43261596;//170;
  uint32_t ret = reverseBits(res);

  //printf("%" PRIu16 "\n", ret);
  printf("[test] L=109 Output:" "%" PRIu32 "\n", ret);
}

int main () {
  test();
  return 0;
}

/**
   => ./a.out
   [reverseBits] L=96 :n=128 (n&1) = 0 power = 8
   [reverseBits] L=96 :n=64 (n&1) = 0 power = 7
   [reverseBits] L=96 :n=32 (n&1) = 0 power = 6
   [reverseBits] L=96 :n=16 (n&1) = 0 power = 5
   [reverseBits] L=96 :n=8 (n&1) = 0 power = 4
   [reverseBits] L=96 :n=4 (n&1) = 0 power = 3
   [reverseBits] L=96 :n=2 (n&1) = 0 power = 2
   [reverseBits] L=96 :n=1 (n&1) = 1 power = 1
   [test]        L=109 Output:1
**/
