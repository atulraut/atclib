/***

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: 2, Jan 2022
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

int subsetXORSum(int* nums, int numsSize) {
  int ors= 0;

  for(int i=0; i<numsSize; ++i)
    ors |= nums[i];

  return pow(2,numsSize-1)*(ors);
}

void xor_subset_sum(int *nums, int *sum_xor, int *arr, int arr_index, int k, int numsSize) {
  if(k >= numsSize) {
    int temp_xor = 0;
    for(int i=0;i<arr_index;i++) {
      // printf("%d, %d\n", arr[i], nums[arr[i]]);
      if(0 == i) {
	temp_xor = nums[arr[i]];
	continue;
      }
      temp_xor ^= nums[arr[i]];
    }
    *sum_xor += temp_xor;
    // printf("============\n");
  } else {
    arr[arr_index++] = k;
    xor_subset_sum(nums, sum_xor, arr, arr_index, k+1, numsSize);

    arr[arr_index--] = 0;
    xor_subset_sum(nums, sum_xor, arr, arr_index, k+1, numsSize);
  }
}

int subsetXORSum1(int *nums, int numsSize) {
  assert(numsSize<=12);
  int arr[13];
  memset(arr, 0, numsSize*sizeof(int));
  int arr_index = 0;
  int sum_xor = 0;
  xor_subset_sum(nums, &sum_xor, arr, arr_index, 0, numsSize);
  return sum_xor;
}

int main (int argc, char **argv) {
  int ret = 0;
  int nums[] = {5,1,6};
  int numsSize = arrsz(nums);

  ret = subsetXORSum(nums, numsSize);
  debug("Output = %d", ret);
  return 0;
}

/**
   => ./a.out
   [main] L=82 :Output = 28
**/
