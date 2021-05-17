/***
    Medium: 1197. Minimum Knight Moves
    https://leetcode.com/problems/minimum-knight-moves/

    In an infinite chess board with coordinates from -infinity
    to +infinity, you have a knight at square [0, 0].

    A knight has 8 possible moves it can make, as illustrated below.
    Each move is two squares in a cardinal direction, then one
    square in an orthogonal direction.

    Return the minimum number of steps needed to move the knight
    to the square [x, y].  It is guaranteed the answer exists.

    Input: x = 2, y = 1
    Output: 1
    Explanation: [0, 0] → [2, 1]

    Input: x = 5, y = 5
    Output: 4
    Explanation: [0, 0] → [2, 1] → [4, 2] → [3, 4] → [5, 5]

    Constraints:
    |x| + |y| <= 300

    Date: 17 May 2021
    San Diego, CA.
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

#define NUM 301
int dp[NUM][NUM] = {};

int min(int x, int y) {
  if(x<y)
    return x;
  return y;
}

int minKnightMoves(int x, int y) {
  if(x < 0)
    x *= -1;
  if(y < 0)
    y *= -1;
  if(x + y == 0)
    return 0;
  if(x + y == 2)
    return 2;
  if(dp[x][y] != 0)
    return dp[x][y];

  return dp[x][y] = min(minKnightMoves(x-1, y-2), minKnightMoves(x-2, y-1)) + 1;
}

int main () {
  int ret = 0;
  int x = 2;
  int y = 1;

  ret = minKnightMoves(x, y);
  debug("Output = %d", ret);

  return 0;
}

/**
   => ./a.out
   [main] L=73 :Output = 1
**/
