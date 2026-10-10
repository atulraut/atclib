/***

    Fixed-size sliding window

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Thu Oct  8 09:48:06 PDT 2026
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

int maxSum(int arr[], int n, int k) {
    if (k <= 0 || k > n)
        return INT_MIN;

    int sum = 0;

    // Step 1: Calculate first window
    for (int i = 0; i < k; i++)
        sum += arr[i];

    int maxSum = sum;

    // Step 2: Slide the window
    for (int i = k; i < n; i++) {
        sum += arr[i];      // Add incoming
        sum -= arr[i - k];  // Remove outgoing

        if (sum > maxSum)
            maxSum = sum;
    }

    return maxSum;
}

int test(void) {
    int arr[] = {2, 1, 5, 1, 3, 2};
    int n = sizeof(arr) / sizeof(arr[0]);

    debug("Max sum = %d\n", maxSum(arr, n, 3));
    return 0;
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**
   Output: Max sum = 9
**/

/**
   Memorize: sum = sum + incoming - outgoing
   Time: O(n), Extra space: O(1). The example assumes sums fit in int.
**/
