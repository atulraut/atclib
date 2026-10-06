/***
    Find Winner on a Tic Tac Toe Game
    Tic-tac-toe is played by two players A and B on a 3 x 3 grid.
    Here are the rules of Tic-Tac-Toe:

    Players take turns placing characters into empty squares (" ").
    The first player A always places "X" characters, while the
    second player B always places "O" characters.
    "X" and "O" characters are always placed into empty
    squares, never on filled ones.
    The game ends when there are 3 of the same (non-empty)
    character filling any row, column, or diagonal.
    The game also ends if all squares are non-empty.
    No more moves can be played if the game is over.
    Given an array moves where each element is another array of
    size 2 corresponding to the row and column of the grid where
    they mark their respective character in the order in which
    A and B play.

    Return the winner of the game if it exists (A or B), in
    case the game ends in a draw return "Draw", if there
    are still movements to play return "Pending".

    You can assume that moves is valid (It follows the rules
    of Tic-Tac-Toe), the grid is initially empty and A will
    play first.

    Input: moves = [[0,0],[2,0],[1,1],[2,1],[2,2]]
    Output: "A"
    Explanation: "A" wins, he always plays first.
    "X  "    "X  "    "X  "    "X  "    "X  "
    "   " -> "   " -> " X " -> " X " -> " X "
    "   "    "O  "    "O  "    "OO "    "OOX"

    Input: moves = [[0,0],[1,1],[0,1],[0,2],[1,0],[2,0]]
    Output: "B"
    Explanation: "B" wins.
    "X  "    "X  "    "XX "    "XXO"    "XXO"    "XXO"
    "   " -> " O " -> " O " -> " O " -> "XO " -> "XO "
    "   "    "   "    "   "    "   "    "   "    "O  "

    Input: moves = [[0,0],[1,1],[2,0],[1,0],[1,2],[2,1],[0,1],[0,2],[2,2]]
    Output: "Draw"
    Explanation: The game ends in a draw since there are no moves to make.
    "XXO"
    "OOX"
    "XOX"

    Input: moves = [[0,0],[1,1]]
    Output: "Pending"
    Explanation: The game has not finished yet.
    "X  "
    " O "
    "   "

    Constraints:
    1 <= moves.length <= 9
    moves[i].length == 2
    0 <= moves[i][j] <= 2
    There are no repeated elements on moves.
    moves follow the rules of tic tac toe.

    https://leetcode.com/problems/find-winner-on-a-tic-tac-toe-game/
    Date: 20 Sept 2021.
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

char* tictactoe(int** moves1, int movesSize, int* movesColSize) {
  char temp[3][3] = {' '};
  int moves[5][2] = {
    {0,0},
    {2,0},
    {1,1},
    {2,1},
    {2,2}
  };

  for(int i=0; i<movesSize; i++)
    if(i % 2 == 0)
      temp[moves[i][0]][moves[i][1]] = 'X';
    else
      temp[moves[i][0]][moves[i][1]] = 'O';
  char win = 0;

  for(int i=0; i<3; i++) {
    if(temp[i][0] == temp[i][1] && temp[i][0] == temp[i][2]) //check row
      win = temp[i][0];
    if(temp[0][i] == temp[1][i] && temp[0][i] == temp[2][i]) //check col
      win = temp[0][i];
    if(temp[0][0] == temp[1][1] && temp[0][0] == temp[2][2]) //check diagonal
      win = temp[0][0];
    if(temp[0][2] == temp[1][1] && temp[0][2] == temp[2][0]) //check diagonal
      win = temp[0][2];
  }
  if(win)
    return win == 'X' ? "A" : "B";
  else {
    if(movesSize == 9)
      return "Draw";
    else
      return "Pending";
  }
}

char* tictactoe1(int** moves1, int movesSize, int* movesColSize) {
  int moves[5][2] = {
    {0,0},
    {2,0},
    {1,1},
    {2,1},
    {2,2}
  };

  char board[3][3];

  for(int i=0; i<3; i++)
    for(int j=0; j<3; j++)
      board[i][j] = ' ';

  for(int i=0; i<movesSize; i++)
    board[moves[i][0]][moves[i][1]] = i%2 ? 'O' : 'X';

  bool win = false;

  for(int i=0; i<3; i++) {
    if((board[i][0] != ' ' && board[i][0] == board[i][1] && board[i][1] == board[i][2]) ||
       (board[0][i] != ' ' && board[0][i] == board[1][i] && board[1][i] == board[2][i])) {
      win = true;
      break;
    }
  }

  if(!win &&
     ((board[0][0] != ' ' && board[0][0] == board[1][1] && board[1][1] == board[2][2]) ||
      (board[0][2] != ' ' && board[0][2] == board[1][1] && board[1][1] == board[2][0])))
        win = true;

  if(win) {
    if(movesSize%2)
      return "A";
    else return "B";
  } else if(movesSize == 9){
    return "Draw";
  } else {
    return "Pending";
  }
}

int** get_matrix(int row, int col) {
  int** mat = (int**)calloc(row, sizeof(int));
  for (int i=0; i<row; ++i)
    mat[i] = (int*)calloc(col, sizeof(int));

  return mat;
}

int main (int argc, char **argv) {
  char* ret = 0;
  int** moves;
  int movesSize = 5;
  int movesColSize = 2;
  int row = 5;
  int col = 2;

  //Input: moves = [[0,0],[2,0],[1,1],[2,1],[2,2]]
  moves = get_matrix(row, col);
  *(*(moves + 0) + 0) = 0;
  *(*(moves + 0) + 1) = 0;
  *(*(moves + 0) + 2) = 0;

  *(*(moves + 1) + 0) = 0;
  *(*(moves + 1) + 1) = 1;
  *(*(moves + 1) + 2) = 0;

  *(*(moves + 2) + 0) = 1;
  *(*(moves + 2) + 1) = 1;
  *(*(moves + 2) + 2) = 1;

  ret = tictactoe1(moves, movesSize, &movesColSize);
  debug("Output = %s", ret);
  return 0;
}

/**

 **/
