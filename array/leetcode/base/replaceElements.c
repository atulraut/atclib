/***
    LeetCode: Replace Elements with Greatest Element on Right Side
    https://leetcode.com/explore/featured/card/fun-with-arrays/511/in-place-operations/3259/
    https://leetcode.com/problems/replace-elements-with-greatest-element-on-right-side/

    Given an array arr, replace every element in that array with the greatest
    element among the elements to its right, and replace the last element with -1.

    After doing so, return the array.

    Example 1:

    Input: arr = [17,18,5,4,6,1]
    Output: [18,6,6,6,1,-1]
    Explanation:
    - index 0 --> the greatest element to the right of index 0 is index 1 (18).
    - index 1 --> the greatest element to the right of index 1 is index 4 (6).
    - index 2 --> the greatest element to the right of index 2 is index 4 (6).
    - index 3 --> the greatest element to the right of index 3 is index 4 (6).
    - index 4 --> the greatest element to the right of index 4 is index 5 (1).
    - index 5 --> there are no elements to the right of index 5, so we put -1.

    Example 2:

    Input: arr = [400]
    Output: [-1]
    Explanation: There are no elements to the right of index 0.

    Constraints:

    1 <= arr.length <= 104
    1 <= arr[i] <= 105


    Date : 1-23-21 {Palindrome}
    San Diego, CA
*/
#include <stdio.h>
#include "../../../at_lib.h"

/***
 * Note: The returned array must be malloced, assume caller calls free().
 * Hint: Keep the maximum value seen so far.
 */
int* replaceElements(int* arr, int arrSize, int* returnSize){
  int i=0, tmp = 0, max = -1;
  *returnSize=arrSize;

  for(int i=arrSize-1; i>=0; i--){
    tmp = arr[i];
    arr[i] = max;
    max = (max>tmp) ? max:tmp;
  }
  return arr;
}

int main() {
  int i;
  int arr[] = {17,18,5,4,6,1};
  int returnSize = 6;

  for(i=0; i<returnSize; i++)
    debug ("I/P = %d", arr[i]);

  printf("-----------------------\n");
  int* ret = replaceElements(arr, 6, &returnSize);

  for(i=0; i<returnSize; i++)
    debug ("O/P = %d", arr[i]);

}

/***
    => ./a.out
    [main] L=63 :I/P = 17
    [main] L=63 :I/P = 18
    [main] L=63 :I/P = 5
    [main] L=63 :I/P = 4
    [main] L=63 :I/P = 6
    [main] L=63 :I/P = 1
    -----------------------
    [main] L=69 :O/P = 18
    [main] L=69 :O/P = 6
    [main] L=69 :O/P = 6
    [main] L=69 :O/P = 6
    [main] L=69 :O/P = 1
    [main] L=69 :O/P = -1
*/
