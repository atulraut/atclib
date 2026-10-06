/***
    https://leetcode.com/problems/plus-one/
    Plus One

    You are given a large integer represented as an integer
    array digits, where each digits[i] is the ith digit of
    the integer. The digits are ordered from most significant
    to least significant in left-to-right order. The large
    integer does not contain any leading 0's.

    Increment the large integer by one and return the resulting array of digits.

    Input: digits = [1,2,3]
    Output: [1,2,4]
    Explanation: The array represents the integer 123.
    Incrementing by one gives 123 + 1 = 124.
    Thus, the result should be [1,2,4].

    Input: digits = [4,3,2,1]
    Output: [4,3,2,2]
    Explanation: The array represents the integer 4321.
    Incrementing by one gives 4321 + 1 = 4322.
    Thus, the result should be [4,3,2,2].

    Input: digits = [0]
    Output: [1]
    Explanation: The array represents the integer 0.
    Incrementing by one gives 0 + 1 = 1.
    Thus, the result should be [1].

    Input: digits = [9]
    Output: [1,0]
    Explanation: The array represents the integer 9.
    Incrementing by one gives 9 + 1 = 10.
    Thus, the result should be [1,0].

    Constraints:
    1 <= digits.length <= 100
    0 <= digits[i] <= 9
    digits does not contain any leading 0's.

    Date: 17 Oct 2021
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

int* plusOne(int* digits, int digitsSize, int* returnSize) {
  int carry = 1, i = digitsSize;
  int* ret = (int*)malloc(sizeof(int)*(digitsSize+1));

  while (i > 0) {
    //    debug ("i=%d, digit=%d", i-1, digits[i-1]);
    ret[i] = (digits[i-1] + carry) % 10;
    debug("ret[%d]=%d",i, ret[i]);
    carry  = (digits[i-1] + carry) / 10;
    debug("i=%d carry=%d",i-1, carry);
    debug("");
    i--;
  }

  if (!ret[1]) {
    debug ("Carry");
    // size increased 1, set the first digit
    ret[0] = 1;
    *returnSize = digitsSize+1;
    return ret;
  } else {
    debug("No Carry");
    *returnSize = digitsSize;
    return ret+1;
  }
}
/**
 * Pending
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* plusOne2(int* digits, int digitsSize, int* returnSize) {
   // move along the input array starting from the end
    for (int idx = digitsSize - 1; idx >= 0; --idx) {
      // set all the nines at the end of array to zeros
      if (digits[idx] == 9) {
        digits[idx] = 0;
      }
      // here we have the rightmost not-nine
      else {
        // increase this rightmost not-nine by 1
        digits[idx]++;
        // and the job is done
        return digits;
      }
    }
    // we're here because all the digits are nines
    digits = (int*) realloc(digits, (digitsSize + 4));
    digits[0] = 1;
    return digits;
}

int main (int argc, char **argv) {
  int *ret;
  int digits3[]= {4,3,2,1};
  int digits[]= {9};
  int digitsSize = sizeof(digits)/sizeof(digits[0]);
  int returnSize;

  ret = plusOne(digits, digitsSize, &returnSize);
  for (int i=0; i<returnSize; ++i) {
    debug("Output = %d", ret[i]);
  }
  return 0;
}

/**
   => ./a.out
   [main] L=109 :Output = 4
   [main] L=109 :Output = 3
   [main] L=109 :Output = 2
   [main] L=109 :Output = 2
**/

/**
   => ./a.out
   [plusOne] L=65 :ret[1]=0
   [plusOne] L=67 :i=0 carry=1
   [plusOne] L=68 :
   [plusOne] L=73 :Carry
   [main] L=118 :Output = 1
   [main] L=118 :Output = 0
**/
