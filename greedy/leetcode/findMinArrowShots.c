/***
    https://leetcode.com/problems/minimum-number-of-arrows-to-burst-balloons/
    452. Minimum Number of Arrows to Burst Balloons

    There are some spherical balloons taped onto a flat wall
    that represents the XY-plane. The balloons are represented
    as a 2D integer array points where points[i] = [xstart, xend]
    denotes a balloon whose horizontal diameter stretches between
    xstart and xend. You do not know the exact y-coordinates
    of the balloons.

    Arrows can be shot up directly vertically (in the positive y-direction)
    from different points along the x-axis. A balloon with xstart and
    xend is burst by an arrow shot at x if xstart <= x <= xend.
    There is no limit to the number of arrows that can be shot.
    A shot arrow keeps traveling up infinitely, bursting any balloons
    in its path.
    Given the array points, return the minimum number of arrows
    that must be shot to burst all balloons.

    Input: points = [[10,16],[2,8],[1,6],[7,12]]
    Output: 2
    Explanation: The balloons can be burst by 2 arrows:
    - Shoot an arrow at x = 6, bursting the balloons [2,8] and [1,6].
    - Shoot an arrow at x = 11, bursting the balloons [10,16] and [7,12].

    Input: points = [[1,2],[3,4],[5,6],[7,8]]
    Output: 4
    Explanation: One arrow needs to be shot for each balloon for a
    total of 4 arrows.

    Input: points = [[1,2],[2,3],[3,4],[4,5]]
    Output: 2
    Explanation: The balloons can be burst by 2 arrows:
    - Shoot an arrow at x = 2, bursting the balloons [1,2] and [2,3].
    - Shoot an arrow at x = 4, bursting the balloons [3,4] and [4,5].

    Constraints:

    1 <= points.length <= 105
    points[i].length == 2
    -231 <= xstart < xend <= 231 - 1

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address findMinArrowShots.c -lm

    Date: 12 Jan 2021
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

int cmpfunc(int** a, int** b) {
  return (*a)[1] - (*b)[1];
}

int findMinArrowShots(int** points, int pointsSize, int* pointsColSize) {
  int i, arrCount, pos;

  if((points==NULL) || (pointsSize==0)) {
    return 0;
  }
  qsort(points,pointsSize,sizeof(int*),cmpfunc);

  pos = points[0][1];
  arrCount = 1;
  for(i=1;i<pointsSize;i++) {
    if(points[i][0] <= pos)
      continue;
    arrCount++;
    pos = points[i][1];
  }
  return arrCount;
}

int** create_matrix(int rows, int cols) {
  int** max = (int**)calloc(sizeof(int), rows);
  for (int i=0; i<rows; ++i) {
    max[i] = (int*)calloc(sizeof(int *),  cols);
  }
  return max;
}

void print_matrix(int **grid, int row, int col) {
  for (int i=0; i<row; ++i) {
    for (int j=0; j<col; ++j) {
      debug ("-> %d", grid[i][j]);
    }
    printf ("\n");
  }
}

void test() {
  int ret = 0;
  int rows = 4;
  int cols = 2;
  int pointsSize = rows;
  int pointsColSize = cols;

  int **grid = create_matrix(rows, cols);

  *(*(grid + 0) + 0) = 10;
  *(*(grid + 0) + 1) = 16;
  *(*(grid + 1) + 0) = 2;
  *(*(grid + 1) + 1) = 8;
  *(*(grid + 2) + 0) = 1;
  *(*(grid + 2) + 1) = 6;
  *(*(grid + 3) + 0) = 7;
  *(*(grid + 3) + 1) = 12;

  print_matrix(grid, rows, cols);
  ret = findMinArrowShots(grid, pointsSize, &pointsColSize);
  printf("---------------------\n");
  debug("Output = %d", ret);
  print_matrix(grid, rows, cols);
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**
   Algorithm

   Now the algorithm is straightforward :
   Sort the balloons by end coordinate x_end.
   Initiate the end coordinate of a balloon which ends first : first_end = points[0][1].
   Initiate number of arrows: arrows = 1.
   Iterate over all balloons:
   If the balloon starts after first_end:
   Increase the number of arrows by one.
   Set first_end to be equal to the end of the current balloon.
   Return arrows.
*/
/**
   => ./a.out
   [print_matrix] L=110 :-> 10
   [print_matrix] L=110 :-> 16

   [print_matrix] L=110 :-> 2
   [print_matrix] L=110 :-> 8

   [print_matrix] L=110 :-> 1
   [print_matrix] L=110 :-> 6

   [print_matrix] L=110 :-> 7
   [print_matrix] L=110 :-> 12

   ---------------------------
   [test] L=137 :Output = 2
   ---------------------------
   [print_matrix] L=110 :-> 1
   [print_matrix] L=110 :-> 6

   [print_matrix] L=110 :-> 2
   [print_matrix] L=110 :-> 8

   [print_matrix] L=110 :-> 7
   [print_matrix] L=110 :-> 12

   [print_matrix] L=110 :-> 10
   [print_matrix] L=110 :-> 16
**/
