/***
    Medium: 1428. Leftmost Column with at Least a One
    https://leetcode.com/problems/leftmost-column-with-at-least-a-one/

    A row-sorted binary matrix means that all elements are 0 or 1 and
    each row of the matrix is sorted in non-decreasing order.

    Given a row-sorted binary matrix binaryMatrix, return the index
    (0-indexed) of the leftmost column with a 1 in it. If such an
    index does not exist, return -1.

    You can't access the Binary Matrix directly. You may only access
    the matrix using a BinaryMatrix interface:

    BinaryMatrix.get(row, col) returns the element of the matrix at
    index (row, col) (0-indexed).
    BinaryMatrix.dimensions() returns the dimensions of the matrix
    as a list of 2 elements [rows, cols], which means the matrix is rows x cols.

    Submissions making more than 1000 calls to BinaryMatrix.get will
    be judged Wrong Answer. Also, any solutions that attempt to
    circumvent the judge will result in disqualification.

    For custom testing purposes, the input will be the entire binary
    matrix mat. You will not have access to the binary matrix directly.

    Input: mat = [[0,0],[1,1]]
    Output: 0

    Input: mat = [[0,0],[0,1]]
    Output: 1

    Date: 27 April 2021
    San Diego, CA
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
 * // This is the BinaryMatrix's API interface.
 * // You should not implement it, or speculate about its implementation
 * struct BinaryMatrix {
 *     int (*get)(struct BinaryMatrix*, int, int);
 *     int* (*dimensions)(struct BinaryMatrix*);
 * };
 */

int leftMostColumnWithOne(struct BinaryMatrix* matrix) {
  int m = matrix->dimensions(matrix)[1];
  int n = matrix->dimensions(matrix)[0];

  for(int i=m-1,bound=0; i>=0; i--) {
    for(int j=bound; j<n; j++) {
      if(matrix->get(matrix,j,i)) {
	if(i==0) return 0;
	bound=j;
	break;
      } else if(j==n-1)
	return (i==m-1)?-1:i+1;
    }
  }
  return -1;
}


int main () {

}
