/***
    Hard: https://leetcode.com/problems/dungeon-game/
    Dungeon(अंधारकोठडी) Game :

    The demons had captured the princess and imprisoned
    her in the bottom-right corner of a dungeon. The
    dungeon consists of m x n rooms laid out in a 2D grid.
    Our valiant knight was initially positioned in the
    top-left room and must fight his way through dungeon
    to rescue the princess.

    The knight has an initial health point represented by
    a positive integer. If at any point his health point
    drops to 0 or below, he dies immediately.

    Some of the rooms are guarded by demons (represented by
    negative integers), so the knight loses health upon
    entering these rooms; other rooms are either empty
    (represented as 0) or contain magic orbs that increase
    the knight's health (represented by positive integers).

    To reach the princess as quickly as possible, the knight
    decides to move only rightward or downward in each step.

    Return the knight's minimum initial health so that he
    can rescue the princess.

    Note that any room can contain threats or power-ups,
    even the first room the knight enters and the bottom-right
    room where the princess is imprisoned.

    Input: dungeon = [[-2,-3,3],[-5,-10,1],[10,30,-5]]
    Output: 7
    Explanation: The initial health of the knight must be at
    least 7 if he follows the optimal path: RIGHT-> RIGHT -> DOWN -> DOWN.

    Input: dungeon = [[0]]
    Output: 1

    Constraints:
    m == dungeon.length
    n == dungeon[i].length
    1 <= m, n <= 200
    -1000 <= dungeon[i][j] <= 1000

    https://www.youtube.com/watch?v=t1shZ8_s6jc - Finding min cost
    https://github.com/atulraut/atclib/blob/master/dynamic_prog/leetcode/minPathSum.c
    https://www.youtube.com/watch?v=4uUGxZXoR5o - this

    Date: Oct 1, 2021
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

int max(int a, int b) {
  return a > b ? a : b;
}

int min(int a, int b) {
  return a < b ? a : b;
}

int calculateMinimumHP(int** dungeon, int dungeonSize, int* dungeonColSize) {
  int n = dungeonSize;
  int m = *dungeonColSize;
  for(int i=n-1;i>=0;i--) {
    for(int j=m-1;j>=0;j--) {
      if(i == n-1 && j == m-1) {
	dungeon[i][j] = max((-1)*(dungeon[i][j])+1, 1);
	continue;
      }
      if(i == n-1) {
	dungeon[i][j] = max((-1)*(dungeon[i][j] - dungeon[i][j+1]), 1);
	continue;
      }
      if(j == m-1) {
	dungeon[i][j] = max((-1)*(dungeon[i][j] - dungeon[i+1][j]), 1);
	continue;
      }
      dungeon[i][j] = max((-1)*(dungeon[i][j] - min(dungeon[i+1][j], dungeon[i][j+1])), 1);
    }
  }
  return dungeon[0][0];
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
  int rows = 3;
  int cols = 3;
  int **grid = create_matrix(rows, cols);

  *(*(grid + 0) + 0) = -2;
  *(*(grid + 0) + 1) = -3;
  *(*(grid + 0) + 2) = 3;
  *(*(grid + 1) + 0) = -5;
  *(*(grid + 1) + 1) = -10;
  *(*(grid + 1) + 2) = 1;
  *(*(grid + 2) + 0) = 10;
  *(*(grid + 2) + 1) = 30;
  *(*(grid + 2) + 2) = -5;

  ret =  calculateMinimumHP(grid, rows, &cols);
  debug("Output = %d", ret);
  return 0;
}

/**
   => ./a.out
   [main] L=120 :Output = 7
**/
