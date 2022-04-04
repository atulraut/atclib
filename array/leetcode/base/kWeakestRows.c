/***
    https://leetcode.com/problems/the-k-weakest-rows-in-a-matrix/

    The K Weakest Rows in a Matrix

    You are given an m x n binary matrix mat of 1's (representing soldiers)
    and 0's (representing civilians). The soldiers are positioned in front
    of the civilians. That is, all the 1's will appear to the left of
    all the 0's in each row.

    A row i is weaker than a row j if one of the following is true:

    The number of soldiers in row i is less than the number of soldiers in row j.
    Both rows have the same number of soldiers and i < j.
    Return the indices of the k weakest rows in the matrix ordered
    from weakest to strongest.

    Input: mat =
    [[1,1,0,0,0],
    [1,1,1,1,0],
    [1,0,0,0,0],
    [1,1,0,0,0],
    [1,1,1,1,1]],
    k = 3
    Output: [2,0,3]
    Explanation:
    The number of soldiers in each row is:
    - Row 0: 2
    - Row 1: 4
    - Row 2: 1
    - Row 3: 2
    - Row 4: 5
    The rows ordered from weakest to strongest are [2,0,3,1,4].

    Input: mat =
    [[1,0,0,0],
    [1,1,1,1],
    [1,0,0,0],
    [1,0,0,0]],
    k = 2
    Output: [0,2]
    Explanation:
    The number of soldiers in each row is:
    - Row 0: 1
    - Row 1: 4
    - Row 2: 1
    - Row 3: 1
    The rows ordered from weakest to strongest are [0,2,3,1].

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Mon Apr  4 08:58:22 PDT 2022
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
struct pair {
    int idx;
    int nums;
};

int cmp(const void* a, const void* b) {
  struct pair pa = *(const struct pair*) a;
  struct pair pb = *(const struct pair*) b;
  if(pa.nums == pb.nums) return pa.idx - pb.idx;
  return pa.nums - pb.nums;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* kWeakestRows(int** mat, int matSize, int* matColSize, int k, int* returnSize) {
  *returnSize = k;
  struct pair* arr = (struct pair*) malloc(matSize * sizeof(struct pair));
  for(int i = 0; i < matSize; i++) {
    int tmp = 0;
    for(int j = 0; j < matColSize[0]; j++) {
      tmp = (mat[i][j] == 1) ? tmp+1 : tmp;
    }
    arr[i].idx = i;
    arr[i].nums = tmp;
  }
  qsort(arr, matSize, sizeof(struct pair), cmp);
  int* ans = (int*) malloc(k * sizeof(int));
  for(int i = 0; i < k; i++) {
    ans[i] = arr[i].idx;
  }
  free(arr);
  return ans;
}

int** create_matrix(int rows, int cols) {
  int** max = (int**)calloc(sizeof(int *), rows);
  for (int i=0; i<rows; ++i) {
    max[i] = (int*)calloc(sizeof(int),  cols);
  }
  return max;
}

void test() {
  int *ret;
  int matSize = 4;
  int matColSize = 4;
  int k = 2;
  int returnSize;
  int** grid = create_matrix(matSize, matColSize);

  *(*(grid + 0) + 0) = 1;
  *(*(grid + 0) + 1) = 0;
  *(*(grid + 0) + 2) = 0;
  *(*(grid + 0) + 3) = 0;

  *(*(grid + 1) + 0) = 1;
  *(*(grid + 1) + 1) = 1;
  *(*(grid + 1) + 2) = 1;
  *(*(grid + 1) + 3) = 1;

  *(*(grid + 2) + 0) = 1;
  *(*(grid + 2) + 1) = 0;
  *(*(grid + 2) + 2) = 0;
  *(*(grid + 2) + 3) = 0;


  *(*(grid + 3) + 0) = 1;
  *(*(grid + 3) + 1) = 0;
  *(*(grid + 3) + 2) = 0;
  *(*(grid + 3) + 3) = 0;

  ret = kWeakestRows(grid, matSize, &matColSize, k, &returnSize);

  for (int i=0; i<returnSize; ++i)
    debug("Output = %d", ret[i]);
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**
=> ./a.out
[test] L=156 :Output = 0
[test] L=156 :Output = 2
 **/
