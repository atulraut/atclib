/***
    https://leetcode.com/problems/merge-intervals/
    Merge Intervals

    Given an array of intervals where intervals[i] = [starti, endi],
    merge all overlapping intervals, and return an array of the
    non-overlapping intervals that cover all the intervals in the input.

    Input: intervals = [[1,3],[2,6],[8,10],[15,18]]
    Output: [[1,6],[8,10],[15,18]]
    Explanation: Since intervals [1,3] and [2,6] overlaps, merge them into [1,6].
    Example 2:

    Input: intervals = [[1,4],[4,5]]
    Output: [[1,5]]
    Explanation: Intervals [1,4] and [4,5] are considered overlapping.

    Constraints:
    1 <= intervals.length <= 104
    intervals[i].length == 2
    0 <= starti <= endi <= 104

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: 12/23/2021
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

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int cmp(void* a,void* b) {
  if(((int**)a)[0][0] == ((int**)b)[0][0]){
    return ((int**)a)[0][1]-((int**)b)[0][1];
  }
  return ((int**)a)[0][0]-((int**)b)[0][0];
}

int** merge(int** intervals, int intervalsSize, int* intervalsColSize, int* returnSize, int** returnColumnSizes) {
  *returnSize=0;
  if(intervalsSize == 0) {
    return NULL;
  }

  qsort(intervals,intervalsSize,sizeof(intervals[0]),cmp);

  int** ret = (int**)malloc(intervalsSize*sizeof(int*));
  int* tmp = NULL;
  int flag = 0;

  for(int i=0; i<intervalsSize; i++) {
    if(flag == 0) {
      tmp = intervals[i];
      flag = 1;
      continue;
    }

    if(tmp[0]<=intervals[i][0]&&tmp[1] >= intervals[i][0]) {
      tmp[1] = tmp[1] > intervals[i][1] ? tmp[1] : intervals[i][1];
    } else {
      ret[(*returnSize)++] = tmp;
      flag = 0;
      i--;
    }
  }
  ret[(*returnSize)++] = tmp;
  returnColumnSizes[0] = (int*)malloc((*returnSize)*sizeof(int));

  for(int i=0; i<(*returnSize); i++) {
    returnColumnSizes[0][i] = 2;
  }
  return ret;
}

int** create_matrix(int rows, int cols) {
  int** max = (int**)malloc(sizeof(int) * rows);
  for (int i=0; i<rows; ++i) {
    max[i] = (int*)malloc(sizeof(int *) * cols);
  }
  return max;
}

int main (int argc, char **argv) {
  int ret = 0;
  int intervalsSize = 4;
  int intervalsColSize = 2;
  int returnSize;
  int* returnColumnSizes;

  int **grid = create_matrix(4, 2);

  *(*(grid + 0) + 0) = 1;
  *(*(grid + 0) + 1) = 3;

  *(*(grid + 1) + 0) = 2;
  *(*(grid + 1) + 1) = 6;

  *(*(grid + 2) + 0) = 8;
  *(*(grid + 2) + 1) = 10;

  *(*(grid + 3) + 0) = 15;
  *(*(grid + 3) + 1) = 18;

  int **grid1 = merge(grid, intervalsSize, &intervalsColSize, &returnSize, &returnColumnSizes);

  for (int i=0; i<returnSize; ++i) {
    for (int j=0; j<*returnColumnSizes; ++j) {
      printf("[%d]", grid1[i][j]);
    }
    printf ("\t");
  }
  printf("\n");
  return 0;
}

/**
   => ./a.out
   [1][6]	[8][10]	[15][18]
**/
