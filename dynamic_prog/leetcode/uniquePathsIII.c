/***
    https://leetcode.com/problems/unique-paths-iii/
    You are given an m x n integer array grid where grid[i][j] could be:

    1 representing the starting square. There is exactly one starting square.
    2 representing the ending square. There is exactly one ending square.
    0 representing empty squares we can walk over.
    -1 representing obstacles that we cannot walk over.
    Return the number of 4-directional walks from the starting square to
    the ending square, that walk over every non-obstacle square exactly once.

    Input: grid = [[1,0,0,0],[0,0,0,0],[0,0,2,-1]]
    Output: 2
    Explanation: We have the following two paths:
    1. (0,0),(0,1),(0,2),(0,3),(1,3),(1,2),(1,1),(1,0),(2,0),(2,1),(2,2)
    2. (0,0),(1,0),(2,0),(2,1),(1,1),(0,1),(0,2),(0,3),(1,3),(1,2),(2,2)

    Input: grid = [[1,0,0,0],[0,0,0,0],[0,0,0,2]]
    Output: 4
    Explanation: We have the following four paths:
    1. (0,0),(0,1),(0,2),(0,3),(1,3),(1,2),(1,1),(1,0),(2,0),(2,1),(2,2),(2,3)
    2. (0,0),(0,1),(1,1),(1,0),(2,0),(2,1),(2,2),(1,2),(0,2),(0,3),(1,3),(2,3)
    3. (0,0),(1,0),(2,0),(2,1),(2,2),(1,2),(1,1),(0,1),(0,2),(0,3),(1,3),(2,3)
    4. (0,0),(1,0),(2,0),(2,1),(1,1),(0,1),(0,2),(0,3),(1,3),(1,2),(2,2),(2,3)

    Input: grid = [[0,1],[2,0]]
    Output: 0
    Explanation: There is no path that walks over every empty square exactly once.
    Note that the starting and ending square can be anywhere in the grid.

    Constraints:
    m == grid.length
    n == grid[i].length
    1 <= m, n <= 20
    1 <= m * n <= 20
    -1 <= grid[i][j] <= 2
    There is exactly one starting cell and one ending cell.

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address uniquePathsIII.c -lm

    Date: 1 Nov 2021
    Iron Point, CA.
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


#define OBSTACLE -1
#define SPACE 0
#define START 1
#define END 2
#define VISITED 3

int dfs(int **grid, int rowSize, int colSize, int rowIdx, int colIdx, int totalEmptySpaces) {

  if((rowIdx < 0) || (rowIdx >= rowSize) || (colIdx < 0) || (colIdx >= colSize) || (grid[rowIdx][colIdx] == OBSTACLE)) {
    return 0;
  }

  if(grid[rowIdx][colIdx] == END) {
    return totalEmptySpaces == 0;
  }

  // block this path until we visit every node
  grid[rowIdx][colIdx] = OBSTACLE;

  int path = 0;

  path = dfs(grid, rowSize, colSize, rowIdx-1, colIdx, totalEmptySpaces-1) +
    dfs(grid, rowSize, colSize, rowIdx+1, colIdx, totalEmptySpaces-1) +
    dfs(grid, rowSize, colSize, rowIdx, colIdx-1, totalEmptySpaces-1) +
    dfs(grid, rowSize, colSize, rowIdx, colIdx+1, totalEmptySpaces-1);

  // restore the path again, for new iteration
  grid[rowIdx][colIdx] = SPACE;

  return path;
}

int uniquePathsIII(int** grid, int gridSize, int* gridColSize) {
  int rowSize = gridSize, colSize = *gridColSize;
  int emptySpaces = 1, x = -1, y = -1;

  for(int i=0;i<rowSize;i++) {
    for(int j=0;j<colSize;j++) {
      if(grid[i][j] == SPACE) {
	// count total number of empty spaces
	emptySpaces++;
      }
      else if(grid[i][j] == START) {
	x = i;
	y = j;
      }
    }
  }
  return dfs(grid, rowSize, colSize, x, y, emptySpaces);
}

#define ROWS 3
#define COLS 4

int** create_matrix(int rows, int cols) {
    int** mat = (int**) malloc(rows * sizeof(int*));
    int i;
    for (i = 0; i < rows; i++)
        mat[i] = (int*)malloc(cols * sizeof(int));
    return mat;
}

int main (int argc, char **argv) {
  int ret = 0;
  int **obstacleGrid = create_matrix(ROWS, COLS);

  int gridSize = ROWS;//sizeof(obstacleGrid)/ sizeof(obstacleGrid[0]);;
  int gridColSize = COLS;

  *(*(obstacleGrid + 0) + 0) = 1;
  *(*(obstacleGrid + 0) + 1) = 0;
  *(*(obstacleGrid + 0) + 2) = 0;
  *(*(obstacleGrid + 0) + 3) = 0;

  *(*(obstacleGrid + 1) + 0) = 0;
  *(*(obstacleGrid + 1) + 1) = 0;
  *(*(obstacleGrid + 1) + 2) = 0;
  *(*(obstacleGrid + 1) + 3) = 0;

  *(*(obstacleGrid + 2) + 0) = 0;
  *(*(obstacleGrid + 2) + 1) = 0;
  *(*(obstacleGrid + 2) + 2) = 2;
  *(*(obstacleGrid + 2) + 3) = -1;

  ret = uniquePathsIII(obstacleGrid, gridSize, &gridColSize);
  //  [[1,0,0,0],[0,0,0,0],[0,0,2,-1]]
  debug("Output = %d", ret);
  return 0;
}

/**
   => ./a.out
   [main] L=158 :Output = 2
**/
