/***
    https://leetcode.com/problems/two-sum/
    1 Two Sum - UNSorted Array
    Hashing if Array is UNSorted ->

    Problem : 2 Sum In A [UN]Sorted Array
    Given an array sorted in non-decreasing order and a target number,
    find the indices of the two values from the array that sum
    up to the given target number.

    Example
    {
    "numbers": [1, 2, 3, 5, 10],
    "target": 7
    }
    Output:

    [1, 3]
    Sum of the elements at index 1 and 3 is 7.

    Notes
    In case when no answer exists, return an array of size two with
    both values equal to -1, i.e., [-1, -1].
    In case when multiple answers exist, you may return any of them.
    The order of the indices returned does not matter.
    A single index cannot be used twice.
    Constraints:

    2 <= array size <= 105
    -105 <= array elements <= 105
    -105 <= target number <= 105
    Array can contain duplicate elements. >--> Take a **NOTE**
    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Fri Oct  2 09:05:53 PDT 2026
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
#define max(a,b)				\
  ({ __typeof__ (a) _a = (a);			\
    __typeof__ (b) _b = (b);			\
    _a > _b ? _a : _b; })
#define min(a,b)				\
  ({ __typeof__ (a) _a = (a);			\
    __typeof__ (b) _b = (b);			\
    _a < _b ? _a : _b; })
/*----------------------------------- Micro --------------------------------------*/

#define HASH_SIZE 10007

struct HashNode {
  int key;                // nums[i]
  int index;              // i
  struct HashNode *next;  // collision handling
};

static int hash(int key) {
  int h = key % HASH_SIZE;
  // Handle negative numbers
  if (h < 0)
    h += HASH_SIZE;
  debug ("h = %d ", h);
  return h;
}

static void insert(struct HashNode **table, int key, int index) {
  int h = hash(key);

  struct HashNode *node = malloc(sizeof(*node));

  node->key = key;
  node->index = index;

  // Insert at beginning of linked list
  node->next = table[h];
  table[h] = node;
}

static int search(struct HashNode **table, int key) {
  int h = hash(key);

  struct HashNode *node = table[h];

  while (node != NULL) {
    if (node->key == key)
      return node->index;

    node = node->next;
  }

  return -1;
}

int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
  struct HashNode **table =
    calloc(HASH_SIZE, sizeof(struct HashNode *));

  for (int i = 0; i < numsSize; i++) {

    int complement = target - nums[i];
    debug ("[%d] complement = %d target=%d nums[i]=%d",i, complement, target, nums[i]);
    // Search complement first
    int index = search(table, complement);
    debug ("index = %d", index);
    if (index != -1) {
      int *result = malloc(2 * sizeof(int));

      result[0] = index;
      result[1] = i;

      *returnSize = 2;

      // Ideally free hash table here
      return result;
    }
    debug ("[%d] insert = [%d]", i, nums[i]);
    // Store current number and its index
    insert(table, nums[i], i);
  }

  *returnSize = 0;
  return NULL;
}


int main (int argc, char **argv) {
  int* ret;
  /*
    int nums[] = {1, 2, 3, 5, 10};
    int numsSize = sizeof(nums)/sizeof(nums[0]);
    int target = 7;
    int returnSize;
  */
  int nums[] = {2,7,11,15};
  int numsSize = 4;
  int target = 9;


  ret = twoSum(nums, numsSize, target, ret);
  debug("AR Output = [%d]", ret[0]);
  debug("AR Output = [%d]", ret[1]);
  return 0;
}

/**
   [twoSum] L=117 :[0] complement = 7 target=9 nums[i]=2
   [hash] L=78 :h = 7
   [twoSum] L=120 :index = -1
   [twoSum] L=132 :[0] insert = [2]
   [hash] L=78 :h = 2
   [twoSum] L=117 :[1] complement = 2 target=9 nums[i]=7
   [hash] L=78 :h = 2
   [twoSum] L=120 :index = 0
   [main] L=156 :AR Output = [0]
   [main] L=157 :AR Output = [1]
**/

/**
 ORIGINAL ARRAY :
 index      0       1       2       3
          +-----+ +-----+ +-----+ +-----+
 arr[]    |  2  | |  7  | | 11  | | 15  |
          +-----+ +-----+ +-----+ +-----+
             |       |       |       |
             |       |       |       |
             |       |       |       |
             |       |       |       +------ hash(15) = 0
             |       |       +-------------- hash(11) = 1
             |       +---------------------- hash(7)  = 2
             +------------------------------ hash(2)  = 2


                     HASH TABLE
              array of HashNode pointers

              table
                |
                v
          +-------------+
table[0]  | pointer     | --------> +------------------+
          +-------------+           | key   = 15       |
                                    | index = 3        |
                                    | next  = NULL     |
                                    +------------------+

          +-------------+
table[1]  | pointer     | --------> +------------------+
          +-------------+           | key   = 11       |
                                    | index = 2        |
                                    | next  = NULL     |
                                    +------------------+

          +-------------+
table[2]  | pointer     | ----+
          +-------------+     |
                              v
                        +------------------+
                        | key   = 7        |
                        | index = 1        |
                        | next  -----------+------+
                        +------------------+      |
                                                  v
                                           +------------------+
                                           | key   = 2        |
                                           | index = 0        |
                                           | next  = NULL     |
                                           +------------------+

          +-------------+
table[3]  | NULL        |
          +-------------+

          +-------------+
table[4]  | NULL        |
          +-------------+

            "HEAD"
                |
                v
table[h] ---> NODE 1 ---> NODE 2 ---> NODE 3 ---> NULL
                ^           ^           ^
                |           |           |
             start       next        next

  **/
