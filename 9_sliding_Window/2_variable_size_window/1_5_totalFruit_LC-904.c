/***

    https://leetcode.com/problems/fruit-into-baskets/

    904. Fruit Into Baskets

    You are visiting a farm that has a single row of fruit trees arranged from
    left to right.
    The trees are represented by an integer array fruits where fruits[i] is
    the type of fruit the ith tree produces.

    You want to collect as much fruit as possible. However, the
    owner has some strict rules that you must follow:

    You only have two baskets, and each basket can only hold a single type of fruit.
    There is no limit on the amount of fruit each basket can hold.
    Starting from any tree of your choice, you must pick exactly one fruit from
    every tree (including the start tree) while moving to the right.
    The picked fruits must fit in one of your baskets.
    Once you reach a tree with fruit that cannot fit in your baskets, you must stop.
    Given the integer array fruits, return the maximum number of fruits you can pick.

    Input: fruits = [1,2,1]
    Output: 3
    Explanation: We can pick from all 3 trees.

    Input: fruits = [0,1,2,2]
    Output: 3
    Explanation: We can pick from trees [1,2,2].
    If we had started at the first tree, we would only pick from trees [0,1].

    Input: fruits = [1,2,3,2,2]
    Output: 4
    Explanation: We can pick from trees [2,3,2,2].
    If we had started at the first tree, we would only pick from trees [1,2].

    Constraints:
    1 <= fruits.length <= 105
    0 <= fruits[i] < fruits.length

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Sat Oct 10 09:14:03 PDT 2026
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
   Sliding-window approach : We maintain:
   int left = 0;
   int distinct = 0;
   int maxLen = 0;

   For each right:
   1. Add the incoming fruit and increase distinct if it is a new type.
   2. While distinct > 2, remove fruits from the left.
   3. Update the maximum valid window length.
**/
int totalFruit(int* fruits, int fruitsSize) {
  int *freq = calloc(fruitsSize, sizeof(int));
  if (!freq)
    return 0;

  int left = 0;
  int distinct = 0;
  int maxLen = 0;

  for (int right = 0; right < fruitsSize; right++) {

    // Add incoming fruit
    if (freq[fruits[right]]++ == 0)
      distinct++;

    // Shrink until at most 2 types remain
    while (distinct > 2) {

      // Remove outgoing fruit
      if (--freq[fruits[left]] == 0)
	distinct--;

      left++;
    }

    // Update maximum length
    int len = right - left + 1;

    if (len > maxLen)
      maxLen = len;
  }

  free(freq);
  return maxLen;
}

void test() {
  int ret = 0;
  int fruits[] = {1, 2, 3, 2, 2};
  int fruitsSize = 5;
  ret = totalFruit(fruits, fruitsSize);
  debug("Output = %d", ret);
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**
   L=[114][1_5_totalFruit_LC-904.c]->[test] :| Output = 4
**/
