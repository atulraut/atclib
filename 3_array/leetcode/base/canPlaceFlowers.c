/***
    https://leetcode.com/problems/can-place-flowers/
    Can Place Flowers

    You have a long flowerbed in which some of the plots are planted,
    and some are not. However, flowers cannot be planted in adjacent plots.

    Given an integer array flowerbed containing 0's and 1's, where 0
    means empty and 1 means not empty, and an integer n, return if n
    new flowers can be planted in the flowerbed without violating
    the no-adjacent-flowers rule.

    Input: flowerbed = [1,0,0,0,1], n = 1
    Output: true

    Input: flowerbed = [1,0,0,0,1], n = 2
    Output: false

    Constraints:

    1 <= flowerbed.length <= 2 * 104
    flowerbed[i] is 0 or 1.
    There are no two adjacent flowers in flowerbed.
    0 <= n <= flowerbed.length

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: 18 Jan, 2022
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

bool canPlaceFlowers(int* flowerbed, int flowerbedSize, int n) {
  int i = 0, count = 0;
  while (i < flowerbedSize) {
    if (flowerbed[i] == 0 && (i == 0 || flowerbed[i - 1] == 0) && (i == flowerbedSize - 1 || flowerbed[i + 1] == 0)) {
      flowerbed[i++] = 1;
      count++;
    }
    if(count>=n)
      return true;
    i++;
  }
  return false;
}

void test() {
  int ret = 0;
  int flowerbed[] = {1,0,0,0,1};
  int n = 1;
  int flowerbedSize = arrsz(flowerbed);
  debug ("Arr Size  %d", flowerbedSize);
  ret = canPlaceFlowers(flowerbed, flowerbedSize, n);
  debug("Output = %d", ret);
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**
   => ./a.out
   [test] L=78 :Arr Size  5
   [test] L=80 :Output = 1
**/
