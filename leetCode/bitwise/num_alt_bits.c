/*
  Proble:  Binary Number with Alternating Bits
  Given a positive integer, check whether it has alternating bits:
  namely, if two adjacent bits will always have different values.
  Example 1:
   Input: 5
   Output: True
   Explanation:
   The binary representation of 5 is: 101
  Example 2:
   Input: 7
   Output: False
   Explanation:
   The binary representation of 7 is: 111.
   Date : 02 02 2020
   Author : Atul Raut
   Place : San Diego, CA, USA
*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

bool hasAlternatingBits(int n){
  int a,b;
  while(n){
    a = n % 2;
    n = n>>1;
    b = n % 2;
    if(a==b)
      return false;
  }
  return true;
}

int main () {
  int num = 7;
  bool ret;
  ret = hasAlternatingBits(num);
  printf ("--> O/P = %d \n", ret);
}

/**
   => ./a.out
   --> O/P = 0
**/
