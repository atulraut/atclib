/***

    https://leetcode.com/problems/koko-eating-bananas/

    875. Koko Eating Bananas

    Koko loves to eat bananas. There are n piles of bananas, the ith pile
    has piles[i] bananas.
    The guards have gone and will come back in h hours.

    Koko can decide her bananas-per-hour eating speed of k.
    Each hour, she chooses some pile of bananas and eats k bananas from that pile.
    If the pile has less than k bananas, she eats all of them instead and will
    not eat any more bananas during this hour.

    Koko likes to eat slowly but still wants to finish eating all the bananas
    before the guards return.

    Return the minimum integer k such that she can eat all the bananas within h hours.

    Input: piles = [3,6,7,11], h = 8
    Output: 4

    Input: piles = [30,11,23,4,20], h = 5
    Output: 30

    Input: piles = [30,11,23,4,20], h = 6
    Output: 23

    Constraints:
    1 <= piles.length <= 104
    piles.length <= h <= 109
    1 <= piles[i] <= 109
    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Thu Oct 15 18:35:45 PDT 2026
    Folsom, CA.
 */

/*----------------------------------- Header --------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h> // va_arg
#include <ctype.h>
#include <limits.h>
#include <string.h>  /* malloc */
#include <stdbool.h>
#include <math.h>
#include <assert.h>
#include <stdint.h> /* uint32_t */
#include <unistd.h> /* sleep */

#define debug(str,args...) printf("L=[%d][%s]->[%s] :| "str"\n",__LINE__,__FILE__, __func__, ##args)

/**
   |<- voilates constrains ->|                        |
                         end | start
   [Too Slow                 |              Good Speed]   <<--- Input Piles
   k--> 1 2 3 ....                                   | max piles

   takes > h hours
   min value of k = 1
   max value would be arbitrarily range max(piles).
 **/

int minEatingSpeed_IK(int* piles, int pilesSize, int h) {
  int start = 1;
  unsigned int end   = 0; // Integer overflow with just INT
  int hours = 0;
  for (int i=0; i<pilesSize; ++i)
    end   += piles[i];

  while (start <= end) {
    int mid = start + (end-start) / 2;
    hours = 0;
    // for looks takes (n) : Loop to check which zone we are in.
    for (int i=0; i<pilesSize; ++i) { // mid here is eating speed
      hours += piles[i]/mid + (piles[i]%mid != 0); // use cieling to round up ind, 2/3 banans - turns out 2.
    }
    /* Now we know how much hours she takes */
    if (hours > h) // To slow zone : Left Zone
      start = mid + 1; // move toward the boundry
    else // Right Zone
      end = mid - 1;
   }
  return start;
}


void test() {
  int ret = 0;
  int piles[] = {3,6,7,11};
  int pilesSize = sizeof(piles)/sizeof(piles[0]);
  int h = 8;

  ret = minEatingSpeed_IK(piles, pilesSize, h);
  debug("Output = %d", ret);
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**
   L=[98][2_binary_search_modified/05_minEatingSpeed_LC-875.c]->[test] :| Output = 4
 **/
