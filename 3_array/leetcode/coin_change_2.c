/***
 * LeetCode: Coin Change 2 :
 * You are given coins of different denominations and a total amount of money.
 * Write a function to compute the number of combinations that make up that amount.
 * You may assume that you have infinite number of each kind of coin.
 * Example 1:
 * Input: amount = 5, coins = [1, 2, 5]
 * Output: 4
 * Explanation: there are four ways to make up the amount:
 * 5=5
 * 5=2+2+1
 * 5=2+1+1+1
 * 5=1+1+1+1+1
 * Example 2:
 * Input: amount = 3, coins = [2]
 * Output: 0
 * Explanation: the amount of 3 cannot be made up just with coins of 2.
 * Example 3:
 * Input: amount = 10, coins = [10]
 * Output: 1
 * Note: You can assume that
 *  0 <= amount <= 5000
 *  1 <= coin <= 5000
 *  the number of coins is less than 500
 *  the answer is guaranteed to fit into signed 32-bit integer
 * Date: 06/10/2020 - 10:42PM PDT
 * Tag: DP Program - 1] Repeating Subproblem 2] Optimal Solution.
 * https://leetcode.com/explore/featured/card/june-leetcoding-challenge/539/week-1-june-1st-june-7th/3353/
 * Logic : https://www.youtube.com/watch?v=ruMqWViJ2_U
 */
#include<stdio.h>
#include <stdlib.h>
#include <string.h>

int **getDynamicArray(int row, int col) {
  int i, j;
  int **ar;

  ar = (int **)malloc(row * sizeof(int *));
  for (i=0; i<row; i++)
    ar[i] = (int *)malloc(col * sizeof(int));
  printf ("In getDynamicArray Input \n");
  return ar;
}

/* Two Row Solution*/
int change2(int amount, int **coins, int coinsSize) {
  int i, j;
  /*
  for(i=0; i<coinsSize; i++)
    coins[0][i] = 0;

  for(i=0; i<coinsSize; i++)
    coins[i][0] += 1;


  for(i=0; i<coinsSize; i++) {
    for(j=coins[i]; j<amount+1; j++) {
      if(j>= coins[i-1])
	coins[i][j] = coins[i][j - coins[i-1] ] + coins[i-1][j];
      else
	coins[i][j] = coins[i-1][j];
    }
  }

  return coins[n][amount];
  */
}


/* One Row Solution*/
int change(int amount, int* coins, int coinsSize) {
  int i, j;
  int *dp;

  if(coinsSize==0){
    if(amount==0){
      return 1;
    }
    return 0;
  }

  dp=(int*)calloc(amount+1,sizeof(int));
  dp[0]=1;

  for(i=0;i<coinsSize;i++){
    for(j=coins[i]; j<amount+1; j++){
      dp[j] += dp[j-coins[i]];
    }
  }
  return dp[amount];
}

int main () {
  int amount = 5;
  int coins[] = {1, 2, 5};
  int cSize = sizeof(coins)/sizeof(coins[0]);
  /*  One Row Solution */
  int op = change(amount, coins, cSize);
  printf ("--> OP = %d \n", op);

  /* Two Row Solution */
  int **dp =  getDynamicArray(4,6);
  for (int i=0; i<4; i++) {
    for (int j=0; j<6; j++) {
      dp[i][j] = rand() % 6;
      printf ("Input[%d][%d] = |%d| | \t",i,j, dp[i][j]);
    }
    printf ("\n");
  }

  op = change2(amount, dp, cSize);
  printf ("--> OP = %d \n", op);

  return 0;
}
