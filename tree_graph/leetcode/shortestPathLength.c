/***
    https://leetcode.com/problems/shortest-path-visiting-all-nodes/
    Shortest Path Visiting All Nodes

    You have an undirected, connected graph of n nodes labeled
    from 0 to n - 1. You are given an array graph where graph[i]
    is a list of all the nodes connected with node i by an edge.

    Return the length of the shortest path that visits every node.
    You may start and stop at any node, you may revisit nodes
    multiple times, and you may reuse edges.

    Input: graph = [[1,2,3],[0],[0],[0]]
    Output: 4
    Explanation: One possible path is [1,0,2,0,3]
    Example 2:

    Input: graph = [[1],[0,2,4],[1,3,4],[2],[1,2]]
    Output: 4
    Explanation: One possible path is [0,1,4,2,3]

    Constraints:
    n == graph.length
    1 <= n <= 12
    0 <= graph[i].length < n
    graph[i] does not contain i.
    If graph[a] contains b, then graph[b] contains a.
    The input graph is always connected.

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Mon Feb 28 10:12:48 PST 2022
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

class Solution {
 public:
  int shortestPathLength(vector<vector<int>>& graph) {
    bitset<1<<17> memo;
    memo.reset();
    const int endState = (1<<graph.size())-1;
    queue<int> q, other;
    for(int i = 0; i < graph.size(); ++i) q.emplace(encodeState(i, 0 | (1<<i)));
    int w = 0;
    while(true) {
      int state = q.front(); q.pop();
      if(!memo[state]) {
	memo[state] = true;
	auto [v, visited]{decodeState(state)};
	if(visited == endState) return w;
	for(const auto &e: graph[v]) {
	  int state = encodeState(e, visited | (1<<e));
	  other.emplace(state);
	}
      }
      if(q.empty()) ++w, swap(q, other), memo.reset();
      if(q.empty()) return -1;
    }
    return -1;
  }
  inline constexpr int encodeState(int cur, int visited) {
    return cur<<13 | visited;
  }
  inline constexpr pair<int, int> decodeState(int state) {
    return {state>>13, state &= ((1<<13)-1)};
  }
};

void test() {
  int ret = 0;

  debug("Output = %d", ret);
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**

 **/
