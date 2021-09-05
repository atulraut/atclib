/***
    Hard: Sum of Distances in Tree
    There is an undirected connected tree with n nodes labeled from
    0 to n - 1 and n - 1 edges.

    You are given the integer n and the array edges where
    edges[i] = [ai, bi] indicates that there is an edge between
    nodes ai and bi in the tree.

    Return an array answer of length n where answer[i] is the
    sum of the distances between the ith node in the tree
    and all other nodes.

    Input: n = 6, edges = [[0,1],[0,2],[2,3],[2,4],[2,5]]
    Output: [8,12,6,10,10,10]
    Explanation: The tree is shown above.
    We can see that dist(0,1) + dist(0,2) + dist(0,3) + dist(0,4) + dist(0,5)
    equals 1 + 1 + 2 + 2 + 2 = 8.
    Hence, answer[0] = 8, and so on.

    Input: n = 1, edges = []
    Output: [0]

    Input: n = 2, edges = [[1,0]]
    Output: [1,1]

    Constraints:
    1 <= n <= 3 * 104
    edges.length == n - 1
    edges[i].length == 2
    0 <= ai, bi < n
    ai != bi
    The given input represents a valid tree.
    https://leetcode.com/problems/sum-of-distances-in-tree/
    Date: 4 Sept 2021
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

void _help(int* res, int* count, int* parent, int i, int n) {
  if (res[parent[i]] == -1)
    _help(res, count, parent, parent[i], n);
  res[i] = res[parent[i]] + n - 2 * count[i];
}

void _change_root(int* parent, int root) {
  if (parent[root] == -1)
    return;
  _change_root(parent, parent[root]);
  parent[parent[root]] = root;
  parent[root] = -1;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* sumOfDistancesInTree(int n, int** edges, int edgesSize, int* edgesColSize, int* returnSize){
  int* res = malloc(sizeof(int) * (*returnSize = n));
  int parent[n], count[n];
  memset(parent, 255, sizeof(parent));
  memset(res, 255, sizeof(count));
  memset(count, 0, sizeof(count));
  for (int i=0;i<edgesSize;i++) {
    if (parent[edges[i][1]] == -1)
      parent[edges[i][1]] = edges[i][0];
    else if (parent[edges[i][0]] == -1)
      parent[edges[i][0]] = edges[i][1];
    else {
      _change_root(parent, edges[i][0]);
      parent[edges[i][0]] = edges[i][1];
    }
  }
  int sum=0,root;
  for (int i=0;i<n;i++) {
    if (parent[i] == -1) {
      root = i;
    } else {
      int j = i;
      while (parent[j] != -1) {
	count[j]++;
	sum++;
	j = parent[j];
      }
    }
  }
  count[root] = n;
  res[root] = sum;
  for (int i=0;i<n;i++) {
    if (res[i] != -1)
      continue;
    _help(res, count, parent, i, n);
  }
  return res;
}

int main (int argc, char **argv) {
  int ret = 0;

  debug("Output = %d", ret);
  return 0;
}

/**

 **/
