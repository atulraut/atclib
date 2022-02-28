/***
    https://leetcode.com/problems/design-tic-tac-toe/
    Design Tic-Tac-Toe

    Assume the following rules are for the tic-tac-toe game
    on an n x n board between two players:

    A move is guaranteed to be valid and is placed on an empty block.
    Once a winning condition is reached, no more moves are allowed.
    A player who succeeds in placing n of their marks in a horizontal,
    vertical, or diagonal row wins the game.
    Implement the TicTacToe class:

    TicTacToe(int n) Initializes the object the size of the board n.
    int move(int row, int col, int player) Indicates that the player
    with id player plays at the cell (row, col) of the board. The
    move is guaranteed to be a valid move.

    Input
    ["TicTacToe", "move", "move", "move", "move", "move", "move", "move"]
    [[3], [0, 0, 1], [0, 2, 2], [2, 2, 1], [1, 1, 2], [2, 0, 1], [1, 0, 2], [2, 1, 1]]
    Output
    [null, 0, 0, 0, 0, 0, 0, 1]

    Explanation
    TicTacToe ticTacToe = new TicTacToe(3);
    Assume that player 1 is "X" and player 2 is "O" in the board.
    ticTacToe.move(0, 0, 1); // return 0 (no one wins)
    |X| | |
    | | | |    // Player 1 makes a move at (0, 0).
    | | | |

    ticTacToe.move(0, 2, 2); // return 0 (no one wins)
    |X| |O|
    | | | |    // Player 2 makes a move at (0, 2).
    | | | |

    ticTacToe.move(2, 2, 1); // return 0 (no one wins)
    |X| |O|
    | | | |    // Player 1 makes a move at (2, 2).
    | | |X|

    ticTacToe.move(1, 1, 2); // return 0 (no one wins)
    |X| |O|
    | |O| |    // Player 2 makes a move at (1, 1).
    | | |X|

    ticTacToe.move(2, 0, 1); // return 0 (no one wins)
    |X| |O|
    | |O| |    // Player 1 makes a move at (2, 0).
    |X| |X|

    ticTacToe.move(1, 0, 2); // return 0 (no one wins)
    |X| |O|
    |O|O| |    // Player 2 makes a move at (1, 0).
    |X| |X|

    ticTacToe.move(2, 1, 1); // return 1 (player 1 wins)
    |X| |O|
    |O|O| |    // Player 1 makes a move at (2, 1).
    |X|X|X|

    Constraints:
    2 <= n <= 100
    player is 1 or 2.
    0 <= row, col < n
    (row, col) are unique for each different call to move.
    At most n2 calls will be made to move.


    Follow-up: Could you do better than O(n2) per move() operation?
    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Mon Feb 28 10:21:41 PST 2022
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
#define max(a,b)				\
  ({ __typeof__ (a) _a = (a);			\
    __typeof__ (b) _b = (b);			\
    _a > _b ? _a : _b; })
#define min(a,b)				\
  ({ __typeof__ (a) _a = (a);			\
    __typeof__ (b) _b = (b);			\
    _a < _b ? _a : _b; })
/*----------------------------------- Micro --------------------------------------*/

typedef struct {
  int* rows; // rows[i] means the sum of all numbers in the ith row
  int* cols; // cols[i] means the sum of all numbers in the ith column
  int* diags; // diags[i] means the sum of all numbers in the ith diagnol
  int boardSize;
} TicTacToe;

/** Initialize your data structure here. */

TicTacToe* ticTacToeCreate(int n) {
  TicTacToe* obj = malloc(sizeof(TicTacToe));

  obj->rows = calloc(n, sizeof(int));
  obj->cols = calloc(n, sizeof(int));
  obj->diags = calloc(2, sizeof(int));

  obj->boardSize = n;

  return obj;
}

/** Player {player} makes a move at ({row}, {col}).
    @param row The row of the board.
    @param col The column of the board.
    @param player The player, can be either 1 or 2.
    @return The current winning condition, can be either:
    0: No one wins.
    1: Player 1 wins.
    2: Player 2 wins. */
int ticTacToeMove(TicTacToe* obj, int row, int col, int player) {
  int ans = 0;
  int code = (player - 1) * obj->boardSize + 1;  // Make sure the sum of all player 1 in a row / column / diagnol won't overlap with that of player 2

  obj->rows[row] += code;
  if (obj->rows[row] == code * obj->boardSize) {
    ans = player;
    goto END;
  }

  obj->cols[col] += code;
  if (obj->cols[col] == code * obj->boardSize) {
    ans = player;
    goto END;
  }

  if (row == col) {
    obj->diags[0] += code;
    if (obj->diags[0] == code * obj->boardSize) {
      ans = player;
      goto END;
    }
  }

  if (row + col == obj->boardSize-1) {
    obj->diags[1] += code;
    if (obj->diags[1] == code * obj->boardSize) {
      ans = player;
      goto END;
    }
  }

 END:
  // for (int i = 0; i < obj->boardSize; i++)
  // {
  //     printf("rows[%d] = %d\n", i, obj->rows[i]);
  //     printf("cols[%d] = %d\n", i, obj->cols[i]);
  // }
  // printf("\n");

  return ans;
}

void ticTacToeFree(TicTacToe* obj) {
  free(obj->rows);
  free(obj->cols);
  free(obj->diags);
  free(obj);
}

/**
 * Your TicTacToe struct will be instantiated and called as such:
 * TicTacToe* obj = ticTacToeCreate(n);
 * int param_1 = ticTacToeMove(obj, row, col, player);

 * ticTacToeFree(obj);
 */

void test() {
  int ret = 0;
  // Input
  // ["TicTacToe", "move", "move", "move", "move", "move", "move", "move"]
  // [[3], [0, 0, 1], [0, 2, 2], [2, 2, 1], [1, 1, 2], [2, 0, 1], [1, 0, 2], [2, 1, 1]]
  TicTacToe* obj = ticTacToeCreate(3);
  ret =ticTacToeMove(obj, 0, 0, 1);
  debug("Output = %d", ret);
  ret =ticTacToeMove(obj, 0, 2, 2);
  debug("Output = %d", ret);
  ret =ticTacToeMove(obj, 2, 2, 1);
  debug("Output = %d", ret);
  ret =ticTacToeMove(obj, 1, 1, 2);
  debug("Output = %d", ret);
  ret =ticTacToeMove(obj, 2, 0, 1);
  debug("Output = %d", ret);
  ret =ticTacToeMove(obj, 1, 0, 2);
  debug("Output = %d", ret);
  ret =ticTacToeMove(obj, 2, 1, 1);
  debug("Output = %d", ret);

}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**
   => ./a.out
   [test] L=198 :Output = 0
   [test] L=200 :Output = 0
   [test] L=202 :Output = 0
   [test] L=204 :Output = 0
   [test] L=206 :Output = 0
   [test] L=208 :Output = 0
   [test] L=210 :Output = 1
**/
