/**

    Remove duplicates from sorted/unsorted array
    Note, here array size is fix.

    Folsom CA,
    Date : Tue Sep 29 08:42:17 PDT 2026

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

static void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int removeDuplicates(int *nums, int numsSize) {
    if (nums == NULL || numsSize <= 0)
        return 0;

    int i = 0;
    /*
     * Phase 1: Cyclic sort.
     *
     * Assumption:
     *     1 <= nums[i] <= numsSize
     */
    while (i < numsSize) {

        int dest = nums[i] - 1;

        if (nums[i] != nums[dest]) {
            swap(&nums[i], &nums[dest]);
        } else {
            i++;
        }
    }
    /*
     * Phase 2: Compact unique values.
     *
     * After cyclic sort, if nums[i] == i + 1,
     * this is the canonical occurrence of that value.
     */
    int write = 0;
    for (i = 0; i < numsSize; i++) {

        if (nums[i] == i + 1) {
            nums[write++] = nums[i];
        }
    }
    return write;
}

void test() {
  int ret = 0;
  //  int arr[] = {1, 1, 2};
  int arr[] = {0,0,1,1,1,2,2,3,3,4};
  //  int numsSize = 3;
  int numsSize = 10;
  ret = removeDuplicates(arr, numsSize);
  for (int i=0; i<ret; ++i)
    debug("Output => i=%d ret=%d op=%d", i, ret, arr[i]);
}

int main (int argc, char **argv) {
  test();
  return 0;
}
