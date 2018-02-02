/*
S C T
O A X
SOCATX - To Remember
----------------------
 i/p  | & | OR | XOR |  
----------------------
0 | 0 | 0  | 0 | 0   |
----------------------
1 | 0 | 0  | 1 | 1   |
----------------------
0 | 1 | 0  | 1 | 1   |
----------------------
1 | 1 | 1  | 1 | 0   |
----------------------
*/

#include <stdio.h>

int setbit (int num, int bit);
int clearbit (int num, int bit);
int toggle (int num, int bit);
int setallbits (int num);
unsigned int reverseBits(unsigned int num);

int main () {
  int res, num, bit;
  res =0; num = 10; bit = 2;
  res = setbit (num, bit);
  printf ("num = %d, bit = %d res = %d\n", num, bit, res);
  res = clearbit (num, bit);
  printf ("num = %d, bit = %d res = %d\n", num, bit, res);
  res = toggle (num, bit);
  printf ("num = %d, bit = %d res = %d\n", num, bit, res);
  res = setallbits (num);
  printf ("num = %d, bit = %d res = %d\n", num, bit, res);
  res = reverseBits(num);
  printf ("num = %d, bit = %d res = %d\n", num, bit, res);
  return 0;
}

int setbit (int num, int bit) {
  
  num |= (1 << bit);
  return num;
}

int clearbit (int num, int bit) {
  num &= ~(1 << bit);
  return num;
}

int toggle (int num, int bit) {
  num ^= (1 << bit);
  return num;
}

/*
~(x & 0)
x & 0 will always result in 0, 
and ~ will flip all the bits to 1s.
*/
int setallbits (int num) {
  num = ~(num & 0);
  return num;
}

unsigned int reverseBits(unsigned int num) {
  unsigned int count = sizeof(num) * 8 - 1;
  unsigned int reverse_num = num;
     
  num >>= 1; 
  while(num)
    {
      reverse_num <<= 1;       
      reverse_num |= num & 1;
      num >>= 1;
      count--;
    }
  reverse_num <<= count;
  printf ("reverse_num = %d \n", reverse_num);
  return reverse_num;
}
