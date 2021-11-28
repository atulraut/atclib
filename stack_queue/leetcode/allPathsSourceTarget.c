/***
    https://leetcode.com/problems/all-paths-from-source-to-target/
    All Paths From Source to Target

    Given a directed acyclic graph (DAG) of n nodes labeled from
    0 to n - 1, find all possible paths from node 0 to node n - 1
    and return them in any order.

    The graph is given as follows: graph[i] is a list of all nodes
    you can visit from node i (i.e., there is a directed edge from node i to node graph[i][j]).

    Input: graph = [[1,2],[3],[3],[]]
    Output: [[0,1,3],[0,2,3]]
    Explanation: There are two paths: 0 -> 1 -> 3 and 0 -> 2 -> 3.

    Input: graph = [[4,3,1],[3,2,4],[3],[4],[]]
    Output: [[0,4],[0,3,4],[0,1,3,4],[0,1,2,3,4],[0,1,4]]

    Input: graph = [[1],[]]
    Output: [[0,1]]

    Input: graph = [[1,2,3],[2],[3],[]]
    Output: [[0,1,2,3],[0,2,3],[0,3]]

    Input: graph = [[1,3],[2],[3],[]]
    Output: [[0,1,2,3],[0,3]]

    Constraints:
    n == graph.length
    2 <= n <= 15
    0 <= graph[i][j] < n
    graph[i][j] != i (i.e., there will be no self-loops).
    All the elements of graph[i] are unique.
    The input graph is guaranteed to be a DAG.

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: 27 Nov 2021
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

/*----------------------------------- Micro --------------------------------------*/
#define debug(str,args...) printf("[%s] L=%d :"str"\n", __func__, __LINE__, ##args)
#define atsizeof(object) (char *)(&object+1) - (char*)(&object)
#define arrsz(x)  (sizeof(x) / sizeof((x)[0]))
#define max(a,b)		\
  ({ __typeof__ (a) _a = (a);	\
    __typeof__ (b) _b = (b);	\
    _a > _b ? _a : _b; })
#define min(a,b)		\
  ({ __typeof__ (a) _a = (a);	\
    __typeof__ (b) _b = (b);	\
    _a < _b ? _a : _b; })
/*----------------------------------- Micro --------------------------------------*/

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */

struct ListItem {
  int val;
  int links;
  struct ListItem* prev;
};

struct ListItem* ref(struct ListItem* item) {
  item->links ++;
  return item;
}

void unref(struct ListItem* item) {
  struct ListItem* prev = item->prev;
  item->links --;
  if (item->links == 0) {
    free(item);
    if (prev != NULL) {
      unref(prev);
    }
  }
}

struct StackItem {
  struct ListItem* val;
};

struct Stack {
  struct StackItem* data;
  int current;
  int max_size;
};

void stack_init(struct Stack* stack, int size) {
  stack->current = 0;
  stack->max_size = size;
  stack->data = malloc(size*sizeof(struct StackItem));
}

void stack_destroy(struct Stack* stack) {
  free(stack->data);
}

void stack_push(struct Stack* stack, struct ListItem* value) {
  if (stack->current == stack->max_size) {
    stack->max_size = stack->max_size*2;
    stack->data = realloc(stack->data, stack->max_size*sizeof(struct StackItem));
  }
  stack->data[stack->current].val = value;
  stack->current = stack->current + 1;
}

struct ListItem* stack_pop(struct Stack* stack) {
  stack->current = stack->current - 1;
  return stack->data[stack->current].val;
}

int stack_empty(struct Stack* stack) {
  return stack->current == 0;
}

int** allPathsSourceTarget(int** graph, int graphSize, int* graphColSize, int* returnSize, int** returnColumnSizes) {
  struct Stack st;
  struct ListItem* item = malloc(sizeof(*item));
  stack_init(&st, 100);
  item->prev = NULL; item->val = 0; item->links = 0;
  stack_push(&st, ref(item));
  int capacity = 100;
  int** res = malloc(capacity* sizeof(int*));
  int* cols = malloc(capacity* sizeof(int));
  int resSize = 0;
  int i, j, k, l;

  while (!stack_empty(&st)) {
    struct ListItem* item = stack_pop(&st);
    i = item->val;
    for (j = 0; j < graphColSize[i]; j=j+1) {
      int n = graph[i][j];
      if (n == graphSize-1) {
	struct ListItem* cur; struct ListItem* next;
	if (resSize >= capacity) {
	  capacity = capacity*2;
	  res = realloc(res, capacity*sizeof(int*));
	  cols = realloc(cols, capacity*sizeof(int));
	}
	cols[resSize] = 1;
	for (cur = item; cur != NULL; cur=cur->prev) {
	  cols[resSize]++;
	}
	res[resSize] = malloc(cols[resSize]*sizeof(int));
	k = cols[resSize]-1;
	res[resSize][k] = n; k--;
	cur = item;
	for (cur = item; cur != NULL; cur=cur->prev) {
	  res[resSize][k] = cur->val;
	  k--;
	}
	resSize++;
      } else if (n != graphSize-1) {
	struct ListItem* nitem = malloc(sizeof(*nitem));
	nitem->prev = ref(item);
	nitem->val = n;
	nitem->links = 0;
	stack_push(&st, ref(nitem));
      }
    }
    unref(item);
  }
  stack_destroy(&st);
  *returnColumnSizes = cols;
  *returnSize = resSize;
  return res;
}
int main (int argc, char **argv) {
  int ret = 0;

  debug("Output = %d", ret);
  return 0;
}

/**

 **/
