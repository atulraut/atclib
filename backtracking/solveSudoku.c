/***
   Hard: Sudoku Solver

   Write a program to solve a Sudoku puzzle
   by filling the empty cells.

   A sudoku solution must satisfy all of the
   following rules:

    Each of the digits 1-9 must occur exactly
    once in each row.
    Each of the digits 1-9 must occur exactly
    once in each column.
    Each of the digits 1-9 must occur exactly
    once in each of the 9 3x3 sub-boxes of the grid.

    The '.' character indicates empty cells.

    https://leetcode.com/problems/sudoku-solver/

    Date: 21 August 2021
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

int free1(char (*board)[9], int *row, int *col ) {
  for(int i=0; i<9; i++){
    for(int j=0; j<9; j++) {
      if(board[i][j] == '.') {
	*row = i;
	*col = j;
	return 1;
      }
    }
  }
  return 0;
}

int safe(char (*board)[9], int row, int col, int num) {
  //check on col
  int x,y;
  for(int i=0; i<9; i++) {
    if(board[i][col] - '0' ==  num)
      return 0;
  }
  //check on row
  for(int i=0; i<9; i++) {
    if(board[row][i] - '0' == num)
      return 0;
  }

  //check on 3*3 grid;
  x = row - (row%3);
  y = col - (col%3);

  for(int i=0; i<3; i++) {
    for(int j=0; j<3; j++) {

      if(board[i+x][j+y]-'0' == num)
	return 0;
    }
  }
  return 1;
}

//int help(char** board) {
int help(char (*board)[9]) {
  int row, col;

  if(free1(board, &row, &col) == 0)
    return 1;
  for(int i=1; i<=9; i++) {
    if(safe(board, row, col, i)) {
      board[row][col] = i+'0';

      if(help(board))
	return 1;
      //backtracking
      board[row][col] = '.';
    }

  }//end of for for placing numbers
  return 0;

}

//void solveSudoku(char** board, int boardSize, int* boardColSize) {
void solveSudoku(char (*board)[9], int boardSize, int* boardColSize) {
  help(board);
}


char (*generate())[9] {
  static char arr[][9] =
  {
     {'5','3','.','.','7','.','.','.','.'},
     {'6','.','.','1','9','5','.','.','.'},
     {'.','9','8','.','.','.','.','6','.'},
     {'8','.','.','.','6','.','.','.','3'},
     {'4','.','.','8','.','3','.','.','1'},
     {'7','.','.','.','2','.','.','.','6'},
     {'.','6','.','.','.','.','2','8','.'},
     {'.','.','.','4','1','9','.','.','5'},
     {'.','.','.','.','8','.','.','7','9'},
   };

  return arr;
}

char (*create_sparse_matrix(int rows))[9] {
    char (*mat)[9];
    mat = (char(*)[9]) malloc(rows * 9 * sizeof(char));
    /*
      mat[9][9]= {
     {'5','3','.','.','7','.','.','.','.'},
     {'6','.','.','1','9','5','.','.','.'},
     {'.','9','8','.','.','.','.','6','.'},
     {'8','.','.','.','6','.','.','.','3'},
     {'4','.','.','8','.','3','.','.','1'},
     {'7','.','.','.','2','.','.','.','6'},
     {'.','6','.','.','.','.','2','8','.'},
     {'.','.','.','4','1','9','.','.','5'},
     {'.','.','.','.','8','.','.','7','9'},
   };
   */
    return mat;
}

void print_output(char (*board)[9]) {
  debug("Resolvoed Soduku! ");
  for (int i=0; i<9; ++i) {
    for (int j=9; j<9; ++j) {
      debug("%d ", board[i][j]);
    }
    debug ("");
  }
}

int main (int argc, char **argv) {
  int ret = 0;
  int boardSize;
  int boardColSize;

  char (*board)[9] = generate(9); //create_sparse_matrix(9);

  solveSudoku(board, boardSize, &boardColSize);
  print_output(board);

  debug("Output = %d", ret);
  return 0;
}

/**

 **/
