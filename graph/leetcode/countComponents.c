/***
    Medium: 323. Number of Connected Components in an Undirected Graph
    You have a graph of n nodes. You are given an integer n and an
    array edges where edges[i] = [ai, bi] indicates that there is
    an edge between ai and bi in the graph.

    Return the number of connected components in the graph.

    Input: n = 5, edges = [[0,1],[1,2],[3,4]]
    Output: 2

    Input: n = 5, edges = [[0,1],[1,2],[2,3],[3,4]]
    Output: 1

    Constraints:
    1 <= n <= 2000
    1 <= edges.length <= 5000
    edges[i].length == 2
    0 <= ai <= bi < n
    ai != bi
    There are no repeated edges.

    https://leetcode.com/problems/number-of-connected-components-in-an-undirected-graph/

    Date: May 1, 2021.
    San Diego, CA.
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
#define ROWS 3
#define COLS 2

typedef struct _GNode {
  int data;
  struct _GNode *next;
} GNode;

typedef struct _Graph {
  int v;
  GNode **List;
} Graph;

Graph *initGraph(int v) {
  Graph *g = (Graph *)malloc(sizeof(Graph));
  g->v = v;
  g->List = (GNode **)malloc(sizeof(GNode *) * v);
  for(int i = 0; i < v; i ++)
    g->List[i] = NULL;
  return g;
}

void addEdge(Graph *g, int src, int dest) {
  GNode *node = (GNode *)malloc(sizeof(GNode));
  node->data = dest;
  node->next = g->List[src];
  g->List[src] = node;

  GNode *node1 = (GNode *)malloc(sizeof(GNode));
  node1->data = src;
  node1->next = g->List[dest];
  g->List[dest] = node1;
}

void buildAdjList(Graph *g,int** Arr, int edgesRowSize) {
  for(int i = 0; i < edgesRowSize; i ++) {
    int src = Arr[i][0];
    int dest = Arr[i][1];
    addEdge(g, src, dest);
  }
  return;
}

void printGraph(Graph *g) {
  for(int i = 0; i < g->v; i++) {
    printf("[%d] ",i);
    GNode *node = g->List[i];
    while(node != NULL) {
      printf("%d ->", node->data);
      node = node->next;
    }
    debug("NULL");
  }
}

void dfsUtil(Graph *g, int v, bool Arr[]) {
  Arr[v] = true;
  GNode *node = g->List[v];

  while(node != NULL) {
    if(!Arr[node->data]) {
      dfsUtil(g, node->data, Arr);
    }
    node = node->next;
  }
}

int dfs(Graph *g) {
  if(g == NULL)
    return true;
  bool Arr[g->v];
  memset(Arr, false, sizeof(Arr));
  int count = 0;

  for(int i = 0; i < g->v; i ++) {
    if(!Arr[i]) {
      dfsUtil(g, i , Arr);
      count ++;
    }
  }
  return count;
}

int countComponents(int n, int** edges, int edgesRowSize, int edgesColSize) {
  if(n == 0 || edges == NULL)
    return 0;
  Graph *g = initGraph(n);
  buildAdjList(g, edges, edgesRowSize);
  //printGraph(g);
  return dfs(g);

}

int** create_matrix(int rows, int cols) {
  int** mat = (int**) malloc(rows * sizeof(int*));
  int i;
  for (i = 0; i < rows; i++)
    mat[i] = (int*)malloc(cols * sizeof(int));
  return mat;
}

int main () {
  int n = 5;
  int **edges = create_matrix(ROWS, COLS);
  int edgesRowSize = ROWS;
  int edgesColSize = COLS;

  *(*(edges + 0) + 0) = 0;
  *(*(edges + 0) + 1) = 1;

  *(*(edges + 1) + 0) = 1;
  *(*(edges + 1) + 1) = 2;

  *(*(edges + 2) + 0) = 3;
  *(*(edges + 2) + 1) = 4;

  int ret  = countComponents(n, edges, edgesRowSize, edgesColSize);

  debug("Output = %d", ret);

  return 0;
}

/**
   => ./a.out
   [main] L=159 :Output = 2
**/
