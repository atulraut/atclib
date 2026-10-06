/***

    https://leetcode.com/problems/remove-element/

    LC-27 : Remove Element

    Given an integer array nums and an integer val, remove all occurrences
    of val in nums in-place.
    The order of the elements may be changed. Then return the number of elements
    in nums which are not equal to val.

    Consider the number of elements in nums which are not equal to val be k,
    to get accepted, you need to do the following things:

    Change the array nums such that the first k elements of nums contain the
    elements which are not equal to val. The remaining elements of nums are
    not important as well as the size of nums.
    Return k.

    Custom Judge:
    The judge will test your solution with the following code:

    int[] nums = [...]; // Input array
    int val = ...; // Value to remove
    int[] expectedNums = [...]; // The expected answer with correct length.
    // It is sorted with no values equaling val.

    int k = removeElement(nums, val); // Calls your implementation

    assert k == expectedNums.length;
    sort(nums, 0, k); // Sort the first k elements of nums
    for (int i = 0; i < actualLength; i++) {
    assert nums[i] == expectedNums[i];
    }
    If all assertions pass, then your solution will be accepted.

    Assert nums[i] == expectedNums[i];

    If all assertions pass, then your solution will be accepted.

    Example 1:
    Input: nums = [3,2,2,3], val = 3
    Output: 2, nums = [2,2,_,_]
    Explanation: Your function should return k = 2, with the first two
    elements of nums being 2.
    It does not matter what you leave beyond the returned k
    (hence they are underscores).

    Example 2:
    Input: nums = [0,1,2,2,3,0,4,2], val = 2
    Output: 5, nums = [0,1,4,0,3,_,_,_]
    Explanation: Your function should return k = 5, with the first
    five elements of nums containing 0, 0, 1, 3, and 4.
    Note that the five elements can be returned in any order.
    It does not matter what you leave beyond the returned k
    (hence they are underscores).

    Constraints:
    0 <= nums.length <= 100
    0 <= nums[i] <= 50
    0 <= val <= 100

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Fri Mar  6 08:49:04 PST 2026
    Folsom, CA.
*/

/*----------------------------------- Header --------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h> // va_arg
#include <ctype.h>
#include <limits.h>
#include <string.h>  /* malloc */
#include <stdbool.h>
#include <math.h>
#include <assert.h>
#include <stdint.h> /* uint32_t */
#include <unistd.h> /* sleep */

#define debug(str,args...) printf("L=[%d][%s]->[%s] :| "str"\n",__LINE__,__FILE__, __func__, ##args)

int removeElement(int* nums, int numsSize, int val) {

  int read_ptr = 0; // Reads Everything
  int writ_ptr = 0; // Writes Selective

  for (read_ptr=0; read_ptr<numsSize; ++read_ptr) {
    if(nums[read_ptr] != val)
      nums[writ_ptr++] = nums[read_ptr];
  }
  return writ_ptr;
}

void test() {
  int ret = 0;
  int nums[] = {2, 3, 3, 2};
  int numsSize = 4;
  int val = 3;

  ret = removeElement(nums, numsSize, val);

  debug("Output = %d", ret);
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**
   L=[104][1_remove_element_LC_27.c]->[test] :| Output = 2
**/
