/***
    https://leetcode.com/problems/4sum-ii/
    4Sum II

    Given four integer arrays nums1, nums2, nums3, and
    nums4 all of length n, return the number of
    tuples (i, j, k, l) such that:

    0 <= i, j, k, l < n
    nums1[i] + nums2[j] + nums3[k] + nums4[l] == 0

    Example 1:

    Input: nums1 = [1,2], nums2 = [-2,-1], nums3 = [-1,2], nums4 = [0,2]
    Output: 2
    Explanation:
    The two tuples are:
    1. (0, 0, 0, 1) -> nums1[0] + nums2[0] + nums3[0] + nums4[1] = 1 + (-2) + (-1) + 2 = 0
    2. (1, 1, 0, 0) -> nums1[1] + nums2[1] + nums3[0] + nums4[0] = 2 + (-1) + (-1) + 0 = 0
    Example 2:

    Input: nums1 = [0], nums2 = [0], nums3 = [0], nums4 = [0]
    Output: 1

    Constraints:

    n == nums1.length
    n == nums2.length
    n == nums3.length
    n == nums4.length
    1 <= n <= 200
    -228 <= nums1[i], nums2[i], nums3[i], nums4[i] <= 228

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: 02022022
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

#define MAX_HASH_SIZE 10000

struct Hash {
    int key;
    int value;
};

struct Hash hash_table[MAX_HASH_SIZE];

int hash(int key) {
  return abs(key % MAX_HASH_SIZE);
}

int Search(int key) {
  int hash_index = hash(key);
  while(hash_table[hash_index].value != 0) {
    if(hash_table[hash_index].key == key)
      return hash_table[hash_index].value;
    hash_index = (hash_index+1) % MAX_HASH_SIZE;
  }
  return 0;
}

// Collision: linear probing(insert to next empty slot)
bool Insert(int key) {
  int hash_index = hash(key);
  while(hash_table[hash_index].value != 0 && hash_table[hash_index].key != key)
    hash_index = (hash_index+1) % MAX_HASH_SIZE;
  hash_table[hash_index].key = key;
  ++hash_table[hash_index].value;
  return true;
}

/**
   Hashmap:
   Building further on this idea, we can observe that a + b == -(c + d).
   First, we will count sums of elements a + b from the first two arrays
   using a hashmap. Then, we will enumerate elements from the third and
   fourth arrays, and search for a complementary sum a + b == -(c + d)
   in the hashmap.
**/
int fourSumCount(int *nums1, int nums1Size, int *nums2, int nums2Size, int *nums3, int nums3Size, int *nums4, int nums4Size) {
  int count = 0;
  int numsSize = nums1Size;
  if(nums1 == NULL || nums2 == NULL || nums3 == NULL || nums4 == NULL || nums1Size < 1)
    return count;

  for(int i=0; i<MAX_HASH_SIZE; ++i) {
    hash_table[i].key = INT_MIN;
    hash_table[i].value = 0;
  }

  for(int i=0; i<numsSize; ++i)
    for(int j=0; j<numsSize; ++j)
      Insert(nums1[i] + nums2[j]);

  for(int i=0; i<numsSize; ++i)
    for(int j=0; j<numsSize; ++j)
      count += Search(-(nums3[i] + nums4[j]));
  return count;
}

// AR
int fourSumCount_(int* nums1, int nums1Size, int* nums2, int nums2Size, int* nums3, int nums3Size, int* nums4, int nums4Size) {
  int sum = 0;
  int cnt = 0;
  for (int i=0; i<nums1Size; ++i) {
    sum = nums1[i] + nums2[i] + nums3[i] + nums4[i];
    cnt++;
  }
  return sum;
}

void test() {
  int ret = 0;
  int nums1[] = {1,2};
  int nums2[] = {-2,-1};
  int nums3[] = {-1,2};
  int nums4[] = {0,2};
  ret = fourSumCount(nums1, 2, nums2, 2, nums3, 2, nums4, 2);
  debug("Output = %d", ret);
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**
   => ./a.out
   [test] L=138 :Output = 2
**/
