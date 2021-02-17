/***
 * LeetCode : Largest Divisible Subset
 * Given a set of distinct positive integers, find the largest subset such
 * that every pair (Si, Sj) of elements in this subset satisfies:
 * Si % Sj = 0 or Sj % Si = 0.
 * If there are multiple solutions, return any subset is fine.
 * Example 1:
 * Input: [1,2,3]
 * Output: [1,2] (of course, [1,3] will also be ok)
 * Example 2:
 * Input: [1,2,4,8]
 * Output: [1,2,4,8]
 *
 * Logic : https://www.youtube.com/watch?v=Wv6DlL0Sawg
 * a] Sorting b] Apply DP c] Subset
 * Date: 6/18/2020 Thursday 02:00PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cmp(void* a,void* b) {
    return *(int*)a - *(int*)b;
}

void func(int* nums, int numsSize, int* map, int* lens, int pre_index) {
  int i;

    if(numsSize == 1 || map[0] != 0) {
        return;
    }

    for(i=1; i<numsSize; i++) {
        if(nums[i]%nums[0] == 0) {
            if(map[i] == 0) {
                func(&nums[i], numsSize-i,&map[i],&lens[i],pre_index+i);
            }
            if(lens[0] < lens[i]+1) {
                map[0] = i+pre_index;
                lens[0] = lens[i]+1;
            }
        }
    }
}

int* largestDivisibleSubset(int* nums, int numsSize, int* returnSize) {
  int i;
     *returnSize = 0;
    if(numsSize == 0) {
        return NULL;
    }

    qsort(nums, numsSize, sizeof(nums[0]), cmp);

    for (i=0; i<numsSize; i++)
      printf ("[%s]-qsort:- num=%d L=%d \n", __func__, nums[i], __LINE__);

    int* map  = (int*)calloc(numsSize, sizeof(int));
    int* lens = (int*)calloc(numsSize, sizeof(int));
    int* ret  = (int*)calloc(numsSize, sizeof(int));

    for(i=0; i<numsSize-1; i++) {
        if(map[i] != 0) {
            continue;
        }
        func(&nums[i], numsSize-i, &map[i], &lens[i], i);
    }

    int index=0;
    for(i=1; i<numsSize; i++) {
        if(lens[i] > lens[index]) {
            index = i;
        }
    }
    while(map[index]!=0) {
        ret[(*returnSize)++] = nums[index];
        index = map[index];
    }
    ret[(*returnSize)++] = nums[index];
    return ret;
}

int main () {
  int i;
  //  int nums[] = {1, 2, 3};
  int nums[] = {1, 2, 8, 4};
  int numsSize = sizeof(nums)/sizeof(nums[0]);
  int returnSize;
  int *ret;

  ret = largestDivisibleSubset (nums, numsSize, &returnSize);
  for (i=0; i<returnSize; i++)
    printf ("[%s] ret=%d L=%d \n", __func__, ret[i], __LINE__);
}
