/***
    Leetcode: Remove Element
    https://leetcode.com/problems/remove-element/
    Given an array nums and a value val, remove all instances of that
    value in-place and return the new length.

    Do not allocate extra space for another array, you must do this by
    modifying the input array in-place with O(1) extra memory.

    The order of elements can be changed. It doesn't matter what you
    leave beyond the new length.

    Clarification:
    Confused why the returned value is an integer but your answer is an array?
    Note that the input array is passed in by reference, which means
    a modification to the input array will be known to the caller as well.

    Internally you can think of this:
    // nums is passed in by reference. (i.e., without making a copy)
    int len = removeElement(nums, val);

    // any modification to nums in your function would be known by the caller.
    // using the length returned by your function, it prints the first len elements.
    for (int i = 0; i < len; i++) {
    print(nums[i]);
    }

    Example 1:
    Input: nums = [3,2,2,3], val = 3
    Output: 2, nums = [2,2]
    Explanation: Your function should return length = 2, with the first two
    elements of nums being 2.
    It doesn't matter what you leave beyond the returned length. For example
    if you return 2 with nums = [2,2,3,3] or nums = [2,2,0,0], your answer will be accepted.

    Example 2:
    Input: nums = [0,1,2,2,3,0,4,2], val = 2
    Output: 5, nums = [0,1,4,0,3]
    Explanation: Your function should return length = 5, with the first five
    elements of nums containing 0, 1, 3, 0, and 4. Note that the order of those
    five elements can be arbitrary. It doesn't matter what values are set beyond the returned length.


    Constraints:
    0 <= nums.length <= 100
    0 <= nums[i] <= 50
    0 <= val <= 100

    Date : 1-22-21 {Palindrome Date}
    San Diego, CA
*/

#include <stdio.h>
#include "../../../at_lib.h"

int removeElement(int* nums, int numsSize, int val){
  int i = 0;
  int n = numsSize;
  while (i < n) {
    if (nums[i] == val) {
      debug ("i = %d nums[%d] = %d", i, (n-1), nums[n-1]);
      nums[i] = nums[n - 1];
      debug ("nums[%d] = %d", i, nums[i]);
      // reduce array size by one
      n--;
    } else
      i++;
  }
  debug ("n = %d", n);
  return n;
}

int main () {
  int val = 2;
  int nums[] = {3, 2, 2, 1};
  int ret;

  ret = removeElement(nums, 4, val);

  debug ("o/p = %d", ret);

  for (int i=0; i<ret; i++)
    debug("Post Deletion nums[%d] = %d", i, nums[i]);
  return 0;
}

/***
    => ./a.out
    [removeElement] L=61 :i = 1 nums[3] = 1
    [removeElement] L=63 :nums[1] = 1
    [removeElement] L=61 :i = 2 nums[2] = 2
    [removeElement] L=63 :nums[2] = 2
    [removeElement] L=69 :n = 2
    [main] L=80 :o/p = 2
    [main] L=83 :Post Deletion nums[0] = 3
    [main] L=83 :Post Deletion nums[1] = 1
*/

/***
    Algorithm:

    When we encounter nums[i]=valnums[i] = valnums[i]=val, we can swap
    the current element out with the last element and dispose the last one.
    This essentially reduces the array's size by 1.

    Note that the last element that was swapped in could be the value you
    want to remove itself. But don't worry, in the next iteration
    we will still check this element.
*/
