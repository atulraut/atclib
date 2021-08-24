/***
    Medium :  Graph Valid Tree
    You have a graph of n nodes labeled from 0 to n - 1.
    You are given an integer n and a list of edges where
    edges[i] = [ai, bi] indicates that there is an undirected
    edge between nodes ai and bi in the graph.

    Return true if the edges of the given graph make up
    a valid tree, and false otherwise.

    Input: n = 5, edges = [[0,1],[0,2],[0,3],[1,4]]
    Output: true

    Input: n = 5, edges = [[0,1],[1,2],[2,3],[1,3],[1,4]]
    Output: false

    Constraints:
    1 <= 2000 <= n
    0 <= edges.length <= 5000
    edges[i].length == 2
    0 <= ai, bi < n
    ai != bi
    There are no self-loops or repeated edges.

    https://leetcode.com/problems/graph-valid-tree

    Date: 24 August 2021
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

int find(int *set ,int target) {
  int p = target;

  while(p!=set[p]) p = set[p]
		     ;

  return p;
}

void unite(int *set , int p,int q){
  int pp = find(set,p);
  int qq = find(set,q);

  if(pp == qq)
    return;

  set[pp] = qq;
}

int connected(int *set ,int p,int q){
  return (find(set,p) == find(set,q));
}

//int validTree(int n, int** edges, int edgesRowSize, int edgesColSize)
int validTree(int n, int (*edges)[2], int edgesRowSize, int edgesColSize) {
  int set[n];

  for(int i = 0 ; i < n ; i++){
    set[i] = i;
  }

  for(int i = 0 ; i < edgesRowSize ;i++){
    int x = edges[i][0];
    int y = edges[i][1];
    if(connected(set,x,y))
      return 0;
    else
      unite(set,x,y);
  }
  int root = find(set,0);
  for(int i = 0 ; i < n ; i++){
    if(find(set,i) != root)
      return 0;
  }

  return 1;
}

/* Return 2D Array
   int (*generate())[2] {
   static int arr[][2] = { 11, 22, 33, 44 };
   return arr;
   }
*/

/* Return 2D Array */
int (*get_2D_matrix())[2] {
  int edgesRowSize= 4;
  int edgesColSize = 2;
  static int edges[4][2] = {
    {0,1},
    {0,2},
    {0,3},
    {1,4},
  };
  return edges;
}

int main (int argc, char **argv) {
  int ret = 0;
  int n = 5;
  int edgesRowSize= 4;
  int edgesColSize = 2;

  int (*edges)[2] = get_2D_matrix();
  ret = validTree(n, edges, edgesRowSize, edgesColSize);

  debug("Output = %d", ret);
  return 0;
}

/**
   => ./a.out
   [main] L=122 :Output = 1
**/
