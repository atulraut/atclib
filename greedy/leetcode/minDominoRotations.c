/***
    https://leetcode.com/problems/minimum-domino-rotations-for-equal-row/
    Minimum Domino Rotations For Equal Row

    In a row of dominoes, tops[i] and bottoms[i] represent the top and
    bottom halves of the ith domino. (A domino is a tile with two
    numbers from 1 to 6 - one on each half of the tile.)

    We may rotate the ith domino, so that tops[i] and bottoms[i]
    swap values.

    Return the minimum number of rotations so that all the values in
    tops are the same, or all the values in bottoms are the same.

    If it cannot be done, return -1.

    Input: tops = [2,1,2,4,2,2], bottoms = [5,2,6,2,3,2]
    Output: 2
    Explanation:
    The first figure represents the dominoes as given by tops and
    bottoms: before we do any rotations.
    If we rotate the second and fourth dominoes, we can make every
    value in the top row equal to 2, as indicated by the second figure.

    Input: tops = [3,5,1,2,3], bottoms = [3,6,3,3,4]
    Output: -1
    Explanation:
    In this case, it is not possible to rotate the dominoes to make one
    row of values equal.

    Constraints:

    2 <= tops.length <= 2 * 104
    bottoms.length == tops.length
    1 <= tops[i], bottoms[i] <= 6

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Sun Mar 20 07:42:06 PDT 2022
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

/***
    Algorithm: Approach 1: Greedy.

    Pick up the first element. It has two sides: A[0] and B[0].

    Check if one could make all elements in A row or B row to be
    equal to A[0]. If yes, return the minimum number of rotations needed.

    Check if one could make all elements in A row or B row to be
    equal to B[0]. If yes, return the minimum number of rotations needed.

    Otherwise return -1.
*/
int minDominoRotations(int* tops, int topsSize, int* bottoms, int bottomsSize) {
  int i,j, min = INT_MAX, bch= 0, tch = 0;

  //For all the dice
  for(i = 1; i<7; i++) {
    bch= 0;
    tch = 0;
    for(j = 0; j<topsSize; j++) {
      if( tops[j] == i || bottoms[j] == i) {
	if(tops[j] != i)
	  tch++;
	if(bottoms[j] != i)
	  bch++;
      } else {
	//Current dice number can not be solution
	break;
      }
    }
    if(j >= topsSize -1) {
      bch = bch<tch?bch:tch;
      min = min<bch?min:bch;
    }
  }
  return (min == INT_MAX?-1:min);
}

bool is_seen(int *seens, int seen_count, int target) {
  for(int i=0;i<seen_count;i++) {
    if(seens[i] == target) return true;
  }
  return false;
}

int minDominoRotations_(int *tops, int topsSize, int *bottoms, int bottomsSize) {
  assert(topsSize == bottomsSize);

  int already_search_n[6] = {0, 0, 0, 0, 0, 0};
  int i_seen = 0;

  int min_count = INT32_MAX;
  for(int i=0;i<topsSize;i++) {
    int all_to_n = tops[i];

    if(is_seen(already_search_n, i_seen, all_to_n)) {
      continue;
    } else {
      assert(i_seen<6);
      already_search_n[i_seen++] = all_to_n;
    }

    int count = 0;
    for(int j=0;j<topsSize;j++) {
      if((tops[j] != all_to_n) && (bottoms[j] == all_to_n)) {
	count++;
      } else if((tops[j] != all_to_n) && (bottoms[j] != all_to_n)) {
	break;
      }

      if((j == topsSize-1) && (min_count > count)) {
	min_count = count;
      }

      // printf("%d,%d, [%d]: %d\n", tops[j], bottoms[j], all_to_n, count);
    }
  }

  i_seen = 0;
  for(int i=0;i<bottomsSize;i++) {
    int all_to_n = bottoms[i];

    if(is_seen(already_search_n, i_seen, all_to_n)) {
      continue;
    } else {
      assert(i_seen<6);
      already_search_n[i_seen++] = all_to_n;
    }

    int count = 0;
    for(int j=0;j<bottomsSize;j++) {
      if((bottoms[j] != all_to_n) && (tops[j] == all_to_n)) {
	count++;
      } else if((bottoms[j] != all_to_n) && (tops[j] != all_to_n)) {
	break;
      }
      if((j == bottomsSize-1) && (min_count > count)) {
	min_count = count;
      }

      // printf("%d,%d, [%d]: %d\n", tops[j], bottoms[j], all_to_n, count);
    }
  }

  if(min_count == INT32_MAX) return -1;

  return min_count;
}

void test() {
  int ret = 0;
  int tops[]    = {2,1,2,4,2,2};
  int topsSize = sizeof(tops)/sizeof(tops[0]);
  int bottoms[] = {5,2,6,2,3,2};
  int bottomsSize = sizeof( bottoms)/sizeof(bottoms[0]);
  ret = minDominoRotations(tops, topsSize, bottoms, bottomsSize);
  debug("Output = %d", ret);
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**
   => ./a.out
   [test] L=173 :Output = 2
**/
