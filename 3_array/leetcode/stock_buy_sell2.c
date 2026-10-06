/***
    https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-cooldown/
    Best Time to Buy and Sell Stock with Cooldown

    You are given an array prices where prices[i] is the
    price of a given stock on the ith day.

    Find the maximum profit you can achieve. You may complete as
    many transactions as you like (i.e., buy one and sell one
    share of the stock multiple times) with the following restrictions:

    After you sell your stock, you cannot buy stock on the
    next day (i.e., cooldown one day).
    Note: You may not engage in multiple transactions simultaneously
    (i.e., you must sell the stock before you buy again).

    Input: prices = [1,2,3,0,2]
    Output: 3
    Explanation: transactions = [buy, sell, cooldown, buy, sell]

    Input: prices = [1]
    Output: 0

    Constraints:
    1 <= prices.length <= 5000
    0 <= prices[i] <= 1000

    Date: Oct 14, 2021, Happy Dasera, India
    Fair Oaks, CA.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define debug(str,args...) printf("[%s] L=%d :"str"\n", __func__, __LINE__, ##args)
#define MAX(a,b) ((a)>(b)?(a):(b))

int maxProfit(int* prices, int pricesSize) {
  int sold = 0, presold, hold = -prices[0], cool = 0, i;

  for (i = 0; i < pricesSize; i++) {
    presold = sold;
    sold = hold + prices[i];
    hold = MAX(hold, cool - prices[i]);
    cool = MAX(cool, presold);
  }

  return MAX(cool, sold);
}

int maxProfit2(int* prices, int pricesSize) {
  int i, last, dlast, temp;
  for(dlast=0, last=0, i=1; i<pricesSize; i++) {
    temp  = last;
    last  = last+ prices[i]-prices[i-1] > dlast ? last+ prices[i] - prices[i-1] : dlast ;
    dlast = temp>dlast ? temp : dlast;
  }
  return dlast > last ? dlast : last;
}

int main () {
  int ret = 0;
  int prices[] = {1,2,3,0,2};
  int pricesSize = sizeof(prices) / sizeof(prices[0]);
  ret = maxProfit(prices, pricesSize);
  debug("O/p = %d \n", maxProfit(prices, pricesSize));
  return 0;
}

/*
  => ./a.out
  [main] L=64 :O/p = 3
*/
