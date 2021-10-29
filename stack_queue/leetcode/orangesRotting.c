/***
    https://leetcode.com/problems/rotting-oranges/
    Rotting Oranges

    You are given an m x n grid where each cell can have
    one of three values:

    0 representing an empty cell,
    1 representing a fresh orange, or
    2 representing a rotten orange.
    Every minute, any fresh orange that is 4-directionally
    adjacent to a rotten orange becomes rotten.

    Return the minimum number of minutes that must elapse until
    no cell has a fresh orange. If this is impossible, return -1.

    Input: grid = [[2,1,1],[1,1,0],[0,1,1]]
    Output: 4

    Input: grid = [[2,1,1],[0,1,1],[1,0,1]]
    Output: -1
    Explanation: The orange in the bottom left corner (row 2, column 0)
    is never rotten, because rotting only happens 4-directionally.
    Example 3:

    Input: grid = [[0,2]]
    Output: 0
    Explanation: Since there are already no fresh oranges at minute 0,
    the answer is just 0.

    Constraints:
    m == grid.length
    n == grid[i].length
    1 <= m, n <= 10
    grid[i][j] is 0, 1, or 2.

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: 28 Oct 2021
    Fair Oaks, CA.
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

typedef struct rotten {
  int min;
  int x;
  int y;
  struct rotten *next;
}   rotten;

typedef struct queue {
  rotten *front;
  rotten *back;
} queue;

void add(queue *rott,int min, int x, int y, int** grid) {
  rotten *new = (rotten *)malloc(sizeof(rotten));
  grid[x][y] = 2;
  new->min = min;
  new->x = x;
  new->y = y;
  new->next = NULL;
  if (!rott->front) {
    rott->front = rott->back = new;
    return;
  }
  rott->back->next = new;
  rott->back = new;
}

int orangesRotting(int** grid, int s, int* c) {
  int i = -1, j, res = 0;
  rotten *tmp;
  queue *rott = (queue *)malloc(sizeof(queue));
  rott->front = rott->back = NULL;

  while (++i < s) {
    j = -1;
    while (++j < *c)
      if (grid[i][j] == 2)
	add(rott, 0, i, j, grid);
  }

  while (rott->front) {
    tmp = rott->front;
    res = tmp->min;
    if (tmp->x > 0 && grid[tmp->x - 1][tmp->y] == 1)
      add(rott, tmp->min + 1, tmp->x - 1, tmp->y, grid);
    if (tmp->x + 1 < s && grid[tmp->x + 1][tmp->y] == 1)
      add(rott, tmp->min + 1, tmp->x + 1, tmp->y, grid);
    if (tmp->y > 0 && grid[tmp->x][tmp->y - 1] == 1)
      add(rott, tmp->min + 1, tmp->x, tmp->y - 1, grid);
    if (tmp->y + 1 < *c && grid[tmp->x][tmp->y + 1] == 1)
      add(rott, tmp->min + 1, tmp->x, tmp->y + 1, grid);
    rott->front = rott->front->next;
    free(tmp);
  }

  while (--i >= 0) {
    j = *c;
    while (--j >= 0)
      if (grid[i][j] == 1)
	return (-1);
  }
  return (res);
}

#define EMPTY 0
#define FRESH 1
#define ROTTEN 2

int directions[4][2] = {{-1,0},{1,0},{0,-1},{0,1}};

typedef struct queue_ {
  int front;
  int rear;
  int currItemCount;
  int *arrayRow;
  int *arrayCol;
} queue_t;

queue_t *createQueue(int queueSize) {
  queue_t *queue = malloc(sizeof(queue_t));
  if(!queue){
    return NULL;
  }
  queue->front = 0;
  queue->rear = -1;
  queue->currItemCount = 0;
  queue->arrayRow = malloc(sizeof(int)*queueSize);
  queue->arrayCol = malloc(sizeof(int)*queueSize);
  if(!queue->arrayRow || !queue->arrayCol){
    return NULL;
  }
  return queue;
}

bool isQueueEmpty(queue_t *queue) {
  return queue->currItemCount == 0;
}

void queueEnqueue(queue_t *queue, int rowIdx, int colIdx) {
  queue->arrayRow[++queue->rear] = rowIdx;
  queue->arrayCol[queue->rear] = colIdx;
  queue->currItemCount++;
}

int queueDequeueRow(queue_t *queue) {
  return queue->arrayRow[queue->front];
}

int queueDequeueCol(queue_t *queue) {
  queue->currItemCount--;
  return queue->arrayCol[queue->front++];
}

void freeQueue(queue_t *queue) {
  free(queue->arrayRow);
  free(queue->arrayCol);
  free(queue);
}

void printQueue(queue_t *queue, int queueSize) {
  printf("Row:    [");
  for(int i=0; i<queueSize; i++) {
    printf("%d,",queue->arrayRow[i]);
  }
  printf("]\n");
  printf("Column: [");
  for(int i=0; i<queueSize; i++) {
    printf("%d,",queue->arrayCol[i]);
  }
  printf("]\n");
}

int orangesRotting2(int** grid, int gridSize, int* gridColSize) {

  if((gridSize == 0) || (*gridColSize == 0)) {
    return 0;
  }

  int numOfRows = gridSize;
  int numOfCols = *gridColSize;
  int freshOranges = 0;
  int queueSize = numOfCols*numOfRows*2;

  queue_t *queue = createQueue(queueSize);

  for(int i=0; i<numOfRows; i++) {
    for(int j=0; j<numOfCols; j++) {
      if(grid[i][j] == ROTTEN) {
	queueEnqueue(queue, i, j);
      } else if(grid[i][j] == FRESH) {
	freshOranges++;
      }
    }
  }

  queueEnqueue(queue, -1, -1);
  int minutesElapsed = -1;
  // printQueue(queue, numOfRows, numOfCols);
  while(!isQueueEmpty(queue)) {
    // printQueue(queue, queueSize);
    int rowIdx = queueDequeueRow(queue);
    int colIdx = queueDequeueCol(queue);
    if(rowIdx == -1) {
      minutesElapsed++;
      if(!isQueueEmpty(queue)) {
	queueEnqueue(queue, -1, -1);
      }
      // printf("\nAdding -1 again\n");
      // printQueue(queue, queueSize);
    } else {
      for(int i=0; i<4; i++) {
	int r = rowIdx + directions[i][0];
	int c = colIdx + directions[i][1];
	if(r >= 0 && r < numOfRows && c >= 0 && c < numOfCols) {
	  if(grid[r][c] == FRESH){
	    grid[r][c] = ROTTEN;
	    freshOranges--;
	    queueEnqueue(queue, r, c);
	  }
	}
      }
      // printQueue(queue, queueSize);
    }
  }

  freeQueue(queue);
  return freshOranges == 0 ? minutesElapsed : -1;
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
  int gridSize = 3;
  int gridColSize = 3;

  int **grid = create_matrix(gridSize, gridColSize);
  *(*(grid + 0) + 0) = 2;
  *(*(grid + 0) + 1) = 1;
  *(*(grid + 0) + 2) = 1;
  *(*(grid + 1) + 0) = 1;
  *(*(grid + 1) + 1) = 1;
  *(*(grid + 1) + 2) = 0;
  *(*(grid + 2) + 0) = 0;
  *(*(grid + 2) + 1) = 1;
  *(*(grid + 2) + 2) = 1;

  ret = orangesRotting2(grid, gridSize, &gridColSize);
  debug("Output = %d", ret);
  return 0;
}

/**
   => ./a.out
   [main] L=283 :Output = 4
**/
