/***
    Medium: Valid Sudoku

    Determine if a 9 x 9 Sudoku board is valid.
    Only the filled cells need to be validated according
    to the following rules:

    Each row must contain the digits 1-9 without repetition.
    Each column must contain the digits 1-9 without repetition.
    Each of the nine 3 x 3 sub-boxes of the grid must
    contain the digits 1-9 without repetition.

    Note:
    A Sudoku board (partially filled) could be valid but
    is not necessarily solvable.
    Only the filled cells need to be validated according
    to the mentioned rules.

    https://leetcode.com/problems/valid-sudoku/

    Date: 20 August 2021.
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

//bool isValidSudoku(char** board, int boardSize, int* boardColSize) {

bool isValidSudoku(char **board, int boardSize, int* boardColSize) {
  int r, c, value, check[3][9][10] = {0};
  r = boardSize;
  c = *boardColSize;
  for(r=0; r<9; r++)
    for(c=0; c<9; c++) {
      value = board[r][c] - '0';
      if(value != -2) {
	if(check[0][r][value]++ > 0)
	  return false;
	if(check[1][c][value]++ > 0)
	  return false;
	if(check[2][(r/3)*3 + c/3][value]++ > 0)
	  return false;
      }
    }
  return true;
}

int main (int argc, char **argv) {
  int ret = 0;
  int boardSize =9;
  int boardColSize = 9;
  char board[9][9] = {
    {'5', '3', '.', '.', '7', '.', '.', '.', '.'}
    ,{'6', '.','.','1','9','5','.','.','.'}
    ,{'.', '9','8','.','.','.','.','6','.'}
    ,{'8', '.','.','.','6','.','.','.','3'}
    ,{'4', '.','.','8','.','3','.','.','1'}
    ,{'7', '.','.','.','2','.','.','.','6'}
    ,{'.', '6','.','.','.','.','2','8','.'}
    ,{'.', '.','.','4','1','9','.','.','5'}
    ,{'.', '.','.','.','8','.','.','7','9'}
  };

  char *board2[9][9] = {
    {"5","3",".",".","7",".",".",".","."}
    ,{"6",".",".","1","9","5",".",".","."}
    ,{".","9","8",".",".",".",".","6","."}
    ,{"8",".",".",".","6",".",".",".","3"}
    ,{"4",".",".","8",".","3",".",".","1"}
    ,{"7",".",".",".","2",".",".",".","6"}
    ,{".","6",".",".",".",".","2","8","."}
    ,{".",".",".","4","1","9",".",".","5"}
    ,{".",".",".",".","8",".",".","7","9"}
  };
  ret= isValidSudoku(board, boardSize, &boardColSize);
  debug("Output = %d", ret);
  return 0;
}

/**

 **/
