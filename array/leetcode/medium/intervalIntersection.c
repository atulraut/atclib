/***
    https://leetcode.com/problems/interval-list-intersections/
    You are given two lists of closed intervals, firstList and secondList,
    where firstList[i] = [starti, endi] and secondList[j] = [startj, endj].
    Each list of intervals is pairwise disjoint and in sorted order.

    Return the intersection of these two interval lists.
    A closed interval [a, b] (with a <= b) denotes the set of real numbers
    x with a <= x <= b.

    The intersection of two closed intervals is a set of real numbers that
    are either empty or represented as a closed interval. For example, the
    intersection of [1, 3] and [2, 4] is [2, 3].

    Input:
    firstList = [[0,2],[5,10],[13,23],[24,25]],
    secondList = [[1,5],[8,12],[15,24],[25,26]]
    Output: [[1,2],[5,5],[8,10],[15,23],[24,24],[25,25]]
    Example 2:

    Input: firstList = [[1,3],[5,9]], secondList = []
    Output: []
    Example 3:

    Input: firstList = [], secondList = [[4,8],[10,12]]
    Output: []
    Example 4:

    Input: firstList = [[1,7]], secondList = [[3,10]]
    Output: [[3,7]]

    Constraints:

    0 <= firstList.length, secondList.length <= 1000
    firstList.length + secondList.length >= 1
    0 <= starti < endi <= 109
    endi < starti+1
    0 <= startj < endj <= 109
    endj < startj+1
    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: 26 Nov 2021 - Black Friday
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
int** intervalIntersection(int** A, int ASize, int* AColSize, int** B, int BSize, int* BColSize, int* returnSize, int** returnColumnSizes) {
  int l = (ASize>BSize)?ASize:BSize;
  int** result = malloc(sizeof(int*)*l*2);
  *returnColumnSizes = malloc(sizeof(int*)*l*2);
  int   count = 0;
  int   i=0;
  int   j=0;
  while (i < ASize && j < BSize) {
    if  ((A[i])[0] < (B[j])[0]) {             // [ {
      if ((A[i])[1] < (B[j])[0]) i++;     // []{}
      else if ((A[i])[1] < (B[j])[1]) {   // [{]}
	result[count] = malloc(sizeof(int)*2);
	(result[count])[0] = (B[j])[0];
	(result[count])[1] = (A[i])[1];
	i++;
	(*returnColumnSizes)[count++]=2;
      } else {                            // [{}]
	result[count] = malloc(sizeof(int)*2);
	(result[count])[0] = (B[j])[0];
	(result[count])[1] = (B[j])[1];
	j++;
	(*returnColumnSizes)[count++]=2;
      }

    } else {                                // { [
      if ((B[j])[1] < (A[i])[0]) j++;     // {}[]
      else if ((B[j])[1] < (A[i])[1]) {   // {[}]
	result[count] = malloc(sizeof(int)*2);
	(result[count])[0] = (A[i])[0];
	(result[count])[1] = (B[j])[1];
	j++;
	(*returnColumnSizes)[count++]=2;
      } else {                            // {[]}
	result[count] = malloc(sizeof(int)*2);
	(result[count])[0] = (A[i])[0];
	(result[count])[1] = (A[i])[1];
	i++;
	(*returnColumnSizes)[count++]=2;
      }

    }
  }
  *returnSize = count;
  return result;
}

int** create_matrix(int rows, int cols) {
  int** max = (int**)calloc(sizeof(int), rows);

  for (int i=0; i<rows; ++i) {
    max[i] = (int*)calloc(sizeof(int *),  cols);
  }
  return max;
}

int main (int argc, char **argv) {
  int **ret;
  int **grid1 = create_matrix(4, 2);

  *(*(grid1 + 0) + 0) = 0;
  *(*(grid1 + 0) + 1) = 2;
  *(*(grid1 + 1) + 0) = 5;
  *(*(grid1 + 1) + 1) = 10;
  *(*(grid1 + 2) + 0) = 13;
  *(*(grid1 + 2) + 1) = 23;
  *(*(grid1 + 3) + 0) = 24;
  *(*(grid1 + 3) + 1) = 26;

  int **grid2 = create_matrix(4, 2);

  *(*(grid2 + 0) + 0) = 1;
  *(*(grid2 + 0) + 1) = 5;
  *(*(grid2 + 1) + 0) = 8;
  *(*(grid2 + 1) + 1) = 12;
  *(*(grid2 + 2) + 0) = 15;
  *(*(grid2 + 2) + 1) = 24;
  *(*(grid2 + 3) + 0) = 25;
  *(*(grid2 + 3) + 1) = 26;

  int firstList[4][2]  = {
    {0,2},
    {5,10},
    {13,23},
    {24,25}
  };
  int asize = 4;
  int acolsz = 2;

  int secondList[4][2] = {
    {1,5},
    {8,1},
    {15,24},
    {25,26}
  };
  int bsize = 4;
  int bcolsz= 2;
  int returnSize;
  int* returnColumnSizes;

  ret = intervalIntersection(grid1, asize, &acolsz, grid2, bsize, &bcolsz, &returnSize, &returnColumnSizes);
  for (int i=0; i < returnSize; ++i) {
    for (int j=0; j < *returnColumnSizes; ++j) {
      printf("[%d]\t", ret[i][j]);
    }
    printf ("\n");
  }
  return 0;
}

/**
   => ./a.out
   [1]	[2]
   [5]	[5]
   [8]	[10]
   [15]	[23]
   [24]	[24]
   [25]	[26]
**/
