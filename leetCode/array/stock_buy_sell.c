/*
  Best Time to Buy and Sell Stock II
  Say you have an array prices for which the ith element is the
  price of a given stock on day i.
  Design an algorithm to find the maximum profit. You may complete
  as many transactions as you like (i.e., buy one and sell one
  share of the stock multiple times).
  Note: You may not engage in multiple transactions at the same
  time (i.e., you must sell the stock before you buy again).
  Example 1:
  Input: [7,1,5,3,6,4]
  Output: 7
  Explanation: Buy on day 2 (price = 1) and sell on day 3 (price = 5), profit = 5-1 = 4.
  Then buy on day 4 (price = 3) and sell on day 5 (price = 6), profit = 6-3 = 3.
  Example 2:
  Input: [1,2,3,4,5]
  Output: 4
  Explanation: Buy on day 1 (price = 1) and sell on day 5 (price = 5), profit = 5-1 = 4.
  Note that you cannot buy on day 1, buy on day 2 and sell them later, as you are
  engaging multiple transactions at the same time. You must sell before buying again.
  Example 3:
  Input: [7,6,4,3,1]
  Output: 0
  Explanation: In this case, no transaction is done, i.e. max profit = 0.
  Solution : https://www.youtube.com/watch?v=K8iHi8AW1ls
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int maxProfit(int* prices, int pricesSize) {
  int diff = 0;
  for(int i=1; i<pricesSize; i++) {
    if (prices[i] > prices[i-1]) {
      diff += prices[i] - prices[i-1];
      printf ("[%s] o/p = %d \n",__func__, diff);
    }
  }
  printf ("[%s] o/p = %d \n",__func__, diff);
  return diff;
}

int main () {
  int input[] = {7,1,5,3,6,4};
  int sz = sizeof(input) / sizeof(input[0]);
  printf ("[%s] o/p = %d \n",__func__, maxProfit(input, sz));
  return 0;
}
