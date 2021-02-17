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
https://www.teksmart.in/2018/09/toggle-given-range-of-bits-of-unsigned.html

Toggle a given range of bits of an unsigned int
First discuss about what is bits toggling?

Number 12 is represented as 1100 in binary format. Mathematical representation like (12)10 = (1100)2.
So Number (1100)2 then complete toggled result is (0011)2, Here 1 is replaced with 0 and 0 with 1,
this is called bitwise complement.
But in some cases we need to toggle particular bit of Number. For example (1100)2 toggle 1st bit only,
then result become (1110)2, (bit counted from right to left, counting started with number 0),
this is single bit toggling.
Now we can start with toggle bits of number with given range. For example (1100)2 toggle bits from
1st to 3rd bit, then result become (0010)2. This is rang bits toggling.

Now we can start with how to code this in C.

Bitwise complement:
Suppose N is unsigned integer value.
 Then we can code in C like this:

unsigned int bitwise_complement(unsigned int N)
{
  return ~ N
}

Operator ~ is used to get bitwise complement.

Single bit toggling:
Single bit toggle is possible with following method:
Input is (1100)2  and 2nd bit need to toggle, then first create binary number which contain 1 as bit
value at 2nd bit. Suppose number is X, that we can create X like this 1 << 2 = (0100)2, Now do
XOR of both number (1100)2 ^ (0100)2 = (1000)2

Then we can code in C like this:

unsigned int single_bit_toggling(unsigned int N, unsigned int k)
{
  return (N ^ (1 << k));
}

Toggle a given range of bits:
Input is (1100)2  and range is from 1st bit to 3rd bit. Then first create binary number which contain
1 as a bit value from 1st bit to 3rd bit and other bits values are 0. So required value is (1110)2.
But how to created (1110)2 using given rang ? So first find range difference i.e. 3 -1 = 2,
then (1 <<  (2+1)) -1 = (7)10 = (0111)2 , Now shift this value with lowest rang value  (0111)2  << 1 = (1110)2,
 This is required value to do XOR with input
(1100)2 ^ (1110)2 =  (0010)2

Then we can code in C like this:

unsigned int rang_toggling(unsigned int N, unsigned int k , unsigned int l)
{
 //Here l > k
  return N ^ ((1<<(l-k)+1)-1)<<k;
}

*/

#include <stdio.h>

int setbit (int num, int bit);
int clearbit (int num, int bit);
int toggle (int num, int bit);
unsigned int range_toggling(unsigned int N,
				unsigned int start, unsigned int end);
int setallbits (int num);
unsigned int reverseBits(unsigned int num);


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

unsigned int range_toggling(unsigned int N,
				unsigned int start, unsigned int end) {
 //Here end > start
  return N ^ ((1<<(end-start)+1)-1)<<start;
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

/* Key: R-LXR */
unsigned int reverseBits(unsigned int n) {
  unsigned int rev = 0;

  // traversing bits of 'n' from the right
  while (n > 0)
    {
      // bitwise left shift
      // 'rev' by 1
      rev <<= 1;

      // if current bit is '1
      if (n & 1 == 1)
	rev ^= 1;

      // bitwise right shift
      // 'n' by 1
      n >>= 1;

    }

  // required number
  return rev;
}

int main () {
  int res, num, bit;
  res =0; num = 10; bit = 2;
  int start = 1, end = 3;
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
  num = 12;
  res = range_toggling(num, start, end);
  printf ("[range_toggling] num = %d, start = %d end = %d res = %d\n", num, start, end, res);
  return 0;
}
