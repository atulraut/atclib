/***

    Non LC :

    Max Subarray Product Size K
 
    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Thu Oct  8 22:04:46 PDT 2026
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

/**
   Simple C solution — without zeros
   This can't handle divide by zero condition
   e.g.
   curr_product /= arr[i - k];  // Division by zero!
**/
long long maxSubararay_Product(int* nums, int numsSize, int k) {
  long long current_prod = 1;
  long long max_prod  = 1;
  if(k <= 0 || k > numsSize)
    return INT_MIN;

  // Step 1: Calculate 1st window
  for(int i=0; i<k; ++i)
    current_prod *= nums[i];

  max_prod = current_prod;

  // Step 2: Slide window
  for (int i=k; i<numsSize; ++i) {
    current_prod *= nums[i];    // Add incoming
    current_prod /= nums[i-k];  // Remove/Divide/Subtract outgoing

    if(current_prod > max_prod)
      max_prod = current_prod;
  }
  return max_prod;
}

/**
   Simple C solution — with Zeros
   Handle Condtion :
   curr_product /= arr[i - k];  // Division by zero!
   Handles zeros and negative numbers.
   To handle zeros correctly, maintain a zeroCount and a product of the nonzero elements.
**/
long long maxSubararay_Product_Zeros(int* nums, int n, int k) {
  if (k <= 0 || k > n)
    return 0;

  long long curr_product = 1;
  long long maxProduct;
  int zeroCount = 0;

  // First window
  for (int i = 0; i < k; i++) {
    if (nums[i] == 0)
      zeroCount++;
    else
      curr_product *= nums[i];
  }
  debug("zerocount = %d", zeroCount);
  maxProduct = zeroCount ? 0 : curr_product;
  debug("maxProduct = %lld", maxProduct);
 
  // Slide the window
  for (int i = k; i < n; i++) {

    int outgoing = nums[i - k];
    int incoming = nums[i];

    // Remove outgoing
    if (outgoing == 0)
      zeroCount--;
    else
      curr_product /= outgoing;

    // Add incoming
    if (incoming == 0)
      zeroCount++;
    else
      curr_product *= incoming;

    // Calculate current window product
    long long current = zeroCount ? 0 : curr_product;

    if (current > maxProduct)
      maxProduct = current;
  }

  return maxProduct;
}

void test() {

  int nums[] = {1, 2, 3, 4};
  int numsSize = 4;;
  int k = 2;
  //int nums[] = {1, 4, 1, 6, -3, 3, -5, 2, 26};
  //int numsSize = 9;
  //  int k = 4;

  long long  ret1 = maxSubararay_Product(nums, numsSize, k);
  debug("Output = %lld", ret1);

  int arr[] = {2, 0, 3, 4, 5};
  k = 3;
  ret1 = maxSubararay_Product_Zeros(arr, 5, k);
  debug("Output = %lld", ret1);
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**
   Because [3, 4, 5] gives 3 × 4 × 5 = 60.
 **/
