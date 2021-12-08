/***
    https://leetcode.com/problems/maximum-units-on-a-truck/
    Maximum Units on a Truck

    You are assigned to put some amount of boxes onto one truck.
    You are given a 2D array boxTypes,
    where boxTypes[i] = [numberOfBoxesi, numberOfUnitsPerBoxi]:

    numberOfBoxesi is the number of boxes of type i.
    numberOfUnitsPerBoxi is the number of units in each box of the type i.
    You are also given an integer truckSize, which is the maximum
    number of boxes that can be put on the truck. You can choose any
    boxes to put on the truck as long as the number of boxes does not
    exceed truckSize.

    Return the maximum total number of units that can be put on the truck.

    Input: boxTypes = [[1,3],[2,2],[3,1]], truckSize = 4
    Output: 8
    Explanation: There are:
    - 1 box of the first type that contains 3 units.
    - 2 boxes of the second type that contain 2 units each.
    - 3 boxes of the third type that contain 1 unit each.
    You can take all the boxes of the first and second types, and one
    box of the third type.
    The total number of units will be = (1 * 3) + (2 * 2) + (1 * 1) = 8.

    Input: boxTypes = [[5,10],[2,5],[4,7],[3,9]], truckSize = 10
    Output: 91

    Constraints:
    1 <= boxTypes.length <= 1000
    1 <= numberOfBoxesi, numberOfUnitsPerBoxi <= 1000
    1 <= truckSize <= 106

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address maximumUnits.c -lm

    Date: 12/6/2021
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

int cmp(const void *aa, const void *bb) {
  const int *a = *(const int **)aa;
  const int *b = *(const int **)bb;

  if (b[1] == a[1])
    return b[0] - a[0];

  return (b[1] - a[1]);
}


int maximumUnits(int** boxTypes, int boxTypesSize, int* boxTypesColSize, int truckSize) {
  int i = 0, max = 0;

  qsort(boxTypes, boxTypesSize, sizeof(int *), cmp);

  while (truckSize >= 0 && i < boxTypesSize) {
    if (truckSize >= boxTypes[i][0]) {
      debug ("i = %d [%d][%d]", i, boxTypes[i][0], boxTypes[i][1]);
      max += boxTypes[i][1] * boxTypes[i][0];
    } else {
      max += boxTypes[i][1] * truckSize;
    }
    truckSize -= boxTypes[i][0];
    debug ("i = %d truckSize = %d max = %d", i, truckSize, max);
    i++;
  }

  return max;
}

int cmp1(const void *aa, const void *bb) {
  const int *b = *(const int **)bb;
  const int *a = *(const int **)aa;

  if (b[1] == a[1])
    return b[0] - a[0];
  else
    return b[1] - a[1];
}

int maximumUnits1(int** boxTypes, int boxTypesSize, int* boxTypesColSize, int truckSize) {
  if (boxTypes == NULL || boxTypesSize == 0 || truckSize == 0)
    return 0;

  qsort(boxTypes, boxTypesSize, sizeof boxTypes[0], cmp1);

  int i = 0, ans = 0;

  while (truckSize >= 0 && i < boxTypesSize) {
    if (truckSize >= boxTypes[i][0]) {
      ans += boxTypes[i][1] * boxTypes[i][0];
      truckSize -= boxTypes[i][0];
    } else {
      ans += boxTypes[i][1] * truckSize;
      truckSize -= boxTypes[i][0];
    }
    i++;
  }

  return ans;
}

int** create_matrix(int rows, int cols) {
  int** max = (int**)calloc(sizeof(int), rows);
  for (int i=0; i<rows; ++i) {
    max[i] = (int*)calloc(sizeof(int *),  cols);
  }
  return max;
}

int main (int argc, char **argv) {
  int ret = 0;
  int rows = 3, cols = 2;
  int boxTypesSize = 2;
  int boxTypesColSize = 3;
  int truckSize = 4;

  int **grid = create_matrix(rows, cols);

  //[[1,3],[2,2],[3,1]]

  *(*(grid + 0) + 0) = 1;
  *(*(grid + 0) + 1) = 3;

  *(*(grid + 1) + 0) = 2;
  *(*(grid + 1) + 1) = 2;

  *(*(grid + 2) + 0) = 3;
  *(*(grid + 2) + 1) = 1;

  ret = maximumUnits(grid, boxTypesSize, &boxTypesColSize, truckSize);
  debug("Output = %d", ret);
  return 0;
}

/**
   => ./a.out
   [maximumUnits] L=86 :i = 0 [1][3]
   [maximumUnits] L=92 :i = 0 truckSize = 3 max = 3
   [maximumUnits] L=86 :i = 1 [2][2]
   [maximumUnits] L=92 :i = 1 truckSize = 1 max = 7
   [main] L=160 :Output = 7
**/
