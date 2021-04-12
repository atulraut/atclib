/***
    https://leetcode.com/problems/longest-increasing-path-in-a-matrix/
    Hard: 329. Longest Increasing Path in a Matrix
    Given an m x n integers matrix, return the length of the longest increasing path in matrix.

    From each cell, you can either move in four directions: left, right, up, or down.
    You may not move diagonally or move outside the boundary (i.e., wrap-around is not allowed).

    Input: matrix = [[9,9,4],[6,6,8],[2,1,1]]
    Output: 4
    Explanation: The longest increasing path is [1, 2, 6, 9].
    Constraints:
    m == matrix.length
    n == matrix[i].length
    1 <= m, n <= 200
    0 <= matrix[i][j] <= 231 - 1

    Date: 04/10/2021 April
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

#define MAXN 2048
#define zip(x,y) ((x)*(col)+(y))

int max(int a, int b) {
    return a > b?a:b;
}

int dp[MAXN*MAXN];

int dfs(int x,int y,const int row,const int col,int last,int **mat) {
     if(x >= row || y >= col || x < 0 || y < 0 || mat[x][y] <= last)
        return 0;

    int t = zip(x,y);
    if(dp[t])
        return dp[t];

    int ret = dfs(x-1,y,row,col,mat[x][y],mat);

    ret = max(ret,dfs(x+1,y,row,col,mat[x][y],mat));
    ret = max(ret,dfs(x,y-1,row,col,mat[x][y],mat));
    ret = max(ret,dfs(x,y+1,row,col,mat[x][y],mat));

    return dp[t] = ++ret;
 }

 int longestIncreasingPath(int** mat, int row, int col) {
     int ret = 0;
     memset(dp,0,sizeof(int)*zip(row,col));
     for(int i = 0; i < row; i++)
        for(int j = 0; j < col; j++)
            ret = max(ret,dfs(i,j,row,col,mat[i][j] - 1,mat));
    return ret;
 }

int **getDynamicArray(int row, int col) {
  int i;
  int **ar;
  ar = (int **)malloc(row * sizeof(int *));
  for (i=0; i<row; i++)
    ar[i] = (int *)malloc(col * sizeof(int));
  printf ("In getDynamicArray \n");
  return ar;
}

void print_array (int **arr, int r, int c) {
  int i, j;
  debug("Enter !");
  for(i=0; i<3; i++) {
    for(j=0; j<3; j++) {
      printf ("--> %d \t", *(*(arr+i) +j) );
    }
     printf ("\n");
  }
}

void free_array(int** max, int row, int col) {
  for (int i=0; i<row; i++)
    free(max[i]);

  free(max);
}

int main () {
  int **matrix = getDynamicArray(3, 3);
  /*
  matrix[3][3] = {
    {9,9,4},
    {6,6,8},
    {2,1,1},
  };
  */
 *(*(matrix+0)+0) = 9;
 *(*(matrix+0)+1) = 9;
 *(*(matrix+0)+2) = 9;

 *(*(matrix+1)+0) = 6;
 *(*(matrix+1)+1) = 6;
 *(*(matrix+1)+2) = 8;

 *(*(matrix+2)+0) = 2;
 *(*(matrix+2)+1) = 1;
 *(*(matrix+2)+2) = 1;

 print_array(matrix, 3, 3);
  int row=3;
  int col=3;

  int ret = longestIncreasingPath(matrix, row, col);

  debug("ret = %d", ret);
  free_array(matrix, 3, 3);
  return 0;
}
