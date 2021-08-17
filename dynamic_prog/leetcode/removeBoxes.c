/***
    Hard: Remove Boxes

    You are given several boxes with different colors represented by different
    positive numbers.

    You may experience several rounds to remove boxes until there is no box left.
    Each time you can choose some continuous boxes with the same color (i.e.,
    composed of k boxes, k >= 1), remove them and get k * k points.

    Return the maximum points you can get.

    Input: boxes = [1,3,2,2,2,3,4,3,1]
    Output: 23
    Explanation:
    [1, 3, 2, 2, 2, 3, 4, 3, 1]
    ----> [1, 3, 3, 4, 3, 1] (3*3=9 points)
    ----> [1, 3, 3, 3, 1] (1*1=1 points)
    ----> [1, 1] (3*3=9 points)
    ----> [] (2*2=4 points)

    Input: boxes = [1,1,1]
    Output: 9

    Input: boxes = [1]
    Output: 1

    https://leetcode.com/problems/remove-boxes/
    Status : sigseg fault

    Date: 16 August 2021
    Fair Oaks, CA.
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

#define max(x, y) (((x) > (y)) ? (x) : (y))

int*** get_3d_matrix(int one, int rows, int cols) {
  int ***arr3D = (int***)malloc(sizeof(int) * rows);
  int i, j, k;

  arr3D = (int ***)malloc(one * sizeof(int **));

  for(int i=0; i<one; ++i) {
    arr3D[i] = (int **)malloc(sizeof(int*) * rows);

    for(j=0; j<rows; ++j) {
      arr3D[i][j] = (int*)malloc(cols * sizeof(int));
    }
  }
  return arr3D;
}

void deallocate3D(int*** arr3D, int l, int m) {
  int i,j;

  for(i=0;i<l;i++) {
    for(int j=0;j<m;j++) {
      free(arr3D[i][j]);
    }
    free(arr3D[i]);
  }
  free(arr3D);
}

int calculatePoints(int* boxes, int*** dp, int l, int r, int k) {
  if (l > r)
    return 0;

  while (r > l && boxes[r] == boxes[r - 1]) {
    r--;
    k++;
  }

  if (dp[l][r][k] != 0) {
    return dp[l][r][k];
  }

  dp[l][r][k] = calculatePoints(boxes, dp, l, r - 1, 0) + (k + 1) * (k + 1);

  for (int i = l; i < r; i++) {
    if (boxes[i] == boxes[r]) {
      dp[l][r][k] = max(dp[l][r][k], calculatePoints(boxes, dp, l, i, k + 1)
			+ calculatePoints(boxes, dp, i + 1, r - 1, 0));
    }
  }

  return dp[l][r][k];
}

int removeBoxes(int* boxes, int sz) {
  //int dp[100][100][100] = {0};
  int one=100;
  int rows=100;
  int cols=100;
  int***dp = get_3d_matrix(one, rows, cols);

  return calculatePoints(boxes, dp, 0, sz - 1, 0);
}

int main (int argc, char **argv) {
  int ret = 0;
  int rows = 3;
  int cols = 3;
  int boxes[] = {1, 3, 2, 2, 2, 3, 4, 3, 1};
  int sz = sizeof(boxes)/sizeof(boxes[0]);

  debug ("Matrix Size = %d", sz);

  ret = removeBoxes(boxes, sz);
  debug("Output = %d", ret);
  return 0;
}

/**
   => ./a.out
   [main] L=92 :Matrix Size = 9
   [main] L=95 :Output = 23
**/
