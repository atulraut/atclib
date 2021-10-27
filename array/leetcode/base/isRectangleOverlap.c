/***
    https://leetcode.com/problems/rectangle-overlap/
    Rectangle Overlap

    An axis-aligned rectangle is represented as a list
    [x1, y1, x2, y2], where (x1, y1) is the coordinate
    of its bottom-left corner, and (x2, y2) is the coordinate
    of its top-right corner. Its top and bottom edges are
    parallel to the X-axis, and its left and right edges
    are parallel to the Y-axis.

    Two rectangles overlap if the area of their intersection
    is positive. To be clear, two rectangles that only touch
    at the corner or edges do not overlap.

    Given two axis-aligned rectangles rec1 and rec2, return
    true if they overlap, otherwise return false.

    Input: rec1 = [0,0,2,2], rec2 = [1,1,3,3]
    Output: true

    Input: rec1 = [0,0,1,1], rec2 = [1,0,2,1]
    Output: false

    Input: rec1 = [0,0,1,1], rec2 = [2,2,3,3]
    Output: false

    Constraints:
    rect1.length == 4
    rect2.length == 4
    -109 <= rec1[i], rec2[i] <= 109
    rec1 and rec2 represent a valid rectangle with a non-zero area.

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address isRectangleOverlap.c -lm

    Date: 27 Oct 2021
    Fair Oaks, CA.
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
  ({ typeof (a) _a = (a);	\
    typeof (b) _b = (b);	\
    _a > _b ? _a : _b; })
#define min(a,b)		\
  ({ typeof (a) _a = (a);	\
    typeof (b) _b = (b);	\
    _a < _b ? _a : _b; })
/*----------------------------------- Micro --------------------------------------*/

/**
   Approach #2: Check Area [Accepted]
   Intuition

   If the rectangles overlap, they have positive area.
   This area must be a rectangle where both dimensions
   are positive, since the boundaries of the intersection
   are axis aligned.

   Thus, we can reduce the problem to the one-dimensional
   problem of determining whether two line segments overlap.

   Algorithm
   Say the area of the intersection is width * height, where
   width is the intersection of the rectangles projected onto
   the x-axis, and height is the same for the y-axis.
   We want both quantities to be positive.

   The width is positive when min(rec1[2],
   rec2[2]) > max(rec1[0], rec2[0]), that is when the smaller
   of (the largest x-coordinates) is larger than the larger
   of (the smallest x-coordinates). The height is similar.
**/
bool isRectangleOverlap(int* rec1, int rec1Size, int* rec2, int rec2Size) {
  return (min(rec1[2], rec2[2]) > max(rec1[0], rec2[0]) && // width > 0
	  min(rec1[3], rec2[3]) > max(rec1[1], rec2[1]));  // height > 0
}

int main (int argc, char **argv) {
  int ret = 0;
  int rec1[] = {0,0,2,2};
  int rec1Size = sizeof(rec1)/sizeof(rec1[0]);;
  int rec2[] = {1,1,3,3};
  int rec2Size = sizeof(rec2)/sizeof(rec2[0]);;;

  ret = isRectangleOverlap(rec1, rec1Size,rec2, rec2Size);
  debug("Output = %d", ret);
  return 0;
}

/**
   => ./a.out
   [main] L=102 :Output = 1
**/
