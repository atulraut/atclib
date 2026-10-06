/***
    https://leetcode.com/problems/kth-missing-positive-number/
    Kth Missing Positive Number

    Given an array arr of positive integers sorted in
    a strictly increasing order, and an integer k.

    Find the kth positive integer that is missing from
    this array.

    Input: arr = [2,3,4,7,11], k = 5
    Output: 9
    Explanation: The missing positive integers are [1,5,6,8,9,10,12,13,...].
    The 5th missing positive integer is 9.

    Input: arr = [1,2,3,4], k = 2
    Output: 6
    Explanation: The missing positive integers are [5,6,7,...].
    The 2nd missing positive integer is 6.

    Constraints:
    1 <= arr.length <= 1000
    1 <= arr[i] <= 1000
    1 <= k <= 1000
    arr[i] < arr[j] for 1 <= i < j <= arr.length

    Date: Oct 18, 2021
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

/**
   Algorithm:  Approach 1: Brute Force, (N)time
   Check if the kth missing number is less than the
     first element of the array. If it's the case, return k.
   Decrease k by the number of positive integers which
     are missing before the array starts: k -= arr[0] - 1.
   Iterate over the array elements:
   At each step, compute the number of missing positive
     integers in-between i + 1th and ith elements: currMissing = arr[i + 1] - arr[i] - 1.
   Compare k to the currMissing. If k <= currMissing then
     the number to return is in-between arr[i + 1] and arr[i],
     and you could return it: arr[i] + k.
   Otherwise, decrease k by currMissing and proceed further.
   We're here because the element to return is greater than
     the last element of the array. Return it: arr[n - 1] + k.
*/
int __findKthPositive(int* arr, int arrSize, int k) {
  // if the kth missing is less than arr[0]
  if (k <= arr[0] - 1) {
    return k;
  }
  k -= arr[0] - 1;

  // search kth missing between the array numbers
  int n = arrSize;
  for (int i = 0; i < n - 1; ++i) {
    // missing between arr[i] and arr[i + 1]
    int currMissing = arr[i + 1] - arr[i] - 1;
    // if the kth missing is between
    // arr[i] and arr[i + 1] -> return it
    if (k <= currMissing) {
      return arr[i] + k;
    }
    // otherwise, proceed further
    k -= currMissing;
  }

  // if the missing number if greater than arr[n - 1]
  return arr[n - 1] + k;
}
/**
   Complexity Analysis
   Time complexity: O(N) because in the worst case, we have
   to parse all array elements.
   Space complexity: O(1), we don't allocate any additional data structures.
*/

/**
   Approach 1: Brute Force, O(N) time
   Algorithm
   Check if the kth missing number is less than the first
   element of the array. If it's the case, return k.
   Decrease k by the number of positive integers which are
   missing before the array starts: k -= arr[0] - 1.
   Iterate over the array elements:
   At each step, compute the number of missing positive integers
   in-between i + 1th and ith elements: currMissing = arr[i + 1] - arr[i] - 1.
   Compare k to the currMissing. If k <= currMissing then
   the number to return is in-between arr[i + 1] and arr[i],
   and you could return it: arr[i] + k.
   Otherwise, decrease k by currMissing and proceed further.
   We're here because the element to return is greater than
   the last element of the array. Return it: arr[n - 1] + k.
**/
int findKthPositive(int* arr, int arrSize, int k) {
  int left = 0, right = arrSize - 1;
  while (left <= right) {
    int pivot = left + (right - left) / 2;
    // If number of positive integers
    // which are missing before arr[pivot]
    // is less than k -->
    // continue to search on the right.
    if (arr[pivot] - pivot - 1 < k) {
      left = pivot + 1;
      // Otherwise, go left.
    } else {
      right = pivot - 1;
    }
  }

  // At the end of the loop, left = right + 1,
  // and the kth missing is in-between arr[right] and arr[left].
  // The number of integers missing before arr[right] is
  // arr[right] - right - 1 -->
  // the number to return is
  // arr[right] + k - (arr[right] - right - 1) = k + left
  return left + k;
}
/**
   Complexity Analysis
   Time complexity: O(logN), where is a number of elements in the input array.
   Space complexity: O(1), we don't allocate any additional data structures.
**/

int main (int argc, char **argv) {
  int ret = 0;
  int arr[] = {2,3,4,7,11};
  int arrSize = sizeof(arr)/sizeof(arr[0]);
  int k = 5;

  ret = __findKthPositive(arr, arrSize, k);
  debug("Output = %d", ret);
  return 0;
}

/**
   => ./a.out
   [main] L=110 :Output = 9
**/
