/***
    1198. Find Smallest Common Element in All Rows
    https://leetcode.com/problems/find-smallest-common-element-in-all-rows/
    Given an m x n matrix mat where every row is sorted in strictly
    increasing order, return the smallest common element in all rows.
    If there is no common element, return -1.
    Input: mat = [[1,2,3,4,5],[2,4,5,8,10],[3,5,7,9,11],[1,3,5,7,9]]
    Output: 5

    Input: mat = [[1,2,3],[2,3,4],[2,3,5]]
    Output: 2

Constraints:
    m == mat.length
    n == mat[i].length
    1 <= m, n <= 500
    1 <= mat[i][j] <= 104
    mat[i] is sorted in strictly increasing order.

    Date : 24 March 2021
    San Diego, CA
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

int smallestCommonElement(int (*mat)[3], int matSize, int* matColSize) {
  int count[10001] = {};
  int row = matSize;
  int col = matColSize[0];

  for (int j = 0; j < col; ++j) {
    for (int i = 0; i < row; ++i) {
      debug ("mat = %d ", mat[i][j]);
      if (++count[mat[i][j]] == row) {
	debug ("cnt = %d ", count[mat[i][j]]);
	return mat[i][j];
      }
      debug ("cnt = %d ", count[mat[i][j]]);
    }
  }

  return -1;
}

int main () {
  int mat[3][3] = {
    {1, 2, 3},
    {2, 3, 4},
    {2, 3, 5}
  };

  int r = sizeof (mat)/ sizeof (mat[0]);
  int c = sizeof (mat[0]) / sizeof (mat[0][0]);
  debug ("row size = %d col size = %d ", r, c);

  int ret = smallestCommonElement(mat, r, &c);

  debug ("output = %d", ret);

  return 0;
}

/***
    The fact that every row is sorted in the increasing order tells
    us that there are no duplicates within a single row. So, if an
    element appears in all rows, it will appear exactly n times
    (where n is the number of rows).

    We can count all elements, and then pick the smallest one that
    appears n times. This approach has a linear time complexity - at
    the cost of additional memory for storing counts.

    Approach 1: Count Elements
    Iterate through all elements row-by-row and count each element. Since
    elements are constrained to [1...10000], we'll use an array of that
    size to store counts.

    Then, iterate through the array left-to-right, and return the first
    element that appears n times. This is, by the way, how the counting sort works.

    Algorithm :
    1] Iterate i through each row.
    -->Iterate j through each column.
    -->Increment count for element mat[i][j].
    2] Iterate k from 1 to 10000.
    -->If count[k] equals n, return k.
    3] Return -1.

    We can improve the average time complexity if we count elements
    column-by-column. This way, smaller elements will be counted first,
    and we can exit as soon as we get to an element that repeats n times.
    Complexity Analysis
    Time complexity: O(nm)\mathcal{O}(nm)O(nm), where nnn and mmm are the
    number of rows and columns.
    Space complexity:
    Constrained problem: O(10000)=O(1)\mathcal{O}(10000)=\mathcal{O}(1)O(10000)=O(1).
    Unconstrained problem: O(k)\mathcal{O}(k)O(k), where kkk is the number of unique
    elements.
*/

/***
    => ./a.out
    [main] L=66 :row size = 3 col size = 3
    [smallestCommonElement] L=45 :mat = 1
    [smallestCommonElement] L=50 :cnt = 1
    [smallestCommonElement] L=45 :mat = 2
    [smallestCommonElement] L=50 :cnt = 1
    [smallestCommonElement] L=45 :mat = 2
    [smallestCommonElement] L=50 :cnt = 2
    [smallestCommonElement] L=45 :mat = 2
    [smallestCommonElement] L=47 :cnt = 3
    [main] L=70 :output = 2
*/
