/***
    Calculate Square without using * or carrot sign.
    https://www.geeksforgeeks.org/calculate-square-of-a-number-without-using-and-pow/
*/

#include <stdio.h>
#include <stdlib.h>
#include "../../at_lib.h"

int square(int num) {
  if (num < 0)
    num = -num;

  int result = 0, times = num;

  while (times > 0) {
    int possibleShifts = 0, currTimes = 1;

    while ((currTimes << 1) <= times) {
      currTimes = currTimes << 1;
      ++possibleShifts;
    }

    result = result + (num << possibleShifts);
    times = times - currTimes;
  }

  return result;
}

int main() {

  for (int n = 10; n <= 15; ++n)
    debug("n = %d  n^2 =%d ", n, square(n));
  return 0;
}

/**
   => ./a.out
   [main] L=30 :n = 10  n^2 =100
   [main] L=30 :n = 11  n^2 =121
   [main] L=30 :n = 12  n^2 =144
   [main] L=30 :n = 13  n^2 =169
   [main] L=30 :n = 14  n^2 =196
   [main] L=30 :n = 15  n^2 =225
**/
