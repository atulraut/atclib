/***
    Medium : 695. Max Area of Island
    https://leetcode.com/problems/max-area-of-island/

    You are given an m x n binary matrix grid. An island is a
    group of 1's (representing land) connected 4-directionally (horizontal or vertical.)
    You may assume all four edges of the grid are surrounded by water.

    The area of an island is the number of cells with a value 1 in the island.

    Return the maximum area of an island in grid. If there is no island, return 0.

    Input: grid = [[0,0,1,0,0,0,0,1,0,0,0,0,0],[0,0,0,0,0,0,0,1,1,1,0,0,0],[0,1,1,0,1,
    0,0,0,0,0,0,0,0],[0,1,0,0,1,1,0,0,1,0,1,0,0],[0,1,0,0,1,1,0,0,1,1,1,0,0],
    [0,0,0,0,0,0,0,0,0,0,1,0,0],[0,0,0,0,0,0,0,1,1,1,0,0,0],[0,0,0,0,0,0,0,1,1,0,0,0,0]]
    Output: 6
    Explanation: The answer is not 11, because the island must be connected 4-directionally.

    Input: grid = [[0,0,0,0,0,0,0,0]]
    Output: 0

    Constraints:
    m == grid.length
    n == grid[i].length
    1 <= m, n <= 50
    grid[i][j] is either 0 or 1.

    Date: June 1, 2021
    San Diego, CA.

    Status : Needs a Fix for overflow Issue.
    gcc island/maxAreaOfIsland.c -o main -Wall -Werror -g -fsanitize=address
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

/***
 *              (x-1, y)
 *                  |
 *                  |
 * (x, y-1) ------------------ (x, y+1)
 *                  |
 *                  |
 *              (x+1, y)
 */

void mark_current_island(int (*grid)[5], int x, int y, int row, int col) {
  if (grid[x][y] == 1)
    printf ("row = %d col=%d\n", x, y);

  /* Check bondry condition, such that we cant go beyond array bondry. */
  if (x < 0 || x >= row || y <= 0 || grid[x][y] != 1)
    return;
  if ( (row == 0 && y == 0) || (row == 1 && y ==0))
    printf ("row = %d \n", row);
  grid[x][y] = 2;

  /* Make recursive call in all 4 adjacent directories. */
  mark_current_island(grid, x+1, y, row, col); /* DOWN  */
  mark_current_island(grid, x, y+1, row, col); /* RIGHT */
  mark_current_island(grid, x-1, y, row, col); /* TOP   */
  mark_current_island(grid, x, y-1, row, col); /* LEFT  */
}

int maxAreaOfIsland(int  (*grid)[5], int gridSize, int* gridColSize) {
  int i, j;
  int no_of_islands = 0;

  /* Emptry grid */
  if(*gridColSize == 0)
    return 0;

  debug ("gridSize=%d gridColSize=%d", gridSize, *gridColSize);

  /* Iterate for all cells of the array */
  for (i=0; i<4; i++) {
    for (j=0; j<5; j++) {
      if (grid[i][j] == 1) {
	//	printf ("row = %d col=%d\n", i, j);
	mark_current_island(grid, i, j, 4, 5);
	no_of_islands += 1;
      }
    }
  }
  printf ("[%s] no_of_islands = %d \n", __func__, no_of_islands );
  return no_of_islands;
}

int main () {
  //  int ret = 0;
  int i, j;
  int gridSize;
  int gridColSize;

  int grid[4][5] =  {
    {1, 1, 1, 1, 0},
    {1, 1, 0, 1, 0},
    {1 ,1 ,0, 0, 0},
    {0, 0, 0, 0, 0},
  };

  gridSize = 4;
  gridColSize = 5;

  int no_of_islands =  maxAreaOfIsland(grid, gridSize, &gridColSize);
  printf ("Output-> %d \n", no_of_islands);
  for (i=0; i<4; i++) {
    for (j=0; j<5; j++) {
      printf (" |%d| \t", grid[i][j]);
    }
    printf ("\n");
  }

  //  debug("Output = %d", ret);
  return 0;
}

/**

 **/
