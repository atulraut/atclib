/***
 * LeetCode :   Number of Islands
 * Given a 2d grid map of '1's (land) and '0's (water), count the number of islands.
 * An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically.
 * You may assume all four edges of the grid are all surrounded by water.
 * Example 1:
 * Input:
 * 11110
 * 11010
 * 11000
 * 00000
 * Output: 1
 * Example 2:
 * Input:
 * 11000
 * 11000
 * 00100
 * 00011
 * Output: 3
 * Logic : https://www.youtube.com/watch?v=9ZyLjjk536U
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

/* grid is a pointer to array of(size 5) integers.*/
int numIslands(int (*grid)[5], int gridSize, int* gridColSize) {
  int i, j, rows;
  int no_of_islands = 0;
  rows = gridSize;

  /* Emptry grid */
  if(*gridColSize == 0)
    return 0;

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

int **getDynamicArray(int row, int col) {
  int i, j;
  int **ar;
  ar = (int **)malloc(row * sizeof(int *));
  for (i=0; i<row; i++)
    ar[i] = (int *)malloc(col * sizeof(int));
  printf ("In getDynamicArray Input \n");
  return ar;
}

int main () {
  int i, j;
  int gridSize;
  int gridColSize;
  int (*ptr)[5];
  int grid[4][5] =  {
    {1, 1, 1, 1, 0},
    {1, 1, 0, 1, 0},
    {1 ,1 ,0, 0, 0},
    {0, 0, 0, 0, 0},
  };

  gridSize = 4;
  gridColSize = 5;

   int **arr = getDynamicArray(4, 2);
   for (i=0; i<4; i++) {
    for (j=0; j<5; j++) {
      arr[i][j] = rand() % 2;
      printf (" |%d| \t", arr[i][j]);
      //printf ("arr[%d][%d] = |%d| | \t",i,j, arr[i][j]);
    }
    printf ("\n");
  }
   ptr=grid;
   printf ("--> %d \n", sizeof(int));
  int no_of_islands =  numIslands(grid, gridSize, &gridColSize);
  printf ("Output-> %d \n", no_of_islands);
  for (i=0; i<4; i++) {
    for (j=0; j<5; j++) {
      printf (" |%d| \t", arr[i][j]);
    }
    printf ("\n");
  }

  return 0;
}
