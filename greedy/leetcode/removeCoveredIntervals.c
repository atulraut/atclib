/***
    https://leetcode.com/problems/remove-covered-intervals
     Remove Covered Intervals
     Given an array intervals where intervals[i] = [li, ri]
     represent the interval [li, ri), remove all intervals
     that are covered by another interval in the list.

     The interval [a, b) is covered by the interval [c, d)
     if and only if c <= a and b <= d.

     Return the number of remaining intervals.

     Input: intervals = [[1,4],[3,6],[2,8]]
     Output: 2
     Explanation: Interval [3,6] is covered by [2,8], therefore it is removed.

     Input: intervals = [[1,4],[2,3]]
     Output: 1
     Constraints:

     1 <= intervals.length <= 1000
     intervals[i].length == 2
     0 <= li <= ri <= 105
     All the given intervals are unique.

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address removeCoveredIntervals.c -lm

    Date: Sun Feb 20 09:39:53 PST 2022
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
#define max(a,b)		\
  ({ __typeof__ (a) _a = (a);	\
    __typeof__ (b) _b = (b);	\
    _a > _b ? _a : _b; })
#define min(a,b)		\
  ({ __typeof__ (a) _a = (a);	\
    __typeof__ (b) _b = (b);	\
    _a < _b ? _a : _b; })
/*----------------------------------- Micro --------------------------------------*/

void print_matrix(int** intervals, int intervalsSize, int* intervalsColSize) {
  debug("**>--------- Enter ----------<**");
  for (int i=0; i<intervalsSize; ++i) {
    for(int j=0; j<*intervalsColSize; ++j) {
      debug ("i=%d j=%d intervals=%d",i, j, intervals[i][j]);
    }
  }
}

int cmpfunc1(int** a, int** b) {
  int* pa = (*a);
  int* pb = (*b);

  if(pa[0]==pb[0]) // if same height, position small at the front
    return pa[1] - pb[1];
  else             // bigger height at the front
    return pb[0] - pa[0];
}

int cmpfunc (const void * a, const void * b) {
  return ((*(int**)a)[0] != (*(int**)b)[0]) ? ( (*(int**)a)[0] - (*(int**)b)[0] ): (*(int**)b)[1] - (*(int**)a)[1];
}

int removeCoveredIntervals(int** intervals, int intervalsSize, int* intervalsColSize) {
  int count=0, j, beforeR=-1;

  print_matrix(intervals, intervalsSize, intervalsColSize);
  qsort(intervals, intervalsSize, sizeof(int[2]), cmpfunc);
  print_matrix(intervals, intervalsSize, intervalsColSize);

  for(int i=0;i<intervalsSize;i++)
    if(intervals[i][1] > beforeR){
      beforeR = intervals[i][1];
      count++;
    }
  return count;
}

int** create_matrix(int rows, int cols) {
  int** max = (int**)calloc(sizeof(int *), rows);
  for (int i=0; i<rows; ++i) {
    max[i] = (int*)calloc(sizeof(int),  cols);
  }
  return max;
}

void test() {
  int ret = 0;
  int rows = 3;
  int cols = 2;
  int intervalsSize = rows;
  int intervalsColSize = cols;
  int **grid = create_matrix(rows, cols);

  *(*(grid + 0) + 0) = 1;
  *(*(grid + 0) + 1) = 4;
  *(*(grid + 1) + 0) = 3;
  *(*(grid + 1) + 1) = 6;
  *(*(grid + 2) + 0) = 2;
  *(*(grid + 2) + 1) = 8;
  ret = removeCoveredIntervals(grid, intervalsSize, &intervalsColSize);
  debug("Output = %d", ret);
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**
   => ./a.out
   [print_matrix] L=59 :**>--------- Enter ----------<**
   [print_matrix] L=62 :i=0 j=0 intervals=1
   [print_matrix] L=62 :i=0 j=1 intervals=4
   [print_matrix] L=62 :i=1 j=0 intervals=3
   [print_matrix] L=62 :i=1 j=1 intervals=6
   [print_matrix] L=62 :i=2 j=0 intervals=2
   [print_matrix] L=62 :i=2 j=1 intervals=8
   [print_matrix] L=59 :**>--------- Enter ----------<**
   [print_matrix] L=62 :i=0 j=0 intervals=1
   [print_matrix] L=62 :i=0 j=1 intervals=4
   [print_matrix] L=62 :i=1 j=0 intervals=2
   [print_matrix] L=62 :i=1 j=1 intervals=8
   [print_matrix] L=62 :i=2 j=0 intervals=3
   [print_matrix] L=62 :i=2 j=1 intervals=6
   [test] L=119 :Output = 2
**/
