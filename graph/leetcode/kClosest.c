/***
    https://leetcode.com/problems/k-closest-points-to-origin
    K Closest Points to Origin

    Given an array of points where points[i] = [xi, yi] represents
    a point on the X-Y plane and an integer k, return the k closest
    points to the origin (0, 0).

    The distance between two points on the X-Y plane is the Euclidean
    distance (i.e., √(x1 - x2)2 + (y1 - y2)2).

    You may return the answer in any order. The answer is guaranteed
    to be unique (except for the order that it is in).

    Input: points = [[1,3],[-2,2]], k = 1
    Output: [[-2,2]]
    Explanation:
    The distance between (1, 3) and the origin is sqrt(10).
    The distance between (-2, 2) and the origin is sqrt(8).
    Since sqrt(8) < sqrt(10), (-2, 2) is closer to the origin.
    We only want the closest k = 1 points from the origin, so the answer is just [[-2,2]].
    Example 2:

    Input: points = [[3,3],[5,-1],[-2,4]], k = 2
    Output: [[3,3],[-2,4]]
    Explanation: The answer [[-2,4],[3,3]] would also be accepted.


    Constraints:
    1 <= k <= points.length <= 104
    -104 < xi, yi < 104

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: 12/25/2021
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

int comp(const void *a, const void *b) {
    const int *ia = a;
    const int *ib = b;
    return *ia - *ib;
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** kClosest(int** points, int pointsSize, int* pointsColSize, int k, int* returnSize, int** returnColumnSizes) {
    int unsorted[pointsSize];
    int sorted[pointsSize];
    int dist;

    int **rtn = (int **)malloc(k * sizeof(int *));

    int *colSizes = (int *)malloc(k * sizeof(int));
    *returnColumnSizes = colSizes;

    int i, j;
    for(i=0;i<pointsSize;++i)
        sorted[i] = unsorted[i] = points[i][0]*points[i][0] + points[i][1]*points[i][1];

    qsort(&sorted[0], pointsSize, sizeof(sorted[0]), comp);
    dist=sorted[k-1];

    for(i=j=0;i<pointsSize;++i) {
        if (unsorted[i] <= dist) {
            rtn[j] = (int *)malloc(2 * sizeof(int));
            rtn[j][0] = points[i][0];
            rtn[j][1] = points[i][1];
            colSizes[j++] = 2;
        }
    }

    *returnSize = j;
    return rtn;
}

int main (int argc, char **argv) {
  int ret = 0;

  debug("Output = %d", ret);
  return 0;
}

/**

 **/
