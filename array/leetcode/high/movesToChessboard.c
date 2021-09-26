/***
    Hard: Transform to Chessboard

    You are given an n x n binary grid board. In each move,
    you can swap any two rows with each other, or any two
    columns with each other.
    Return the minimum number of moves to transform the
    board into a chessboard board. If the task is impossible,
    return -1.

    A chessboard board is a board where no 0's and no 1's
    are 4-directionally adjacent.

    Input: board = [[0,1,1,0],[0,1,1,0],[1,0,0,1],[1,0,0,1]]
    Output: 2
    Explanation: One potential sequence of moves is shown.
    The first move swaps the first and second column.
    The second move swaps the second and third row.

    Input: board = [[0,1],[1,0]]
    Output: 0
    Explanation: Also note that the board with 0 in the top
    left corner, is also a valid chessboard.

    Input: board = [[1,0],[1,0]]
    Output: -1
    Explanation: No matter what sequence of moves you make,
    you cannot end with a valid chessboard.

    Constraints:
    n == board.length
    n == board[i].length
    2 <= n <= 30
    board[i][j] is either 0 or 1.

    https://leetcode.com/problems/transform-to-chessboard/

    Date: 26 Sept 2021
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

int movesToChessboard(int** board, int boardSize, int* boardColSize) {
  int rowSum = 0, colSum = 0, row = 0, col = 0;
  for (int i = 0; i < boardSize; ++i)
    for (int j = 0; j < boardSize; ++j)
      if (board[0][0] ^ board[i][0] ^ board[0][j] ^ board[i][j])
	return -1;
  for (int i = 0; i < boardSize; ++i) {
    rowSum += board[0][i];
    colSum += board[i][0];
    if((i % 2) == board[i][0]) row++;
    if((i % 2) == board[0][i]) col++;
  }

  if (boardSize / 2 > rowSum || rowSum > (boardSize + 1) / 2)
    return -1;
  if (boardSize / 2 > colSum || colSum > (boardSize + 1) / 2)
    return -1;

  if (boardSize % 2) {
    if (row % 2) row = boardSize - row;
    if (col % 2) col = boardSize - col;
  } else {
    row = boardSize - row < row ? boardSize - row : row;
    col = boardSize - col < col ? boardSize - col : col;
  }

  return (row + col) / 2;
}

int** create_matrix(int rows, int cols) {
  int** max = (int**)calloc(sizeof(int), rows);
  for (int i=0; i<rows; ++i) {
    max[i] = (int*)calloc(sizeof(int *),  cols);
  }
  return max;
}

int main (int argc, char **argv) {
  int ret = 0;
  int rows = 2;
  int cols = 2;
  int **board = create_matrix(rows, cols);

  *(*(board + 0) + 0) = 0;
  *(*(board + 0) + 1) = 1;
  *(*(board + 1) + 0) = 1;
  *(*(board + 1) + 1) = 0;

  int boardSize = rows;
  int boardColSize = cols;

  ret =  movesToChessboard(board, boardSize, &boardColSize);
  debug("Output = %d", ret);
  return 0;
}

/**
   => ./a.out
   [main] L=107 :Output = 0
**/
