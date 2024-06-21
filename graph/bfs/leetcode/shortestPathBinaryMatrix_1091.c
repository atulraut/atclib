/***

    https://leetcode.com/problems/shortest-path-in-binary-matrix/
    091. Shortest Path in Binary Matrix - Medium

    Given an n x n binary matrix grid, return the length of the
    shortest clear path in the matrix. If there is no clear path, return -1.

    A clear path in a binary matrix is a path from the top-left cell
    (i.e., (0, 0)) to the bottom-right cell (i.e., (n - 1, n - 1)) such that:

    All the visited cells of the path are 0.
    All the adjacent cells of the path are 8-directionally connected
    (i.e., they are different and they share an edge or a corner).
    The length of a clear path is the number of visited cells of this path.

    Input: grid = [[0,1],[1,0]]
    Output: 2

    Input: grid = [[0,0,0],[1,1,0],[1,1,0]]
    Output: 4

    Input: grid = [[1,0,0],[1,1,0],[1,1,0]]
    Output: -1

    Constraints:
    n == grid.length
    n == grid[i].length
    1 <= n <= 100
    grid[i][j] is 0 or 1

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Mon 08 Apr 2024 08:03:13 PM PDT
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

#define debug(str,args...) printf("L=[%d] [%s] :| "str"\n", __LINE__, __func__, ##args)

typedef struct _pair_t {
  int x;
  int y;
} pair_t;

typedef pair_t queue_data_t;

typedef enum queue_er_em {
  QUEUE_OK = 0,
  QUEUE_EMPTY = 1,
  QUEUE_FULL = 2,
  QUEUE_ERROR = 0xFF
} queue_er_em;

typedef struct _queue_t {
  queue_data_t *value;
  int buf_size;
  int offer_i;
  int poll_i;
  int count;
} queue_t;

queue_t *create_queue(int buf_size) {
  queue_t *queue = malloc(sizeof(queue_t));
  memset(queue, 0, sizeof(queue_t));
  queue->buf_size = buf_size;
  queue->value = malloc(buf_size*sizeof(queue_data_t));
  memset(queue->value, 0, buf_size*sizeof(queue_data_t));

  return queue;
}

queue_er_em offer_queue(queue_t *queue, queue_data_t *tdata) {

  assert(queue->count < queue->buf_size);
  if(queue->count >= queue->buf_size)
    return QUEUE_ERROR;

  memcpy(&queue->value[queue->offer_i++], tdata, sizeof(queue_data_t));

  if(queue->offer_i == queue->buf_size)
    queue->offer_i = 0;

  queue->count++;
  return QUEUE_OK;
}

queue_er_em poll_queue(queue_t *queue, queue_data_t *rdata) {

  assert(queue->count > 0);
  if(queue->count < 1)
    return QUEUE_EMPTY;

  memcpy(rdata, &queue->value[queue->poll_i++], sizeof(queue_data_t));

  if(queue->poll_i == queue->buf_size)
    queue->poll_i = 0;

  queue->count--;
  return QUEUE_OK;
}

int get_queue_data_count(queue_t *queue) {
  return queue->count;
}

bool is_queue_empty(queue_t *queue) {
  return !(queue->count!=0);
}


int shortestPathBinaryMatrix(int **grid, int gridSize, int *gridColSize) {
  if(grid[0][0] == 1)
    return -1;

  queue_t *buf = create_queue(500);
  int dir[8][2] = {{-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}};

  pair_t pair = {
	 .x = 0,
	 .y = 0
  };

  pair_t temp;
  int count = 0;
  offer_queue(buf, &pair);

  while(!is_queue_empty(buf)) {
    int c = get_queue_data_count(buf);
    count++;
    for(int i=0;i<c;i++) {
      poll_queue(buf, &pair);
      // printf("%d, %d\n", pair.x, pair.y);
      if(pair.x == gridSize-1 && pair.y == gridColSize[0]-1) {
	return count;
      }
      for(int j=0;j<8;j++) {
	int tr = pair.x + dir[j][0];
	int tc = pair.y + dir[j][1];
	if(tr>=0 && tr<gridSize && tc>=0 && tc<gridColSize[0] && grid[tr][tc] == 0) {
	  temp.x = tr;
	  temp.y = tc;
	  offer_queue(buf, &temp);

	  grid[tr][tc] = -1;
	}
      }
    }
  }
  return -1;
}

int** create_matrix(int rows, int cols) {
  int** max = (int**)calloc(sizeof(int *), rows);
  for (int i=0; i<rows; ++i) {
    max[i] = (int*)calloc(sizeof(int),  cols);
  }
  return max;
}

void test() {
  int ret = 0;
  int rows=2, cols=2;
  int gridSize = rows;
  int gridColSize = cols;
  int **grid = create_matrix(rows, cols);

  *(*(grid + 0) + 0) = 0;
  *(*(grid + 0) + 1) = 1;

  *(*(grid + 1) + 0) = 1;
  *(*(grid + 1) + 1) = 0;

  ret = shortestPathBinaryMatrix(grid, gridSize, &gridColSize);
  debug("Output = %d", ret);
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**

 **/
