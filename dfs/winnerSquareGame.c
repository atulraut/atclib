/***
    https://leetcode.com/problems/stone-game-iv/
    Stone Game IV

    Alice and Bob take turns playing a game, with Alice starting first.

    Initially, there are n stones in a pile. On each player's turn,
    that player makes a move consisting of removing any non-zero
    square number of stones in the pile.

    Also, if a player cannot make a move, he/she loses the game.
    Given a positive integer n, return true if and only if
    Alice wins the game otherwise return false, assuming both players play optimally.

    Input: n = 1
    Output: true
    Explanation: Alice can remove 1 stone winning the game because
    Bob doesn't have any moves.

    Input: n = 2
    Output: false
    Explanation: Alice can only remove 1 stone, after that Bob removes
    the last one winning the game (2 -> 1 -> 0).

    Input: n = 4
    Output: true
    Explanation: n is already a perfect square, Alice can win with
    one move, removing 4 stones (4 -> 0).

    Constraints:

    1 <= n <= 105

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: 30 Jan 2022
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

bool winnerSquareGame(int n) {
  int i,k, *dp = (int*)calloc(sizeof(int), (n+1));
  for(i=1; i<=n; ++i)
    for(k=1; (k*k)<=i; k++)
      if(dp[i - (k*k)] == 0){
	dp[i] = 1;
	break;
      }
  return dp[--i];
}

void test() {
  int ret = 0;
  int n = 4;
  ret = winnerSquareGame(n);
  debug("Output = %d", ret);
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**
   => ./a.out
   [test] L=81 :Output = 1
**/
