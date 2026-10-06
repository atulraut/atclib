/***

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: 28 Oct 2021
    Fair Oaks, CA.
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

int cmp(const void *a, const void *b)
{
  return *(int *)a - *(int *)b;
}

int *subArr(int p1, int p2, int p3)
{
  const int size = 3;
  int *res = (int *)malloc(sizeof(int) * size);
  if (res == NULL) {
    return NULL;
  }
  res[0] = p1;
  res[1] = p2;
  res[2] = p3;
  return res;
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** threeSum(int* nums, int numsSize, int* returnSize, int** returnColumnSizes){
  qsort(nums, numsSize, sizeof(int), cmp);
  *returnSize = 0;
  int size = 64;
  int **res = (int **)malloc(sizeof(int *) * size);
  *returnColumnSizes = (int *)malloc(sizeof(int) * size);
  for (int i = 0; i < numsSize; i++) {
    if (i != 0 && nums[i] == nums[i - 1]) {
      continue;
    }

    // --------------- two sum -----------------
    int p1 = i + 1, p2 = numsSize - 1;
    int target = -nums[i];

    while (p1 < p2) {
      int sum = nums[p1] + nums[p2];
      if (sum < target) {
	p1++;
      } else if (sum > target) {
	p2--;
      } else {
	(*returnColumnSizes)[*returnSize] = 3;
	res[(*returnSize)++] = subArr(nums[i], nums[p1], nums[p2]);
	// (*returnSize)++;
	p1++;
	p2--;
	while (p1 < p2 && nums[p1] == nums[p1 - 1]) {
	  p1++;
	}
	if ((*returnSize) == size) {
	  size *= 2;
	  *returnColumnSizes = (int *)realloc(*returnColumnSizes, sizeof(int) * size);
	  res = (int **)realloc(res, sizeof(int *) * size);
	}
      }
    }
  }

  return res;
}

int main (int argc, char **argv) {
  int** ret;
  int nums[] = {-1,0,1,2,-1,-4};
  int numsSize = sizeof(nums)/sizeof(nums[0]);
  int returnSize;
  int* returnColumnSizes;

  ret = threeSum(nums, numsSize, &returnSize, &returnColumnSizes);

  return 0;
}

/**

 **/
