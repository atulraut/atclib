/***
    https://leetcode.com/problems/get-maximum-in-generated-array/
    1646. Get Maximum in Generated Array

    You are given an integer n. An array nums of length n + 1 is
    generated in the following way:

    nums[0] = 0
    nums[1] = 1
    nums[2 * i] = nums[i] when 2 <= 2 * i <= n
    nums[2 * i + 1] = nums[i] + nums[i + 1] when 2 <= 2 * i + 1 <= n
    Return the maximum integer in the array nums​​​.


    Example 1:

    Input: n = 7
    Output: 3
    Explanation: According to the given rules:
    nums[0] = 0
    nums[1] = 1
    nums[(1 * 2) = 2] = nums[1] = 1
    nums[(1 * 2) + 1 = 3] = nums[1] + nums[2] = 1 + 1 = 2
    nums[(2 * 2) = 4] = nums[2] = 1
    nums[(2 * 2) + 1 = 5] = nums[2] + nums[3] = 1 + 2 = 3
    nums[(3 * 2) = 6] = nums[3] = 2
    nums[(3 * 2) + 1 = 7] = nums[3] + nums[4] = 2 + 1 = 3
    Hence, nums = [0,1,1,2,1,3,2,3], and the maximum is 3.
    Example 2:
    Input: n = 2
    Output: 1
    Explanation: According to the given rules, the maximum between nums[0], nums[1], and nums[2] is 1.

    Example 3:
    Input: n = 3
    Output: 2
    Explanation: According to the given rules, the maximum between nums[0], nums[1], nums[2], and nums[3] is 2.
    Constraints:
    0 <= n <= 100

    Quick way to understand algorithm : https://www.youtube.com/watch?v=BbYzOfoydPs
    nums[2 * i] Is EVEN Number which is Equal to = nums[i] when 2 <= 2 * i <= n
    ==> Which can be/written as nums[i/2]
    nums[2 * i + 1] Is ODD Number which is Equal to  = nums[i] + nums[i + 1] when 2 <= 2 * i + 1 <= n
    ==> Which can be/written as nums[i/2] + nums[i/2 + 1]

    Date : 1-20-21 {Palindrome Date}
    San Deigo, CA
*/
#include <stdio.h>
#include "../../at_lib.h"

#define max(x, y) (((x) > (y)) ? (x) : (y))

int getMaximumGenerated(int n) {
  int i;
  if (n == 0) {
    return 0;
  }
  int nums[n + 1];
  int maximumValue = 1;

  nums[1] = 1;

  for (i = 2; i <= n; i++) {
    if (i % 2 == 0)
      nums[i] = nums[i / 2];
    else
      nums[i] = nums[i / 2] + nums[i / 2 + 1];
    maximumValue = max(maximumValue, nums[i]);
  }
  return maximumValue;
}


int main () {
  debug ("O/p = %d ", getMaximumGenerated(7));

  return 0;
}


/***
    Approach 3: Using Division
    We could generate current value based on
    previous values (using division).

    nums[i*2] is equal to the value of nums[i].

    This could be written as, if i is EVEN, nums[i] is equal to the value of nums[i/2]

    nums[i*2+1] is equal to the value of nums[i] + nums[i+1].

    This could be written as, if i is ODD, nums[i] is equal to value of nums[i/2] + nums[i/2+1]

    Algorithm

    Build an array nums of size n+1 using the array generation rules.

    Iterate from 1 to n where i is the current index of array nums. As we iterate over
    each array element, calculate the value of current position nums[i] as follows,
    If current index i is even, the value of nums[i] is equal to nums[i/2].
    Else, the value of nums[i] is equal to nums[i/2] + nums[i/2+1].

    The maximum value would only be updated if the value at the current position
    nums[i] is greater than the maximum value calculated so far.

    Time Complexity : O(n), as we iterate nnn times to build the array.
    Space Complexity: O(n), as we use an array nums of size n.
    => ./a.out
    [main] L=77 :O/p = 3
*/
