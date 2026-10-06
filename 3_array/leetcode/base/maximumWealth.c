/***
    https://leetcode.com/problems/richest-customer-wealth/
    Richest Customer Wealth

    You are given an m x n integer grid accounts where
    accounts[i][j] is the amount of money the ith customer has
    in the jth bank. Return the wealth that the richest customer has.

    A customer's wealth is the amount of money they have in all
    their bank accounts. The richest customer is the customer
    that has the maximum wealth.

    Input: accounts = [[1,2,3],[3,2,1]]
    Output: 6
    Explanation:
    1st customer has wealth = 1 + 2 + 3 = 6
    2nd customer has wealth = 3 + 2 + 1 = 6
    Both customers are considered the richest with a wealth of 6 each, so return 6.

    Input: accounts = [[1,5],[7,3],[3,5]]
    Output: 10
    Explanation:
    1st customer has wealth = 6
    2nd customer has wealth = 10
    3rd customer has wealth = 8
    The 2nd customer is the richest with a wealth of 10.

    Input: accounts = [[2,8,7],[7,1,3],[1,9,5]]
    Output: 17

    Constraints:
    m == accounts.length
    n == accounts[i].length
    1 <= m, n <= 50
    1 <= accounts[i][j] <= 100

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address maximumWealth.c -lm

    Date: Jan 30, 2022
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
int maximumWealth(int** accounts, int accountsSize, int* accountsColSize) {
  int sum = 0;
  int finalSum = 0;

  for (int i=0; i<accountsSize; ++i) {
    for (int j=0; j<*accountsColSize; ++j) {
      sum += accounts[i][j];
      debug ("i = %d sum = %d", accounts[i][j], sum);
    }
    finalSum = max(finalSum, sum);
    sum = 0;
  }
  return finalSum;
}

int** create_matrix(int row, int col) {
  int** ptr= (int **)malloc(row * sizeof(int *));
  for (int i=0; i<row; ++i)
    ptr[i] = (int *)malloc(col * sizeof(int));\

  return ptr;
}

void free_mat(int **mat, int row) {
  for (int i=0; i<row; ++i)
    free(mat[i]);
  free(mat);
  mat = NULL;
}

void test() {
  int ret = 0;
  int row = 2;
  int col = 3;
  int accountsSize = row;
  int accountsColSize = col;;
  int** accounts = create_matrix(row, col);

  *(*(accounts + 0) + 0) = 1;
  *(*(accounts + 0) + 1) = 2;
  *(*(accounts + 0) + 2) = 3;

  *(*(accounts + 1) + 0) = 3;
  *(*(accounts + 1) + 1) = 2;
  *(*(accounts + 1) + 2) = 1;

  ret = maximumWealth(accounts, accountsSize, &accountsColSize);
  debug("Output = %d", ret);
  free_mat(accounts, row);
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**
   => ./main
   [maximumWealth] L=75 :i = 1 sum = 1
   [maximumWealth] L=75 :i = 2 sum = 3
   [maximumWealth] L=75 :i = 3 sum = 6
   [maximumWealth] L=75 :i = 3 sum = 3
   [maximumWealth] L=75 :i = 2 sum = 5
   [maximumWealth] L=75 :i = 1 sum = 6
   [test] L=115 :Output = 6
**/
