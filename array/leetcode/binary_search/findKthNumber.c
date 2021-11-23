/***
    https://leetcode.com/problems/kth-smallest-number-in-multiplication-table/
    Nearly everyone has used the Multiplication Table.
    The multiplication table of size m x n is an integer
    matrix mat where mat[i][j] == i * j (1-indexed).

    Given three integers m, n, and k, return the kth
    smallest element in the m x n multiplication table.

    Input: m = 3, n = 3, k = 5
    Output: 3
    Explanation: The 5th smallest number is 3.

    Input: m = 2, n = 3, k = 6
    Output: 6
    Explanation: The 6th smallest number is 6.


    Constraints:
    1 <= m, n <= 3 * 104
    1 <= k <= m * n

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address findKthNumber.c -lm

    Date: 11/15/2021
    Folsom, CA.
*/

/*----------------------------------- Header --------------------------------------*/
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

/*----------------------------------- Micro --------------------------------------*/
#define debug(str,args...) printf("[%s] L=%d :"str"\n", __func__, __LINE__, ##args)
#define atsizeof(object) (char *)(&object+1) - (char*)(&object)
#define arrsz(x)  (sizeof(x) / sizeof((x)[0]))
#define max(a,b)				\
  ({ __typeof__ (a) _a = (a);			\
    __typeof__ (b) _b = (b);			\
    _a > _b ? _a : _b; })
#define min(a,b)				\
  ({ __typeof__ (a) _a = (a);			\
    __typeof__ (b) _b = (b);			\
    _a < _b ? _a : _b; })
/*----------------------------------- Micro --------------------------------------*/

int count(int m, int n, int x) {
  int count = 0;
  for(int i = 1; i <= m; i++)
    count += min(x/i, n);
  //    count += n < x/i ? n : x/i;
  return count;
}

int findKthNumber(int m, int n, int k) {
  int start = 1, end = m * n + 1;
  while(start < end) {
    int mid = (start + end) / 2;
    debug("count = %d", count(m, n, mid));
    if(count(m, n, mid) >= k)
      end = mid;
    else
      start = mid + 1;
  }
  return start;
}

int main (int argc, char **argv) {
  int ret = 0;
  int m=3;
  int n=3;
  int k=5;

  ret =  findKthNumber(m, n, k);
  debug("Output = %d", ret);
  return 0;
}

/**
   Algorithm

   Let's do the binary search for the answer {A}A.

   Say enough(x) is true if and only if there are {k}k or more values
   in the multiplication table that are less than or equal to {x}x.
   Colloquially, enough describes whether {x}x is large enough to be the k^{th}k
   th
   value in the multiplication table.

   Then (for our answer {A}A), whenever {x ≥ A}, enough(x) is True; and
   whenever {x < A}x < A, enough(x) is False.

   In our binary search, our loop invariant is enough(hi) = True. At
   the beginning, enough(m*n) = True, and whenever hi is set, it is
   set to a value that is "enough" (enough(mi) = True). That means hi will
   be the lowest such value at the end of our binary search.

   This leaves us with the task of counting how many values are less than
   or equal to {x}x. For each of {m}m rows, the i^{th}i
   th
   row looks like {[i, 2*i, 3*i, ..., n*i]}[i, 2*i, 3*i, ..., n*i].
   The largest possible {k*i ≤ x} that could appear is {k = x // i}k = x // i.
   However, if {x}x is really big, then perhaps {k > n}k > n, so in total
   there are {min(k, n) = min(x // i, n)}min(k, n) = min(x // i, n) values
   in that row that are less than or equal to {x}x.

   After we have the count of how many values in the table are less than
   or equal to {x}x, by the definition of enough(x), we want to know if
   that count is greater than or equal to {k}k.
**/
/**
  Complexity Analysis
  Time Complexity: O(m * \log (m*n))O(m∗log(m∗n)).
  Our binary search divides the interval {[lo, hi]}[lo, hi]
  into half at each step. At each step, we call enough
  which requires O(m)O(m) time.
  Space Complexity: O(1)O(1). We only keep integers in
  memory during our intermediate calculations.
**/

/**
   [main] L=61 :Output = 3
**/
