/***
    Subset Sum Problem :
    https://leetcode.com/problems/combination-sum-iii/
    216. Combination Sum III - Medium

    Find all valid combinations of k numbers that sum up
    to n such that the following conditions are true:

    Only numbers 1 through 9 are used.
    Each number is used at most once.
    Return a list of all possible valid combinations. The list
    must not contain the same combination twice, and the
    combinations may be returned in any order.

    Input: k = 3, n = 7
    Output: [[1,2,4]]
    Explanation:
    1 + 2 + 4 = 7
    There are no other valid combinations.

    Input: k = 3, n = 9
    Output: [[1,2,6],[1,3,5],[2,3,4]]
    Explanation:
    1 + 2 + 6 = 9
    1 + 3 + 5 = 9
    2 + 3 + 4 = 9
    There are no other valid combinations.

    Input: k = 4, n = 1
    Output: []
    Explanation: There are no valid combinations.
    Using 4 different numbers in the range [1,9], the smallest
    sum we can get is 1+2+3+4 = 10 and since 10 > 1, there
    are no valid combination.

    Constraints:
    2 <= k <= 9
    1 <= n <= 60
    Accepted
    364,902

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Tue Oct 11 07:11:34 PM PDT 2022
    Folsom, CA.
    #Google
    #Amazon
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
#define max(a,b)				\
  ({ __typeof__ (a) _a = (a);			\
    __typeof__ (b) _b = (b);			\
    _a > _b ? _a : _b; })
#define min(a,b)				\
  ({ __typeof__ (a) _a = (a);			\
    __typeof__ (b) _b = (b);			\
    _a < _b ? _a : _b; })
/*----------------------------------- Micro --------------------------------------*/


void help(int **result, int *res_count, int *buf, int *i_buf, int *nums, int index, int k, int n) {
  if(*i_buf == k && n == 0) {
    for(int i=0; i<*i_buf; i++) {
      debug("[%d]->[%d],",i, buf[i]);
    }
    printf("\n");

    result[*res_count] = malloc(k*sizeof(int));
    memcpy(result[*res_count], buf, k*sizeof(int));
    (*res_count)++;
    return;
  }

  for(int i=index; i<9; i++) {
    buf[(*i_buf)++] = nums[i]; // include - Add
    help(result, res_count, buf, i_buf, nums, i+1, k, n-nums[i]);
    (*i_buf)--;  // exclude - Remove
  }

}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int **combinationSum3(int k, int n, int *returnSize, int **returnColumnSizes) {
  *returnSize = 0;

  int *nums = malloc(9*sizeof(int));
  for(int i=1; i<=9; i++) // reverse also works 9-1
    nums[i-1] = i;

  int **result = (int **)malloc(sizeof(int *) * 16);
  int *buf = (int *)malloc(10 * sizeof(int));
  int i_buf = 0;

  help(result, returnSize, buf, &i_buf, nums, 0, k, n);

  *returnColumnSizes = malloc((*returnSize)*sizeof(int));

  for(int i=0; i<*returnSize; i++)
    (*returnColumnSizes)[i] = k;

  return result;
}

void test() {
  int k = 3;
  int n = 7; // Target AR
  int returnSize;
  int *returnColumnSizes;
  int** ret = combinationSum3(k, n, &returnSize, &returnColumnSizes);
  for (int i=0; i<returnSize; ++i) {
    for(int j=0; j<*returnColumnSizes; ++j) {
      debug("Output = %d", ret[i][j]);
    }
    printf ("\n");
  }
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**
   => ./a.out
   [help] L=80 :[0]->[1],
   [help] L=80 :[1]->[2],
   [help] L=80 :[2]->[4],

   [test] L=132 :Output = 1
   [test] L=132 :Output = 2
   [test] L=132 :Output = 4
**/
