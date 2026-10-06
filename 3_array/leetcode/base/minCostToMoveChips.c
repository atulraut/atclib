/***
    https://leetcode.com/problems/minimum-cost-to-move-chips-to-the-same-position
    Minimum Cost to Move Chips to The Same Position

    We have n chips, where the position of the ith chip is position[i].

    We need to move all the chips to the same position. In one step, we can
    change the position of the ith chip from position[i] to:

    position[i] + 2 or position[i] - 2 with cost = 0.
    position[i] + 1 or position[i] - 1 with cost = 1.
    Return the minimum cost needed to move all the chips to the same position.

    Input: position = [1,2,3]
    Output: 1
    Explanation: First step: Move the chip at position 3 to position 1 with cost = 0.
    Second step: Move the chip at position 2 to position 1 with cost = 1.
    Total cost is 1.

    Input: position = [2,2,2,3,3]
    Output: 2
    Explanation: We can move the two chips at position  3 to position 2.
    Each move has cost = 1. The total cost = 2.

    Input: position = [1,1000000000]
    Output: 1

    Constraints:
    1 <= position.length <= 100
    1 <= position[i] <= 10^9

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: 12/05/2021
    Folsom, CA.
*/

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

int minCostToMoveChips2(int* position, int positionSize){
  int even_cnt = 0;
  int odd_cnt = 0;
  for (int i=0; i<positionSize; ++i) {
    if (i % 2 == 0) {
      even_cnt++;
    } else {
      odd_cnt++;
    }
  }
  return min(odd_cnt, even_cnt);
}

int minCostToMoveChips1(int* chips, int chipsSize) {
  int odd=0;
  int i;
  for (i=0; i<chipsSize; i++)
    if ((chips[i] % 2)==1)
      odd++;
  if (odd > chipsSize-odd)
    return chipsSize-odd;
  else
    return odd;
}

int minCostToMoveChips(int* position, int positionSize) {
  int odd = 0;
  for (int i = 0; i < positionSize; ++i) {
    if (position[i]%2 == 1)
      ++odd;
  }
  return odd < positionSize - odd ? odd : positionSize - odd;
}

int main (int argc, char **argv) {
  int ret = 0;
  int position[] = {1, 2, 3};
  int positionSize = 3;

  ret =  minCostToMoveChips(position, positionSize);
  debug("Output = %d", ret);
  return 0;
}

/**
   => ./a.out
   [main] L=104 :Output = 1
**/
