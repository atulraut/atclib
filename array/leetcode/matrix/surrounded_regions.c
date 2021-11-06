/***
    https://leetcode.com/problems/surrounded-regions/
    Surrounded Regions

    Given an m x n matrix board containing 'X' and 'O',
    capture all regions that are 4-directionally surrounded by 'X'.
    A region is captured by flipping all 'O's into 'X's in that surrounded region.

    Input: board = [["X","X","X","X"],["X","O","O","X"],["X","X","O","X"],["X","O","X","X"]]
    Output: [["X","X","X","X"],["X","X","X","X"],["X","X","X","X"],["X","O","X","X"]]
    Explanation: Surrounded regions should not be on the border,
    which means that any 'O' on the border of the board are not flipped to 'X'.
    Any 'O' that is not on the border and it is not connected to an 'O' on the border
    will be flipped to 'X'. Two cells are connected if they are adjacent cells connected
    horizontally or vertically.

    Input: board = [["X"]]
    Output: [["X"]]

    Constraints:
    m == board.length
    n == board[i].length
    1 <= m, n <= 200
    board[i][j] is 'X' or 'O'.

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Status: pending
    Date: 5 Nov 2021
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

void search(char** board, int i, int j, int S, int C) {
  if (i < 0 || j < 0 || i >= S || j >= C || board[i][j] != 'O')
    return;
  board[i][j] = 'A';
  search(board, i + 1, j, S, C);
  search(board, i, j + 1, S, C);
  search(board, i - 1, j, S, C);
  search(board, i, j - 1, S, C);
}

void solve1(char** board, int S, int* C) {
  int i = -1, j = -1;

  while (++j < *C) {
    if (board[0][j] == 'O')
      search(board, 0, j, S, *C);
    if (board[S - 1][j] == 'O')
      search(board, S - 1, j, S, *C);
  }
  j = -1;
  while (++j < S) {
    if (board[j][*C - 1] == 'O')
      search(board, j, *C - 1, S, *C);
    if (board[j][0] == 'O')
      search(board, j, 0, S, *C);
  }
  i = -1;
  while (++i < S) {
    j = -1;
    while (++j < *C)
      if (board[i][j] == 'A')
	board[i][j] = 'O';
      else if (board[i][j] == 'O')
	board[i][j] = 'X';
  }
}

void check(char** board, int row, int col, int rowMax, int colMax) {
  if(row < 0 || row >= rowMax || col < 0 || col >= colMax)
    return;

  if(board[row][col] == 'O') {
    board[row][col] = '1';
    check(board, row - 1, col , rowMax, colMax);
    check(board, row , col - 1, rowMax, colMax);
    check(board, row + 1, col , rowMax, colMax);
    check(board, row, col + 1 , rowMax, colMax);
  }
}

void solve(char** board, int boardSize, int* boardColSize) {
  if(board == NULL || boardSize < 3 || *boardColSize < 3)
    return;

  int row, col;
  int rowMax = boardSize;
  int colMax = *boardColSize;

  /* Four loops below will traverse the permiter */
  /* They will convert all the 0 and connected 0 to 1 */

  /* First row */
  row = 0;
  for(col = 0; col < colMax; col++)
    check(board, row, col, rowMax, colMax);

  /* Last row */
  row = rowMax - 1;
  for(col = 0; col < colMax; col++)
    check(board, row, col, rowMax, colMax);

  /* First column */
  col = 0;
  for(row = 1; row < rowMax - 1; row++)
    check(board, row, col, rowMax, colMax);

  /* Last column */
  col = colMax - 1;
  for(row = 1; row < rowMax - 1; row++)
    check(board, row, col, rowMax, colMax);

  /* Replace remaining O with X */
  for(row = 0; row < rowMax; row++){
    for(col = 0; col < colMax; col++){
      if(board[row][col]=='O')
	board[row][col]='X';
    }
  }
  /* Replace Edge 1 or connected 1 to O */
  for(row = 0; row < rowMax; row++) {
    for(col = 0; col < colMax; col++) {
      if(board[row][col]=='1')
	board[row][col]='O';
    }
  }
}

int** create_matrix(int rows, int cols) {
  int** max = (int**)malloc(sizeof(int) * rows);
  for (int i=0; i<rows; ++i) {
    max[i] = (int*)malloc(sizeof(int *) * cols);
  }
  return max;
}

int main (int argc, char **argv) {
  int ret = 0;
  int boardSize = 4;
  int boardColSize = 4;

  int **grid = create_matrix(boardSize, boardColSize);

  *(*(grid + 0) + 0) = X;
  *(*(grid + 0) + 1) = X;
  *(*(grid + 0) + 2) = X;
  *(*(grid + 0) + 3) = X;

  *(*(grid + 1) + 0) = X;
  *(*(grid + 1) + 1) = 0;
  *(*(grid + 1) + 2) = 0;
  *(*(grid + 1) + 3) = X;

  *(*(grid + 2) + 0) = X;
  *(*(grid + 2) + 1) = X;
  *(*(grid + 2) + 2) = 0;
  *(*(grid + 2) + 3) = X;

  *(*(grid + 3) + 0) = X;
  *(*(grid + 3) + 1) = 0;
  *(*(grid + 3) + 2) = X;
  *(*(grid + 3) + 3) = X;

  solve(grid, boardSize, &boardColSize);
  debug("Output = %d", ret);
  return 0;
}

/**

 **/
