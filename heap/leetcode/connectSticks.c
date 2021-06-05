/***
    Medium : 1167. Minimum Cost to Connect Sticks
    https://leetcode.com/problems/minimum-cost-to-connect-sticks/

    You have some number of sticks with positive integer lengths.
    These lengths are given as an array sticks, where sticks[i]
    is the length of the ith stick.
    You can connect any two sticks of lengths x and y into one
    stick by paying a cost of x + y. You must connect all the
    sticks until there is only one stick remaining.

    Return the minimum cost of connecting all the given sticks
    into one stick in this way.

    Input: sticks = [2,4,3]
    Output: 14
    Explanation: You start with sticks = [2,4,3].
    1. Combine sticks 2 and 3 for a cost of 2 + 3 = 5. Now you have sticks = [5,4].
    2. Combine sticks 5 and 4 for a cost of 5 + 4 = 9. Now you have sticks = [9].
    There is only one stick left, so you are done. The total cost is 5 + 9 = 14.

    Input: sticks = [1,8,3,5]
    Output: 30
    Explanation: You start with sticks = [1,8,3,5].
    1. Combine sticks 1 and 3 for a cost of 1 + 3 = 4. Now you have sticks = [4,8,5].
    2. Combine sticks 4 and 5 for a cost of 4 + 5 = 9. Now you have sticks = [9,8].
    3. Combine sticks 9 and 8 for a cost of 9 + 8 = 17. Now you have sticks = [17].
    There is only one stick left, so you are done. The total cost is 4 + 9 + 17 = 30.

    Input: sticks = [5]
    Output: 0
    Explanation: There is only one stick, so you don't need to do anything. The total cost is 0.


    Constraints:
    1 <= sticks.length <= 104
    1 <= sticks[i] <= 104

    Date: 4 June 2021
    San Diego, CA.
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

void minHeapify(int *a, int n, int i) {
  int child, tmp, smallest;

  child = 2 * i + 1;
  while (child < n) {
    smallest = (a[child] < a[i]) ? child : i;
    if (child + 1 < n && a[child + 1] < a[smallest]) smallest = child + 1;
    if (smallest == i) break;
    tmp = a[i]; a[i] = a[smallest]; a[smallest] = tmp;
    i = smallest; child = 2 * i + 1;
  }

  return;
}

void buildMinHeap(int *a, int n) {
  int i;

  for (i = n/2 - 1; i >= 0; i--) {
    minHeapify(a, n, i);
  }

  return;
}

int deleteMin(int *a, int n) {
  int r;

  r = a[0]; a[0] = a[n - 1];
  minHeapify(a, n - 1, 0);

  return r;
}

void addMinHeap(int *a, int n, int r) {
  int i, parent, tmp;

  a[n++] = r;
  i = n - 1; parent = (i - 1)/2;
  while (parent >= 0 && a[parent] > a[i]) {
    tmp = a[i]; a[i] = a[parent]; a[parent] = tmp;
    i = parent; parent = (i - 1)/2;
  }

  return;
}

int connectSticks(int* sticks, int sticksSize) {
  int i, r, sum, lastSum;
  int *a;

  a = (int *)malloc(sticksSize * sizeof(int));
  for (i = 0; i < sticksSize; i++) {
    a[i] = sticks[i];
  }
  buildMinHeap(a, sticksSize);

  sum = 0;
  while (sticksSize > 1) {
    r = deleteMin(a, sticksSize--) + deleteMin(a, sticksSize--);
    sum += r;
    addMinHeap(a, sticksSize++, r);
  }
  free(a);

  return sum;
}

int main () {
  int ret = 0;
  int sticks[] = {1, 8 ,3 ,5};
  int sticksSize = sizeof(sticks) / sizeof(sticks[0]);

  ret = connectSticks(sticks, sticksSize);
  debug("Output = %d", ret);
  return 0;
}

/**
   => ./a.out
   [main] L=130 :Output = 30
**/
