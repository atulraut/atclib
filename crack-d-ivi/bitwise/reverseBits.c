/*
copyrights : http://www.geeksforgeeks.org
----------------------
 i/p  | OR | & | XOR |  
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

unsigned int reverseBits(unsigned int num);

int main () {
  int res, num;
  res =0; num = 3;
  res = reverseBits(num);
  printf ("num = %d res = %d\n", num, res);
  return 0;
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
