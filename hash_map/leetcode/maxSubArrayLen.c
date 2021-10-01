/***
    https://leetcode.com/problems/maximum-size-subarray-sum-equals-k/
    Maximum Size Subarray Sum Equals k
    Given an integer array nums and an integer k,
    return the maximum length of a subarray that
    sums to k. If there isn't one, return 0 instead.

    Input: nums = [1,-1,5,-2,3], k = 3
    Output: 4
    Explanation: The subarray [1, -1, 5, -2] sums to
    and is the longest.

    Input: nums = [-2,-1,2,1], k = 1
    Output: 2
    Explanation: The subarray [-1, 2] sums to 1 and
    is the longest.

    Constraints:

    1 <= nums.length <= 2 * 105
    -104 <= nums[i] <= 104
    -109 <= k <= 109

    Date: 29 Sept 2021
    Fair Oaks, CA.
*/

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

#define debug(str,args...) printf("[%s] L=%d :"str"\n", __func__, __LINE__, ##args)

#define SIZE 100001
struct HashArray {
    int key;
    int count;
    int location;
    struct HashArray* next;
} Hash[SIZE];

void addHash(int num, int location) {

    int index = abs(num%SIZE);
    if (Hash[index].key == 0){
        Hash[index].key = num;
        Hash[index].location = location;
        Hash[index].count++;
    }
    else if (Hash[index].key == num ) {
        Hash[index].count++;
    } else {
        struct HashArray *p = &Hash[index];
        while (p->next != NULL && p->key != num)
            p = p->next;
        if (p->key == num)
            p->count++;
        else {
            p->next = malloc(sizeof(struct HashArray));
            p = p->next;
            p->count = 1;
            p->key = num;
            p->location = location;
            p->next = NULL;
        }
    }
}

int getHash(int num) {
    int index = abs(num%SIZE);
    if (Hash[index].count == 0) {
        return 0;
    } else if (Hash[index].key == num) {
        return Hash[index].location;
    }
    else {
        struct HashArray *p = &Hash[index];
        while (p->next != NULL && p->key != num)
            p = p->next;
        if (p->key == num)
            return p->location;
        else
            return 0;
    }
    return 0;
}

int maxSubArrayLen(int* nums, int numsSize, int k) {

    int globalMax = 0;
    int prefixSum = 0;
    memset (Hash, 0, sizeof(Hash));
    int location;
    for (int i = 0; i < numsSize; i ++) {
        prefixSum += nums[i];
        if (prefixSum == k)
            globalMax = i+1;
        location = getHash(prefixSum-k);
        if (location)
            globalMax = globalMax > (i+1-location) ? globalMax : (i+1-location);
        addHash(prefixSum, i+1);
    }
    return globalMax;
}

int main (int argc, char **argv) {
  int ret = 0;
  int nums[] = {1,-1,5,-2,3};
  int numsSize = 5;
  int k = 3;

  ret =  maxSubArrayLen(nums, numsSize, k);
  debug("Output = %d", ret);
  return 0;
}

/**

 **/
