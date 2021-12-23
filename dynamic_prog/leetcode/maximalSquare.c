/***
    https://leetcode.com/problems/maximal-square/
    Maximal Square

    Given an m x n binary matrix filled with 0's and 1's,
    find the largest square containing only 1's and return its area.

    Input: matrix = [["1","0","1","0","0"],["1","0","1","1","1"],["1","1","1","1","1"],["1","0","0","1","0"]]
    Output: 4

    Input: matrix = [["0","1"],["1","0"]]
    Output: 1

    Input: matrix = [["0"]]
    Output: 0

    Constraints:
    m == matrix.length
    n == matrix[i].length
    1 <= m, n <= 300
    matrix[i][j] is '0' or '1'.

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address maximalSquare.c -lm

    Date: 12/21/2021
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

int maximalSquare(char** matrix, int matrixSize, int* matrixColSize){
  int *dp = (int *)malloc(sizeof(int )*(*matrixColSize+1));
  memset(dp,'\0',sizeof(int )*(*matrixColSize+1));
  int maxlen = 0;
  int prev =0;

  for (int i = 1; i <= matrixSize; i++) {
    for (int j = 1; j <= *matrixColSize; j++) {
      int temp = dp[j];

      if (matrix[i-1][j-1] == '1') {
	dp[j] = min(min(dp[j - 1], prev), dp[j]) + 1;
	maxlen = maxlen > dp[j] ? maxlen : dp[j];
      } else {
	dp[j]=0;
      }

      prev = temp;
    }
  }

  for (int i=0; i<4; ++i)
      printf(" [%d]", dp[i]);
  printf ("\n\n");
  return (maxlen * maxlen);
}

char** create_matrix(int row, int col) {
  char **matrix = (char **)malloc(row*sizeof(char));
  for (int j=0; j<row; ++j)
    matrix[j] = (char *)malloc(col*sizeof(char*));

  return matrix;
}

int main (int argc, char **argv) {
  int re=0;
  char** ret;
  int matrixSize = 4;
  int matrixColSize = 5;

  ret = create_matrix(4, 5);
  *(*(ret + 0) + 0) = 1;
  *(*(ret + 0) + 1) = 0;
  *(*(ret + 0) + 2) = 1;
  *(*(ret + 0) + 3) = 0;
  *(*(ret + 0) + 4) = 0;

  *(*(ret + 1) + 0) = 1;
  *(*(ret + 1) + 1) = 0;
  *(*(ret + 1) + 2) = 1;
  *(*(ret + 1) + 3) = 1;
  *(*(ret + 1) + 4) = 1;

  *(*(ret + 2) + 0) = 1;
  *(*(ret + 2) + 1) = 1;
  *(*(ret + 2) + 2) = 1;
  *(*(ret + 2) + 3) = 1;
  *(*(ret + 2) + 4) = 1;

  *(*(ret + 3) + 0) = 1;
  *(*(ret + 3) + 1) = 0;
  *(*(ret + 3) + 2) = 0;
  *(*(ret + 3) + 3) = 1;
  *(*(ret + 3) + 4) = 0;

  for (int i=0; i<4; ++i) {
    for (int j=0; j<5; j++) {
      printf(" [%d]", ret[i][j]);
    }
    printf ("\n");
  }
  re = maximalSquare(ret, matrixSize, &matrixColSize);
  debug ("Output = %d", re);
  return 0;
}

/**

 **/
