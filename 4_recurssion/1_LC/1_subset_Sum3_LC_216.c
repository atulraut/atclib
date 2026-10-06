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

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Sun 11 Aug 2024 11:20:56 AM PDT
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

#define debug(str,args...) printf("L=[%d] [%s] :| "str"\n", __LINE__, __func__, ##args)
/*
  1] idx - starting Index - from where to start looking
  2] input/S - Set of n items (Here we know 1-9)
  Sub Problme Defination - SD = 1+2
  3] Slate - Partial Solution
*/
/* PS         PS */
void helper(int k, int n, int* rowSz, int* input, int** output, int idx, int* slate_length, int* slate) {
  // Backtracking Case :
  debug ("AR k=%d n=%d *rowSz=%d idx=%d slate_length=%d", k, n, *rowSz, idx, *slate_length);
  // Base case - SD is 0, then just return
  if (*slate_length == k && n == 0) {
    //   debug ("AR 1 = %d", idx);
    for(int i=0; i<*slate_length; i++) {
      debug("[%d]->[%d],",i, slate[i]);
    }
    printf("\n");

    output[*rowSz] = (int *)malloc(sizeof(int) * k+1);
    memcpy(output[*rowSz], slate, k * sizeof(int));
    (*rowSz)++;
    return;
  }

  // Recursive Case
  // Decrease slightly SD + Increase slightly PS
  for (int i=idx; i<9; ++i) {
    // include
    slate[(*slate_length)++] = input[i];
    helper(k, (n-input[i]), rowSz, input, output, i+1, slate_length, slate);
    (*slate_length)--;
  }
}

int** combinationSum3(int k, int n, int* rowSz, int** colSz) {
  *rowSz = 0;
  debug ("k=%d n=%d", k, n);
  int* input = (int*)malloc(9 * sizeof(int));
  for (int i=1; i<=9; ++i)
    input[i-1] = i;

  int** output = (int **)malloc(sizeof(int *) * 16);
  int* slate = (int *)malloc(sizeof(int) * 10);
  int slate_length = 0;

  helper(k, n, rowSz, input, output, 0, &slate_length, slate);

  *colSz = (int *)malloc((*rowSz)*sizeof(int));

  for(int i=0; i<*rowSz; i++)
    (*colSz)[i] = k;

  // Free Resources
  free(input);
  free(slate);
  return output;
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
  // Free Resources
  free(returnColumnSizes);
  for(int i=0; i<returnSize; ++i) {
    int *temp = ret[i];
    free(temp);
    temp = NULL;
  }
  free(ret);
}

int main (int argc, char **argv) {
  test();
  return 0;
}
/**

 **/
