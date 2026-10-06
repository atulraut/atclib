/***
    Hard: https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/
    Best Time to Buy and Sell Stock III

    You are given an array prices where prices[i] is the price
    of a given stock on the ith day.

    Find the maximum profit you can achieve. You may complete at
    most two transactions.

    Note: You may not engage in multiple transactions simultaneously
    (i.e., you must sell the stock before you buy again).

    Input: prices = [3,3,5,0,0,3,1,4]
    Output: 6
    Explanation: Buy on day 4 (price = 0) and sell on day 6
    (price = 3), profit = 3-0 = 3.
    Then buy on day 7 (price = 1) and sell on day 8 (price = 4),
    profit = 4-1 = 3.

    Input: prices = [1,2,3,4,5]
    Output: 4
    Explanation: Buy on day 1 (price = 1) and sell on day 5
    (price = 5), profit = 5-1 = 4.
    Note that you cannot buy on day 1, buy on day 2 and sell them
    later, as you are engaging multiple transactions at the same
    time. You must sell before buying again.

    Input: prices = [7,6,4,3,1]
    Output: 0
    Explanation: In this case, no transaction is done, i.e.
    max profit = 0.

    Input: prices = [1]
    Output: 0

    Constraints:
    1 <= prices.length <= 105
    0 <= prices[i] <= 105

    Date: 15 Oct 2021 Dasera USA
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

#define max(a, b) ((a) > (b)? (a): (b))
#define min(a, b) ((a) < (b)? (a): (b))

// void swap(int* a, int* b) {
//   int tmp = *a;
//   *a = *b;
//   *b = tmp;
// }
// #if 0
// int maxProfit(int* prices, int pricesSize){
//   int buy1 = 10000;
//   int sell_1 = 0;
//   int buy2 = 10000;
//   int sell_2 = 0;

//   for (int i = 0; i < pricesSize; i++) {
//     buy1    = min(buy1, prices[i]);
//     sell_1 = max(sell_1, prices[i] - buy1);
//     buy2    = min(buy2, prices[i] - sell_1);
//     sell_2 = max(sell_2, prices[i] - buy2);
//   }

//   return sell_2;
// }
// #endif

int maxProfit(int* prices, int pricesSize) {
  int buy1 = -prices[0];
  int sell_1 = 0;
  int buy2 = -10000;
  int sell_2 = 0;

  for (int i = 1; i < pricesSize; i++) {
    buy1   = max(buy1, -prices[i]);
    sell_1 = max(sell_1, prices[i] + buy1);
    buy2   = max(buy2, sell_1 - prices[i]);
    sell_2 = max(sell_2, prices[i] + buy2);
  }

  return sell_2;
}

int maxProfit_DP(int* prices, int pricesSize) {
  if(pricesSize == 1 || pricesSize == 0) {
    return 0;
  }

  int* global = (int*)malloc(sizeof(int) * 3);
  int* local = (int*)malloc(sizeof(int) * 3);

  for(int i = 0; i < 3; ++i) {
    global[i] = 0;
    local[i] = 0;
  }

  for(int i = 0; i < pricesSize - 1; ++i) {
    int diff = prices[i+1] - prices[i];

    for(int j = 2; j >= 1; --j) {
      local[j] = max(global[j-1] + max(diff, 0), local[j] + diff);
      global[j] = max(global[j], local[j]);
    }
  }

  return global[2];
}

int main (int argc, char **argv) {
  int ret = 0;
  int prices[] = {3,3,5,0,0,3,1,4};
  int pricesSize = sizeof(prices) / sizeof(prices[0]);

  ret = maxProfit(prices, pricesSize);
  debug("Output = %d", ret);
  return 0;
}

/**
   => ./a.out
   [main] L=93 :Output = 6
**/
