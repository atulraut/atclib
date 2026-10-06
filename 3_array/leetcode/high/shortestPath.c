
/***
    Hard : You are given an m x n integer matrix grid
    where each cell is either 0 (empty) or 1 (obstacle).
    You can move up, down, left, or right from and to
    an empty cell in one step.

    Return the minimum number of steps to walk from the
    upper left corner (0, 0) to the lower right corner
    (m - 1, n - 1) given that you can eliminate at most
    k obstacles. If it is not possible to find such
    walk return -1.

    Input:
    grid =
    [[0,0,0],
    [1,1,0],
    [0,0,0],
    [0,1,1],
    [0,0,0]],
    k = 1
    Output: 6
    Explanation:
    The shortest path without eliminating any obstacle is 10.
    The shortest path with one obstacle elimination at position
    (3,2) is 6. Such path is (0,0) -> (0,1) -> (0,2) -> (1,2) -> (2,2) -> (3,2) -> (4,2).

    Input:
    grid =
    [[0,1,1],
    [1,1,1],
    [1,0,0]],
    k = 1
    Output: -1
    Explanation:
    We need to eliminate at least two obstacles to find such a walk.

    Constraints:

    m == grid.length
    n == grid[i].length
    1 <= m, n <= 40
    1 <= k <= m * n
    grid[i][j] == 0 or 1
    grid[0][0] == grid[m - 1][n - 1] == 0
    https://leetcode.com/problems/shortest-path-in-a-grid-with-obstacles-elimination/

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

typedef struct dataSet
{
  int x;
  int y;
  int obstacle;
  int path;
} D_SET;


int q_start;
int q_end;
int q_size;

void init_queue(int size)
{
  q_start = q_end = 0;
  q_size = size;
}

bool isQEmpty()
{
  return (q_start == q_end) ? true : false;
}

bool isQFull()
{
  return (q_end == (q_start + 1) % q_size ) ? true : false;
}

void q_append(D_SET data, D_SET *q)
{
  //printf("Append (%d,%d,%d,%d)\n", data.x, data.y, data.obstacle, data.path);
  q[q_start] = data;
  q_start = (q_start + 1) % q_size;

  //{
  //    int total = q_start - q_end;
  //    if(total < 0)total = q_size + total;
  //    printf("Queue size %d (start %d end %d)\n",total, q_start, q_end);
  //}
}

D_SET q_popleft(D_SET *q)
{
  D_SET data = q[q_end];
  //printf("pop (%d,%d,%d,%d)\n", data.x, data.y, data.obstacle, data.path);
  q_end = (q_end + 1) % q_size;

  //{
  //    int total = q_start - q_end;
  //    if(total < 0)total = q_size + total;
  //    printf("Queue size %d (start %d end %d)\n",total, q_start, q_end);
  //}

  return data;
}

D_SET q_getLeft(D_SET *q)
{
  return q[q_end];
}

int q_getSize()
{
  int total = q_start - q_end;
  if(total < 0)total = q_size + total;

  return total;
}

int checkNewPos(int k, int x_dim, int y_dim, int i, int j, D_SET data, D_SET *queue, int** grid, bool ***visited)
{
  int obstacle, path;
  obstacle = data.obstacle;
  path = data.path;

  //printf("checking (%d,%d).....obstacle = %d\n", i, j, obstacle);

  //printf("grid[%d][%d] = %d, obstacle = %d\n", j, i, grid[j][i], obstacle);
  if(grid[j][i] == 1 && obstacle < k && !(visited[j][i][obstacle + 1]))
    {
      //printf("visited[%d][%d][%d] = %d\n", j, i, obstacle + 1, visited[j][i][obstacle+1]);
      data.x = i;
      data.y = j;
      data.obstacle = obstacle + 1;
      data.path = path + 1;
      q_append(data, queue);
      visited[j][i][obstacle + 1] = true;
    }
  else if(grid[j][i] == 0 && !(visited[j][i][obstacle]))
    {
      //printf("visited[%d][%d][%d] = %d\n", j, i, obstacle, visited[j][i][obstacle]);
      if((i == x_dim-1) && (j == y_dim-1))
	{
	  return (data.path + 1);
	}
      else
	{
	  data.x = i;
	  data.y = j;
	  data.obstacle = obstacle;
	  data.path = path + 1;
	  q_append(data, queue);
	  visited[j][i][obstacle] = true;
	}
    }

  return -1;
}

int shortestPath(int** grid, int gridSize, int* gridColSize, int k){

  int obstacle, minPath = -1;
  int i, j;
  int x_dim = gridColSize[0], y_dim = gridSize;
  int depth = k + 1;
  D_SET data;
  //printf("queue size %d\n", x_dim * y_dim * depth);
  D_SET *queue = (D_SET *)malloc(x_dim * y_dim * depth * sizeof(D_SET));
  bool ***visited = (bool ***)malloc(y_dim * sizeof(bool **));

  if((x_dim == y_dim) && (x_dim == 1))return 0;

  init_queue(x_dim * y_dim * depth);

  //printf("x_dim = %d, y_dim = %d, depth = %d\n", x_dim, y_dim, depth);
  // create and initial the visisted array
  for(i = 0; i < y_dim; i++)
    {
      visited[i] = (bool **)malloc(x_dim * sizeof(bool *));
      for(j = 0; j < x_dim; j++)
	{
	  visited[i][j] = (bool *)malloc(depth * sizeof(bool));

	  for(obstacle = 0; obstacle < depth ; obstacle++)
	    {
	      visited[i][j][obstacle] = false;
	    }
	}
    }


  data.x = 0; data.y = 0; data.obstacle = 0; data.path = 0;
  q_append(data, queue);
  visited[0][0][0] = true;

  while(!isQEmpty())
    {
      //printf("==========================================\n");
      data = q_popleft(queue);
      printf("path = %d\n", data.path);

      // check 4 directions
      //printf("## 1 ## Left....\n");
      i = data.x-1; j = data.y;
      if(0 <= i && i < x_dim && 0 <= j && j < y_dim)
	{
	  minPath = checkNewPos(k, x_dim, y_dim, i, j, data, queue, grid, visited);
	  if(minPath != -1)break;
	}

      i = data.x+1; j = data.y;
      //printf("## 2 ## Right....\n");
      if(0 <= i && i < x_dim && 0 <= j && j < y_dim)
	{
	  minPath = checkNewPos(k, x_dim, y_dim, i, j, data, queue, grid, visited);
	  if(minPath != -1)break;
	}

      i = data.x; j = data.y-1;
      //printf("## 3 ## Up....\n");
      if(0 <= i && i < x_dim && 0 <= j && j < y_dim)
	{
	  minPath = checkNewPos(k, x_dim, y_dim, i, j, data, queue, grid, visited);
	  if(minPath != -1)break;
	}

      i = data.x; j = data.y+1;
      //printf("## 4 ## Down....\n");
      if(0 <= i && i < x_dim && 0 <= j && j < y_dim)
	{
	  minPath = checkNewPos(k, x_dim, y_dim, i, j, data, queue, grid, visited);
	  if(minPath != -1)break;
	}
      //printf("==========================================\n");
    }

  // free the visited array
  for(i = 0; i < y_dim; i++)
    {
      for(j = 0; j < x_dim; j++)
	{
	  free(visited[i][j]);
	}
      free(visited[i]);
    }
  free(visited);

  free(queue);

  return minPath;
}

/**
struct T {
  int x;
  int y;
  int r;
  int l;
};

struct Q {
  struct T data[2*41*41*41*41];
  int i;
  int j;
  int size;
  int max_size;
};

void init(struct Q* r) {
  r->i = r->j = r->size = 0;
  r->max_size = 2*41*41*41*41;
}

void push(struct Q* r, struct T t) {
  r->data[r->i++] = t;
  r->size ++;
  r->i = r->i%r->max_size;
}

struct T pop(struct Q* r) {
  struct T t = r->data[r->j++];
  r->j = r->j%r->max_size;
  r->size --;
  return t;
}

int empty(struct Q* r) {
  return r->size == 0;
}

int shortestPath(int** grid, int gridSize, int* gridColSize, int k) {
  struct Q q;
  struct T t = {0,0,k,0};
  int p;
  int ans = -1;
  char V[41*41*41*41];
  memset(V,0,sizeof(V));
  init(&q);
  push(&q, t);
  while (!empty(&q)) {
    t = pop(&q);
    p = (k+1)*(*gridColSize*t.x + t.y)+t.r;
    if (V[p]) {
      continue;
    }
    V[p] = 1;
    if (t.x == gridSize-1 && t.y == *gridColSize-1) {
      ans = t.l; break;
    }
    if (t.x > 0) {
      struct T t1 = {t.x-1,t.y,t.r,t.l+1};
      if (grid[t.x-1][t.y]) {
	t1.r --;
      }
      if (t1.r >= 0) {
	push(&q, t1);
      }
    }
    if (t.y > 0) {
      struct T t1 = {t.x,t.y-1,t.r,t.l+1};
      if (grid[t.x][t.y-1]) {
	t1.r --;
      }
      if (t1.r >= 0) {
	push(&q, t1);
      }
    }
    if (t.x < gridSize-1) {
      struct T t1 = {t.x+1,t.y,t.r,t.l+1};
      if (grid[t.x+1][t.y]) {
	t1.r --;
      }
      if (t1.r >= 0) {
	push(&q, t1);
      }
    }
    if (t.y < *gridColSize-1) {
      struct T t1 = {t.x,t.y+1,t.r,t.l+1};
      if (grid[t.x][t.y+1]) {
	t1.r --;
      }
      if (t1.r >= 0) {
	push(&q, t1);
      }
    }
  }
  return ans;
}
**/

int** create_matrix(int rows, int cols) {
  int** max = (int**)calloc(sizeof(int), rows);
  for (int i=0; i<rows; ++i) {
    max[i] = (int*)calloc(sizeof(int *),  cols);
  }
  return max;
}

int main (int argc, char **argv) {
  int ret = 0;
  int rows = 5;
  int cols = 3;

  int **grid = create_matrix(rows, cols);

  *(*(grid + 0) + 0) = 0;
  *(*(grid + 0) + 1) = 0;
  *(*(grid + 0) + 2) = 0;

  *(*(grid + 1) + 0) = 1;
  *(*(grid + 1) + 1) = 1;
  *(*(grid + 1) + 2) = 0;

  *(*(grid + 2) + 0) = 0;
  *(*(grid + 2) + 1) = 0;
  *(*(grid + 2) + 2) = 0;

  *(*(grid + 2) + 0) = 0;
  *(*(grid + 2) + 1) = 1;
  *(*(grid + 2) + 2) = 1;

  *(*(grid + 2) + 0) = 0;
  *(*(grid + 2) + 1) = 0;
  *(*(grid + 2) + 2) = 0;

  int gridSize = 5;
  int gridColSize = 3;
  int k = 1;

  ret = shortestPath(grid, gridSize, &gridColSize, k);
  debug("Output = %d", ret);
  return 0;
}

/**

 **/
