/***
    Valid Mountain Array

    Given an array of integers arr, return true if and only if
    it is a valid mountain array.

    Recall that arr is a mountain array if and only if:

    arr.length >= 3
    There exists some i with 0 < i < arr.length - 1 such that:
    arr[0] < arr[1] < ... < arr[i - 1] < arr[i]
    arr[i] > arr[i + 1] > ... > arr[arr.length - 1]

    Example 1:
    Input: arr = [2,1]
    Output: false

    Example 2:
    Input: arr = [3,5,5]
    Output: false

    Example 3:
    Input: arr = [0,3,2,1]
    Output: true

    https://leetcode.com/problems/valid-mountain-array/

    Date: 1-23-21 {Palindrome Date}
    San Diego, CA
*/


#include <stdio.h>
#include "../../../at_lib.h"

bool validMountainArray(int* A, int ASize){
  int N = ASize;
  int i = 0;

  // walk up
  while (i+1 < N && A[i] < A[i+1])
    i++;

  // peak can't be first or last
  if (i == 0 || i == N-1)
    return false;

  // walk down
  while (i+1 < N && A[i] > A[i+1])
    i++;

  return i == N-1;
}

int main() {
  int arr[] = {7, 1, 14, 11};

  if(validMountainArray(arr, 4))
    debug ("Is Mountain Array = %d", validMountainArray(arr, 4));
  else
    debug ("NOT Mountain Array = %d", validMountainArray(arr, 4));

  return 0;
}

/***
    => ./a.out
    [main] L=61 :NOT Mountain Array = 0
*/

/***
    Complexity Analysis :

    Time Complexity: O(N)O(N)O(N), where NNN is the length of A.
    Space Complexity: O(1)O(1)O(1
*/
