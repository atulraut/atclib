/*
  WAP : Power of Two using Bitwise and Normal way.
*/
#include <stdio.h>

/* Extra check with && is to validate condition for 0.
   Else if user enter 0 it will return true for powerofTwo
*/
unsigned int powerOfTwo(unsigned int num) {
  unsigned int pos = 0;

  printf ("1. --> %d \n", (num & (num - 1)));
  printf ("2. --> %d \n", !(num & (num - 1)));

  return (num && !(num & (num - 1)));
}

/* function to check if num is power of 2*/
unsigned int isPowerOfTwo(int num)
{
  if (num == 0)
    return 0;
  while (num != 1)
  {
      if (num%2 != 0)
         return 0;
      num = num/2;
  }
  return 1;
}

int findPositionOfBit(unsigned int num) {
  if (!powerOfTwo(num))
    return -1;
  unsigned int i = 1;
  unsigned int pos = 1;
  while (!(i&num)) {
    i = i << 1;
    ++pos;
  }
  return pos;
}

/*
  You are Given Int, print its 4th LSB
*/
int bitAtPosition(int num)
{
  return (num & (1 << 4)); //as needed 4 th LSB
}

int main(void) {
  int num = 4;
  if(powerOfTwo(num))
    printf("\n The num = %d is Power Of Two! \n", num);
  else
    printf("\n The numb = %d is Not Power Of Two! \n", num);

  num = 8;
  printf("\n Find Position of num = %d & its = %d  \n", num, findPositionOfBit(num));
  num = 5;
  printf("\n Find Position of num = %d & its = %d  \n\n", num, findPositionOfBit(num));

  num = 24;
  printf("\n The num = %d & bit at position = %d \n", num, bitAtPosition(num));
  return 0;
}

/* O/P :-->
  1. --> 0
  2. --> 1
  The num = 4 is Power Of  Two!

----------------------------
  Routine bitAtPosition   :
----------------------------
  128 64 32 16 8 4 2 10   : Val per bitwise
----------------------------
  7   6  5  4  3 2 1 0    : Bit Position
----------------------------
  0   0  0  1  1 0 0 0    : Num = 24
-----------------------------
*/

