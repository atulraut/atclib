/***
    Hard : Shortest Distance from All Buildings

    You are given an m x n grid grid of values 0, 1, or 2, where:

    each 0 marks an empty land that you can pass by freely,
    each 1 marks a building that you cannot pass through, and
    each 2 marks an obstacle that you cannot pass through.
    You want to build a house on an empty land that reaches all
    buildings in the shortest total travel distance.
    You can only move up, down, left, and right.

    Return the shortest travel distance for such a house.
    If it is not possible to build such a house
    according to the above rules, return -1.

    The total travel distance is the sum of the distances
    between the houses of the friends and the meeting point.

    The distance is calculated using Manhattan Distance,
    where distance(p1, p2) = |p2.x - p1.x| + |p2.y - p1.y|.

    Input: grid = [[1,0,2,0,1],[0,0,0,0,0],[0,0,1,0,0]]
    Output: 7
    Explanation: Given three buildings at (0,0), (0,4),
    (2,2), and an obstacle at (0,2).
    The point (1,2) is an ideal empty land to build a house,
    as the total travel distance of 3+3+1=7 is minimal.
    So return 7.

    Input: grid = [[1,0]]
    Output: 1

    Input: grid = [[1]]
    Output: -1

    Constraints:

    m == grid.length
    n == grid[i].length
    1 <= m, n <= 50
    grid[i][j] is either 0, 1, or 2.
    There will be at least one building in the grid.

    https://leetcode.com/problems/shortest-distance-from-all-buildings/
    Date: 22 Sept 2021
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
#define min(x, y) (((x) < (y)) ? (x) : (y))

/* Method 1 */
struct BuildListNode {
  int row;
  int col;
  struct BuildListNode *next;
  unsigned int *bfs;
};

struct VListNode {
  int row;
  int col;
  struct VListNode *next;
};

#define elem(ARRAY, COL_SIZE, ROW, COL)		\
  ((ARRAY)[(ROW) * (COL_SIZE) + (COL)])

static inline void vlist_add(struct VListNode **root, struct VListNode *node) {
  node->next = *root;
  *root = node;
}

static inline struct VListNode *vlist_pop(struct VListNode **root)
{
  struct VListNode *ret = *root;

  if (ret != NULL)
    *root = ret->next;
  return ret;
}

static inline void blist_add(struct BuildListNode **root,
			     struct BuildListNode *node) {
  node->next = *root;
  *root = node;
}

int shortestDistance1(int** grid, int gridSize, int* gridColSize) {
  const int row_size = gridSize;
  const int col_size = gridColSize[0];
  int col;
  int row;
  const unsigned int offset = 1;
  unsigned int dist;
  unsigned int d;
  struct BuildListNode *blist = NULL;
  struct BuildListNode *bnew;
  struct BuildListNode *bnode;
  struct VListNode *freelist = NULL;
  struct VListNode *ngh_list = NULL;
  struct VListNode *new_ngh_list = NULL;
  struct VListNode *ngh;
  struct VListNode *node;
  unsigned int *bfs;
  int tot_size = row_size * col_size;
  int nr_buildings = 0;
  int mindist = INT_MAX;

  for (row = 0; row < row_size; row++) {
    for (col = 0; col < col_size; col++) {
      if (grid[row][col] == 1) {
	bnew = alloca(sizeof(struct BuildListNode));
	bnew->row = row;
	bnew->col = col;
	blist_add(&blist, bnew);
	nr_buildings++;
      }
    }
  }

  for (bnode = blist; bnode != NULL; bnode = bnode->next) {
    bfs = malloc(tot_size * sizeof(int));
    bnode->bfs = bfs;
    memset(bfs, 0, tot_size * sizeof(int));
    elem(bfs, col_size, bnode->row, bnode->col) = offset;
    ngh = vlist_pop(&freelist);
    if (ngh == NULL)
      ngh = alloca(sizeof(struct VListNode));
    ngh->row = bnode->row;
    ngh->col = bnode->col;
    vlist_add(&ngh_list, ngh);
    do {
      new_ngh_list = NULL;
      while (ngh_list != NULL) {
	node = vlist_pop(&ngh_list);
	col = node->col;
	row = node->row;
	vlist_add(&freelist, node);

	dist = elem(bfs, col_size, row, col) + 1;

	/* Northern neighbor */
	if (row >= 1 && grid[row - 1][col] == 0 &&
	    elem(bfs, col_size, row - 1, col) == 0) {
	  elem(bfs, col_size, row - 1, col) = dist;
	  ngh = vlist_pop(&freelist);
	  if (ngh == NULL)
	    ngh = alloca(sizeof(struct VListNode));
	  ngh->row = row - 1;
	  ngh->col = col;
	  vlist_add(&new_ngh_list, ngh);
	}

	/* Eastern neighbor */
	if (col + 1 < col_size  && grid[row][col + 1] == 0 &&
	    elem(bfs, col_size, row, col + 1) == 0) {
	  elem(bfs, col_size, row, col + 1) = dist;
	  ngh = vlist_pop(&freelist);
	  if (ngh == NULL)
	    ngh = alloca(sizeof(struct VListNode));
	  ngh->row = row;
	  ngh->col = col + 1;
	  vlist_add(&new_ngh_list, ngh);
	}

	/* Southern neighbor */
	if (row + 1 < row_size && grid[row + 1][col] == 0 &&
	    elem(bfs, col_size, row + 1, col) == 0) {
	  elem(bfs, col_size, row + 1, col) = dist;
	  ngh = vlist_pop(&freelist);
	  if (ngh == NULL)
	    ngh = alloca(sizeof(struct VListNode));
	  ngh->row = row + 1;
	  ngh->col = col;
	  vlist_add(&new_ngh_list, ngh);
	}

	/* Eastern neighbor */
	if (col  >= 1 && grid[row][col - 1] == 0 &&
	    elem(bfs, col_size, row, col - 1) == 0) {
	  elem(bfs, col_size, row, col - 1) = dist;
	  ngh = vlist_pop(&freelist);
	  if (ngh == NULL)
	    ngh = alloca(sizeof(struct VListNode));
	  ngh->row = row;
	  ngh->col = col - 1;
	  vlist_add(&new_ngh_list, ngh);
	}
      }
      ngh_list = new_ngh_list;
    } while(ngh_list != NULL);
  }

  for (row = 0; row < row_size; row++)
    for (col = 0; col < col_size; col++) {
      dist = 0;
      for (bnode = blist; bnode != NULL; bnode = bnode->next) {
	bfs = bnode->bfs;
	d = elem(bnode->bfs, col_size, row, col);
	if (d == offset || d == 0)
	  break;
	dist += d;
      }
      if (bnode == NULL) {
	if (dist < mindist)
	  mindist = dist;
      }
    }

  for (bnode = blist; bnode != NULL; bnode = bnode->next)
    free(bnode->bfs);

  if (mindist == INT_MAX)
    return -1;

  mindist -= nr_buildings * offset;
  return mindist;
}
/* Method 2 :*/
/*
  C BFS Implementation : 40ms
  Complexity analysis

  Time complexity : O(MxNxK),
  where m = number of rows, n = number of cols, k = number of gates.

  Let us start with the case with only one building.
  The breadth-first search takes at most m×n steps to reach all empty spaces,
  therefore the time complexity is O(MxN).
  And we are doing breadth-first search from K gates, thus O(MxNxK)

  Space complexity : O(MxN).
  The space complexity depends on the queue's size. We insert at most MxN points into the queue.

*/

#define EMPTY_LAND  0
#define BUILDING    1
#define OBSTACLE    2

#define MIN(x,y) ((x) < (y) ? (x) : (y))

int directions[4][2] = {{-1,0}, {1,0}, {0,-1}, {0,1}};

typedef struct queue {
  int front;
  int rear;
  int queueSize;
  int numOfItems;
  int *arrayRows;
  int *arrayCols;
} queue_t;

queue_t *createQueue(int queueSize) {
  queue_t *queue = malloc(sizeof(queue_t));
  if(!queue)
    return NULL;
  queue->front = 0;
  queue->rear = -1;
  queue->numOfItems = 0;
  queue->arrayRows = malloc(sizeof(int)*queueSize);
  queue->arrayCols = malloc(sizeof(int)*queueSize);

  if(!queue->arrayRows || !queue->arrayCols)
    return NULL;

  return queue;
}

static inline int getQueueSize(queue_t *queue) {
  return queue->numOfItems;
}

static inline bool isQueueEmpty(queue_t *queue) {
  return queue->numOfItems == 0;
}

static inline void queueEnqueue(queue_t *queue, int rowIdx, int colIdx) {
  queue->arrayRows[++queue->rear] = rowIdx;
  queue->arrayCols[queue->rear]   = colIdx;
  queue->numOfItems++;
}

static inline int queueDequeueRow(queue_t *queue) {
  return queue->arrayRows[queue->front];
}

static inline int queueDequeueCol(queue_t *queue) {
  queue->numOfItems--;
  return queue->arrayCols[queue->front++];
}

static inline void freeQueue(queue_t *queue) {
  free(queue->arrayRows);
  free(queue->arrayCols);
  free(queue);
}

void printArray(int rowIdxSize, int colIdxSize, int grid[][colIdxSize]) {
  printf("[\n");
  for(int i=0; i<rowIdxSize; i++) {
    printf("[");
    for(int j=0; j<colIdxSize; j++) {
      printf("%d,", grid[i][j]);
    }
    printf("],\n");
  }
  printf("]\n");
}

static inline void resetArr(int rowSize, int colSize, int Arr[][colSize]) {
  for(int i = 0; i<rowSize; i++) {
    for(int j = 0; j<colSize; j++) {
      Arr[i][j] = 0;
    }
  }
}

int shortestDistance2(int** grid, int gridSize, int* gridColSize) {
  if((gridSize == 0) || (*gridColSize == 0))
    return -1;

  int numOfRows = gridSize;
  int numOfCols = *gridColSize;
  int minDistance = INT32_MAX;
  int queueSize = numOfRows * numOfCols;

  // 2D-array to calculate total distance for each EMPTY_LAND to all buildings it can reach
  int distance[numOfRows][numOfCols];
  resetArr(numOfRows, numOfCols, distance);
  // 2D-array to keep track of number of buildings we can reach from an EMPTY_LAND
  int reach[numOfRows][numOfCols];
  resetArr(numOfRows, numOfCols, reach);
  // 2D-Array to keep track of visited nodes of input grid
  int visited[numOfRows][numOfCols];
  resetArr(numOfRows, numOfCols, visited);

  int numOfBuildings = 0;
  for(int row=0; row<numOfRows; row++) {
    for(int col=0; col<numOfCols; col++) {
      if(grid[row][col] == BUILDING) {
	numOfBuildings++;
	int level=1;
	// create queue for traversal of each building
	queue_t *queue = createQueue(queueSize);
	queueEnqueue(queue, row, col);
	// reset visited array since its new traversal
	resetArr(numOfRows, numOfCols, visited);
	// traverse until all nodes are visited
	while(!isQueueEmpty(queue)) {
	  int currLevelNodeCount = getQueueSize(queue);
	  // iterate over all nodes found at current level
	  // add each child node of current node to queue
	  for(int k=0; k<currLevelNodeCount; k++) {
	    int rowIdx = queueDequeueRow(queue);
	    int colIdx = queueDequeueCol(queue);
	    // traverse in all 4 directions of current node and find its valid child node
	    // if this child is already visited or is NOT a land, ignore it
	    for(int i=0; i<4; i++) {
	      int r = rowIdx + directions[i][0];
	      int c = colIdx + directions[i][1];
	      if((r >= 0) && (r < numOfRows) && (c >= 0) && (c < numOfCols) && (!visited[r][c]) && (grid[r][c] == EMPTY_LAND)) {
		// add level count to current count
		distance[r][c] += level;
		// printArray(numOfRows, numOfCols, distance);
		reach[r][c]++;
		visited[r][c] = 1;
		queueEnqueue(queue, r, c);
	      }
	    }
	  }
	  level++;
	}
	freeQueue(queue);
      }
    }
  }

  // printArray(numOfRows, numOfCols, distance);
  // printArray(numOfRows, numOfCols, visited);
  // printArray(numOfRows, numOfCols, reach);

  for (int i = 0; i < numOfRows; i++) {
    for (int j = 0; j < numOfCols; j++) {
      // check if current node can reach all the buildings or not
      if (grid[i][j] == EMPTY_LAND && reach[i][j] == numOfBuildings) {
	minDistance = min(minDistance, distance[i][j]);
      }
    }
  }
  return (minDistance == INT32_MAX) ? -1 : minDistance;
}

int** get_matrix(int row, int col) {
  int** mat = (int **)calloc(sizeof(int *), row);
  for (int i=0; i<row; ++i) {
    mat[i] = (int*)calloc(sizeof(int), col);
  }
  return mat;
}

int main (int argc, char **argv) {
  int ret = 0;
  int gridSize;
  int gridColSize;
  int** grid = get_matrix(3, 5);
  *(*(grid + 0) + 0 ) = 1;
  *(*(grid + 0) + 1 ) = 0;
  *(*(grid + 0) + 2 ) = 2;
  *(*(grid + 0) + 3 ) = 0;
  *(*(grid + 0) + 4 ) = 1;

  *(*(grid + 1) + 0 ) = 0;
  *(*(grid + 1) + 1 ) = 0;
  *(*(grid + 1) + 2 ) = 0;
  *(*(grid + 1) + 3 ) = 0;
  *(*(grid + 1) + 4 ) = 0;

  *(*(grid + 2) + 0 ) = 0;
  *(*(grid + 2) + 1 ) = 0;
  *(*(grid + 2) + 2 ) = 1;
  *(*(grid + 2) + 3 ) = 0;
  *(*(grid + 2) + 4 ) = 0;

  ret = shortestDistance2(grid, gridSize, &gridColSize);
  debug("Output = %d", ret);
  return 0;
}

/**

 **/
