/***

    https://leetcode.com/problems/maximum-product-subarray

    152. Maximum Product Subarray

    Given an integer array nums, find a subarray that has the largest
    product, and return the product.

    The test cases are generated so that the answer will fit in a 32-bit integer.

    Note that the product of an array with a single element is the
    value of that element.

    Input: nums = [2,3,-2,4]
    Output: 6
    Explanation: [2,3] has the largest product 6.

    Input: nums = [-2,0,-1]
    Output: 0
    Explanation: The result cannot be 2, because [-2,-1] is not a subarray.


    Constraints:
    1 <= nums.length <= 2 * 104
    -10 <= nums[i] <= 10
    The product of any subarray of nums is guaranteed to fit in a 32-bit integer.

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Thu Oct  8 21:24:41 PDT 2026
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

int maxProduct(int* nums, int numsSize) {

}

void test() {
  int ret = 0;

  debug("Output = %d", ret);
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**

 **/
