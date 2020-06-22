/***
 * LeetCode : Cheapest Flights Within K Stops
 * There are n cities connected by m flights. Each flight starts from city
 * u and arrives at v with a price w.
 * Now given all the cities and flights, together with starting city src and
 * the destination dst, your task is to find the cheapest price from src to
 * dst with up to k stops. If there is no such route, output -1.
 * Example 1:
 * Input:
 * n = 3, edges = [[0,1,100],[1,2,100],[0,2,500]]
 * src = 0, dst = 2, k = 1
 * Output: 200
 * Explanation:
 * The graph looks like this:
 * The cheapest price from city 0 to city 2 with at most 1 stop costs 200,
 *
 *               (0)
 *      RED100	|   |       500
 *	|                  |
 * |	         100              |
 * (1)<------------------------>(2)
 *       RED
 *  as marked red in the picture.
 * Example 2:
 * Input:
 * n = 3, edges = [[0,1,100],[1,2,100],[0,2,500]]
 * src = 0, dst = 2, k = 0
 * Output: 500
 * Explanation:
 * The graph looks like this:
 * The cheapest price from city 0 to city 2 with at most 0 stop costs 500, as
 *  marked blue in the picture.
 * Constraints:
 *   The number of nodes n will be in range [1, 100], with nodes labeled from
 *   0 to n - 1.
 *   The size of flights will be in range [0, n * (n - 1) / 2].
 *   The format of each flight will be (src, dst, price).
 *   The price of each flight will be in the range [1, 10000].
 *   k is in the range of [0, n - 1].
 *   There will not be any duplicated flights or self cycles.
 * Logic : https://www.youtube.com/watch?v=60RbWlDFsmI {Really NOT}
 * https://leetcode.com/problems/cheapest-flights-within-k-stops/
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN(a, b)   (a < b ? a : b)

int findCheapestPrice(int n, int flights[][3], int flightsSize, int* flightsColSize,
		        int src, int dst, int K) {
  int i, j, x, ret;
  int *dp = calloc(n,sizeof(int));
  int *pre = calloc(n, sizeof(int));

  printf ("[%s] Enter flightsSize=%d L=%d \n", __func__, flightsSize, __LINE__);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      printf ("[%s] ret=%d L=%d \n", __func__, flights[i][j], __LINE__);
    }
  }

  // Init (K=0)
  for (i = 0; i < flightsSize; i++) {
      if (src == flights[i][0]) {
        dp[flights[i][1] ] =  flights[i][2];
        pre[flights[i][1] ] =  flights[i][2];
        }
    }

  // Start from "K=1"
  for (x = 1; x < K+1; x++) {
      for (i = 0; i < flightsSize; i++) {
  int u = flights[i][0];
  int v = flights[i][1];
  int w = flights[i][2];

  if (pre[u] != 0) {
      if (dp[v] == 0) {
        dp[v] = pre[u] + w;
              } else {
         dp[v] = MIN(dp[v], pre[u] + w);
              }
          }
        }

      memcpy(pre, dp, sizeof(int)*n);
    }

  ret = dp[dst];
  free(dp);
  free(pre);
  printf ("[%s] ret=%d L=%d \n", __func__, ret, __LINE__);
  return (ret == 0 ? -1 : ret);
}

int main () {
  int n_city = 3;
  int flightsSize;
  int flightsColSize;
  int src = 0;
  int dst = 2;
  int maxStop = 1;
  int flights[3][3] = {
                   {0,1,100},
                   {1,2,100},
                   {0,2,500}
  };

  flightsSize = sizeof(flights)/sizeof(flights[0]);
  int returnSize;
  int ret;

  ret = findCheapestPrice(n_city, flights, flightsSize, &flightsColSize, src,  dst, maxStop);

  printf ("[%s] ret=%d flightSize=%d L=%d \n", __func__, ret, flightsSize, __LINE__);
}
