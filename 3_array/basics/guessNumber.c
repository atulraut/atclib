/***
    https://leetcode.com/problems/guess-number-higher-or-lower/
    Guess Number Higher or Lower

    We are playing the Guess Game. The game is as follows:

    I pick a number from 1 to n. You have to guess which
    number I picked.

    Every time you guess wrong, I will tell you whether the
    number I picked is higher or lower than your guess.

    You call a pre-defined API int guess(int num), which
    returns 3 possible results:

    -1: The number I picked is lower than your guess (i.e. pick < num).
    1: The number I picked is higher than your guess (i.e. pick > num).
    0: The number I picked is equal to your guess (i.e. pick == num).
    Return the number that I picked.

    Input: n = 10, pick = 6
    Output: 6

    Input: n = 1, pick = 1
    Output: 1

    Input: n = 2, pick = 1
    Output: 1

    Input: n = 2, pick = 2
    Output: 2

    Constraints:
    1 <= n <= 231 - 1
    1 <= pick <= n

    Date: 10/11/2021
    Fair Oaks, CA.
 */

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

#define debug(str,args...) printf("[%s] L=%d :"str"\n", __func__, __LINE__, ##args)

// Dummy routine to make compiler Happy.
int guess(int num) {
        return 0;
}
/**
 * Forward declaration of guess API.
 * @param  num   your guess
 * @return      -1 if num is lower than the guess number
 *      1 if num is higher than the guess number
 *               otherwise return 0
 * int guess(int num);
 */

int guessNumber1(int n) {
        for (int i = 1; i < n; i++)
                if (guess(i) == 0)
                        return i;
        return n;
}

int guessNumber(int n) {
        int low = 1;
        int high = n;
        while (low <= high) {
                int mid = low + (high - low) / 2;
                int res = guess(mid);
                if (res == 0)
                        return mid;
                else if (res < 0)
                        high = mid - 1;
                else
                        low = mid + 1;
        }
        return -1;
}
int main (int argc, char **argv) {
  int ret = 0;

  debug("Output = %d", ret);
  return 0;
}

/**

 **/
