/*
  copyrights : http://www.geeksforgeeks.org
  ----------------------
  i/p  | OR | & | XOR  |
  ----------------------
  0 | 0 | 0  | 0 | 0   |
  ----------------------
  0 | 1 | 1  | 0 | 1   |
  ----------------------
  1 | 0 | 1  | 0 | 1   |
  ----------------------
  1 | 1 | 1  | 1 | 0   |
  ----------------------
  The idea is to keep putting set bits of the num in reverse_num until
  num becomes zero. After num becomes zero, shift the remaining bits of reverse_num.
  Let num is stored using 8 bits and num be 00000110. After the loop
  you will get reverse_num as 00000011. Now you need to left shift
  reverse_num 5 more times and you get the exact reverse 01100000.
*/
#include <stdio.h>
#include <stdint.h>

#define debug(str,args...) printf("L=[%d][%s]->[%s] :| "str"\n",__LINE__,__FILE__, __func__, ##args)

uint32_t reverse_bits(uint32_t n) {

    uint32_t result = 0;

    for (int i = 0; i < 32; i++) {
        result <<= 1;       // make room for next bit
        result |= (n & 1U); // copy lowest bit of n
        n >>= 1;            // process next bit
    }
    return result;
}

unsigned int reverseBits(unsigned int num) {
  unsigned int count = sizeof(num) * 8 - 1;
  unsigned int reverse_num = num;
  printf ("count = %d \n", count); /* o/p = 31 */
  num >>= 1;
  printf ("num = %d \n", num);  /*o/p = 1*/
  while(num) {
    reverse_num <<= 1;      /* rev_num = rev_num * 2 */
    printf ("rev_num = %d (num&1) = %d\n", reverse_num, (num&1));
    reverse_num |= num & 1;
    printf ("rev_num = %d (num >>=1) =%d\n", reverse_num, (num >>= 1));
    num >>= 1;  /*num = num / 2 = */
    count--;
  }
  reverse_num <<= count;
  printf ("reverse_num = %d \n", reverse_num);
  return reverse_num;
}

void test_1 () {
  uint32_t n = 22; // 00010110
  n = reverse_bits(n);
  debug ("op -> [%d]", n);
}

void test_2 () {
  int res, num;
  res =0; num = 3;
  res = reverseBits(num);
  printf ("num = %d res = %d\n", num, res);
}

int main () {
  test_1();
  return 0;
}

/**
   ./a.out
   count = 31
   num = 1
   rev_num = 6 (num&1) = 1
   rev_num = 7 (num >>=1) =0
   reverse_num = -1073741824
   num = 3 res = -1073741824
**/

/**
   test_1() -

   Each iteration takes the rightmost bit of n and appends it to result:
   bit
   ↓
   n       = 00010110     n & 1 = 0
   result  = 00000000

   result <<= 1
   result  = 00000000
   result |= 0
   result  = 00000000

   n >>= 1
   n       = 00001011

   Next iteration:
   n       = 00001011
   ↑
   bit = 1

   result <<= 1
   result  = 00000000

   result |= 1
   result  = 00000001

   n >>= 1
   n       = 00000101

   Continuing for all 8 positions eventually gives:
   Input:
   00010110

   Reverse:
   01101000

   For uint32_t, we do exactly 32 iterations, including leading zeros.
   Why not stop when n == 0?
   This would be wrong:
   while (n) {
   result <<= 1;
   result |= n & 1;
   n >>= 1;
   }

   because leading zeros in the original number must become trailing zeros in the reversed 32-bit result.
**/
