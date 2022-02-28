/***
    https://leetcode.com/problems/clone-graph/
    Clone Graph

    Given a reference of a node in a connected undirected graph.
    Return a deep copy (clone) of the graph.
    Each node in the graph contains a value (int) and a list (List[Node]) of its neighbors.

    class Node {
      public int val;
      public List<Node> neighbors;
    }

    Test case format:
    For simplicity, each node's value is the same as the node's index (1-indexed).
    For example, the first node with val == 1, the second node with val == 2,
    and so on. The graph is represented in the test case using an adjacency list.

    An adjacency list is a collection of unordered lists used to represent
    a finite graph. Each list describes the set of neighbors of a node in
    the graph.

    The given node will always be the first node with val = 1. You must return
    the copy of the given node as a reference to the cloned graph.

    Input: adjList = [[2,4],[1,3],[2,4],[1,3]]
    Output: [[2,4],[1,3],[2,4],[1,3]]
    Explanation: There are 4 nodes in the graph.
    1st node (val = 1)'s neighbors are 2nd node (val = 2) and 4th node (val = 4).
    2nd node (val = 2)'s neighbors are 1st node (val = 1) and 3rd node (val = 3).
    3rd node (val = 3)'s neighbors are 2nd node (val = 2) and 4th node (val = 4).
    4th node (val = 4)'s neighbors are 1st node (val = 1) and 3rd node (val = 3).

    Input: adjList = [[]]
    Output: [[]]
    Explanation: Note that the input contains one empty list. The graph consists of
    only one node with val = 1 and it does not have any neighbors.

    Input: adjList = []
    Output: []
    Explanation: This an empty graph, it does not have any nodes.

    Constraints:
    The number of nodes in the graph is in the range [0, 100].
    1 <= Node.val <= 100
    Node.val is unique for each node.
    There are no repeated edges and no self-loops in the graph.
    The Graph is connected and all nodes can be visited starting from the given node.

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: 22/02/2022  : Palindrome Date

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
 * Definition for a Node.
 */
struct Node {
  int val;
  int numNeighbors;
  struct Node** neighbors;
};

struct Node *copy_node(struct Node *node,struct Node ***list, int* _len) {
    int len = *_len;
    int i;
    if (!node) return 0;
     while (node->val >= len) {
        struct Node** t = (*list);
        (*list)=malloc(len*sizeof(struct Node*)*2);
        for (i=0; i<len; i++)
            (*list)[i] = t[i];
        len *= 2;
        *_len = len;
        free(t);
        for (; i<len; i++)
            (*list)[i] = 0;
     }
    if ((*list)[node->val])
        return (*list)[node->val];

    struct Node *new_node=malloc(len*sizeof(struct Node*));
    (*list)[node->val] = new_node;
    new_node->val= node->val;
    new_node->numNeighbors= node->numNeighbors;
    new_node->neighbors = malloc(sizeof(struct Node*)*new_node->numNeighbors);
    for (i=0; i<new_node->numNeighbors; i++ )
        new_node->neighbors[i] = copy_node(node->neighbors[i],list, _len);

    return new_node;
}

struct Node *cloneGraph(struct Node *s) {
    int  len = 100;
    struct Node** list=malloc(len*sizeof(struct Node*));
    for (int i; i<len; i++)
        list[i] = 0;

    return(copy_node(s,&list,&len));
}

void test() {
  //  [[2,4],[1,3],[2,4],[1,3]]
  int ret = 0;

  debug("Output = %d", ret);
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**

 **/
