/***
    WAP : Power of Two using Bitwise and Normal way.
    To Compile :
    gcc poweroftwo.c -o aout -lm
*/
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#define debug(str,args...) printf("[%s] L=%d :"str"\n", __func__, __LINE__, ##args)

/* Trick: Any power of 2 variable, only 1 bit is set,
   hence & with -1 number always turns 0 & !num will
   return 1, so if 1, is power of 2.
   Extra check with && is to validate condition for 0.
   Else if user enter 0 it will return true for powerofTwo
*/
unsigned int powerOfTwo(unsigned int num) {
  unsigned int pos = 0;

  printf ("1. --> %d \n", (num & (num - 1)));
  printf ("2. --> %d \n", !(num & (num - 1)));

  // return (num && !(num & (num - 1)));
  return num > 0 && !(num & (num - 1));  /* Leet Code */
}

/***
    August 2020 Challenge:
    https://leetcode.com/problems/power-of-four/
    Given an integer (signed 32 bits), write a function to check whether it is a power of 4.
    Example 1:
    Input: 16
    Output: true
    Example 2:
    Input: 5
    Output: false
    Follow up: Could you solve it without loops/recursion?
    To Compile : gcc poweroftwo.c -o aout -lm
*/
bool isPowerOfFour(int num) {
  if (num == 1)
    return 1;
  if (num < 4)
    return 0;
  if ((num & (num-1)) ==0)  {
    printf("\n -> num = %d \n", num);
    int a = sqrt(num);
    printf("-> a  = %d \n", a);
    if (a * a != num)
      return 0;
    if ((a & (a -1))==0)
      return 1;
  }
  return 0;
}

int findPositionOfBit(unsigned int num) {
  unsigned int i = 1;
  unsigned int pos = 1;
  if (!powerOfTwo(num))
    return -1;

  debug ("num = %d, i = %d", num, i);
  while (!(i&num)) {
    debug ("(num&i) = %d", (num & i));
    i = i << 1;
    ++pos;
  }
  debug ("pos = %d ", pos);
  return pos;
}

/*
  You are Given Int, print its 4th LSB
*/
int bitAtPosition(int num) {
  return (num & (1 << 4)); //as needed 4 th LSB
}

int main(void) {
  int num = 4;
  if(powerOfTwo(num))
    printf("The num = %d is Power Of Two! \n", num);
  else
    printf("The numb = %d is Not Power Of Two! \n", num);
/*
  num = 8;
  printf("\n Find Position of num = %d & its = %d  \n", num, findPositionOfBit(num));
  num = 5;
  printf("Find Position of num = %d & its = %d  \n\n", num, findPositionOfBit(num));

  num = 24;
  printf("\n The num = %d & bit at position = %d \n", num, bitAtPosition(num));

  printf ("Is Power if Four = %d \n", isPowerOfFour(16));
  printf ("Is Power if Four = %d \n ", isPowerOfFour(5));
*/
  return 0;
}

/*
   gcc poweroftwo.c -o aout -lm
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
/***
    => ./aout
    1. --> 0
    2. --> 1
    The num = 4 is Power Of Two!
    1. --> 0
    2. --> 1

    Find Position of num = 8 & its = 4
    1. --> 4
    2. --> 0
    Find Position of num = 5 & its = -1

    The num = 24 & bit at position = 16

    -> num = 16
    -> a  = 4
    Is Power if Four = 1
    Is Power if Four = 0
*/
