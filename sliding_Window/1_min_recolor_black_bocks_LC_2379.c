/***

    LC - 2379
    Minimum Recolors to Get K Consecutive Black Blocks

    You are given a 0-indexed string blocks of length n, where
    blocks[i] is either 'W' or 'B', representing the color of
    the ith block. The characters 'W' and 'B' denote the colors
    white and black, respectively.

    You are also given an integer k, which is the desired number
    of consecutive black blocks.

    In one operation, you can recolor a white block such that it
    becomes a black block.

    Return the minimum number of operations needed such that there
    is at least one occurrence of k consecutive black blocks.

    Input: blocks = "WBBWWBBWBW", k = 7
    Output: 3
    Explanation:
    One way to achieve 7 consecutive black blocks is to recolor the 0th,
    3rd, and 4th blocks
    so that blocks = "BBBBBBBWBW".
    It can be shown that there is no way to achieve 7 consecutive
    black blocks in less than 3 operations.
    Therefore, we return 3.

    Input: blocks = "WBWBBBW", k = 2
    Output: 0
    Explanation:
    No changes need to be made, since 2 consecutive black blocks already exist.
    Therefore, we return 0.

    Ref - https://www.youtube.com/watch?v=EUL7hBl6RME&t=73s

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Wed 12 Mar 2025 07:51:36 AM PDT
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

#define debug(str,args...) printf("L=[%d] [%s] :| "str"\n", __LINE__, __func__, ##args)

int min(int x, int y) { return x < y ? x : y; }


int minimumRecolors(char* blocks, int k) {

  int count=0;
  int ans=INT_MAX;

  for(int i=0; i<strlen(blocks); i++) {

    if(i-k >= 0 && blocks[i-k] == 'B')
      count--;

    if(blocks[i] == 'B')
      count++;

    if(ans> k-count)
      ans=k-count;
  }
  return ans;
}

int minimumRecolors__(char* blocks, int k) {

  int n = strlen(blocks);
  int black=0;
  int min_recoloring=INT_MAX;

  for(int i=0;i<n;++i) {
    if(blocks[i]=='B')
      black++;
    if(i>=k-1) {
      min_recoloring = min(k-black,min_recoloring);
      if(blocks[i-k+1]=='B')
	black--;
    }
  }
  return min_recoloring;
}

void test() {

  int ret = 0;
  char blocks0[] = "WBWBBBW";
  int k0 = 2;

  char blocks[] = "WBBWWBBWBW";
  int k = 7;
  debug("Output = %d", minimumRecolors(blocks, k));
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**
   => ./a.out
   L=[107] [test] :| Output = 3
**/
