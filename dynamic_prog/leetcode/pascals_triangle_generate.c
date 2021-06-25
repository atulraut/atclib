/***
    Easy: 118. Pascal's Triangle

    Given an integer numRows, return the first numRows of Pascal's triangle.

    In Pascal's triangle, each number is the sum of the two numbers directly above it as shown:

    Input: numRows = 5
    Output: [[1],[1,1],[1,2,1],[1,3,3,1],[1,4,6,4,1]]


    Input: numRows = 1
    Output: [[1]]

    Constraints:
    1 <= numRows <= 30

    https://leetcode.com/problems/pascals-triangle/
    Date: June 21, 2021 - International Yoga Day.
    San Diego, CA.
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


/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** generate(int numRows, int* returnSize, int** returnColumnSizes) {
    int i,j;
    int **array = (int**)malloc(sizeof(int*)*numRows);

    *returnSize = numRows;
    *returnColumnSizes = (int*)malloc(sizeof(int)*(*returnSize));

    for(i=0; i<numRows; ++i) {
        array[i] = (int*)malloc(sizeof(int)*(i+1));
        (*returnColumnSizes)[i] = i+1;
        array[i][0] = 1;
        array[i][i] = 1;
    }

    for(i=2; i<numRows; ++i) {
        for(j=0; j<i-1; ++j) {
            array[i][j+1] = array[i-1][j]+array[i-1][j+1];
        }
    }
    return array;
}

int main () {
  int numRows = 5;
  int returnSize;
  int* returnColumnSizes;

  int** ret = generate(numRows, &returnSize, &returnColumnSizes);

  for (int r=0; r<returnSize; ++r)
    for (int c=0; c<returnSize; ++c)
      debug("Output = %d", ret[r][c]);

  return 0;
}

/**

 **/
