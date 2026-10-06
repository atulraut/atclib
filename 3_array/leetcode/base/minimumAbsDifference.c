/***
    https://leetcode.com/problems/minimum-absolute-difference/
    Minimum Absolute Difference

    Given an array of distinct integers arr, find all pairs of
    elements with the minimum absolute difference of any two elements.

    Return a list of pairs in ascending order(with respect to pairs),
    each pair [a, b] follows
    a, b are from arr
    a < b
    b - a equals to the minimum absolute difference of any two elements in arr

    Input: arr = [4,2,1,3]
    Output: [[1,2],[2,3],[3,4]]
    Explanation: The minimum absolute difference is 1. List all pairs with
    difference equal to 1 in ascending order.

    Input: arr = [1,3,6,10,15]
    Output: [[1,3]]

    Input: arr = [3,8,-10,23,19,-4,-14,27]
    Output: [[-14,-10],[19,23],[23,27]]

    Constraints:2 <= arr.length <= 10^5
    -10^6 <= arr[i] <= 10^6

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: 12/19/2021
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
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int cmp(const void *a, const void *b){
  return *(int*)a > *(int*)b;
}

int** minimumAbsDifference(int* arr, int arrSize, int* returnSize, int** returnColumnSizes) {
  int i, j, min = 66666666, l = arrSize, count = 0;
  qsort(arr, l, sizeof(int), cmp);

  for(i = 0; i < l - 1; i++)
    min = (arr[i + 1] - arr[i]) < min? (arr[i + 1] - arr[i]) : min;

  for(i = 0; i < l - 1; i++)
    if((arr[i + 1] - arr[i]) == min)
      count++;

  *returnSize = count;
  int** output = (int**)malloc(count * sizeof(int*));

  for(i = 0; i < count; i++)
    output[i] = (int*)malloc(2 * sizeof(int));

  for(i = 0, j = 0; i < l - 1; i++)
    if((arr[i + 1] - arr[i]) == min) {
      output[j][0] = arr[i];
      output[j][1] = arr[i + 1];
      j++;
    }

  // *returnColumnSizes, i.e. after dereferencing once, can be seen as a 1D array, where each element is 2 and the length is "count".
  int *temp = (int*)malloc(count * sizeof(int));
  for(i = 0; i < count; i++) {
    temp[i] = 2;
  }
  *returnColumnSizes = temp;

  return output;
}

int cmpfunc (const void * a, const void * b) {
  return ( *(int*)a - *(int*)b );
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** minimumAbsDifference2(int* arr, int arrSize, int* returnSize, int** returnColumnSizes) {
  qsort(arr, arrSize, sizeof(int), cmpfunc);
  int min=INT_MAX,count=0;
  int **ret;

  ret=malloc(sizeof(int*)*5000);

  for(int i=0;i<arrSize-1;i++) {
    if(arr[i+1]-arr[i]<min)  {
      count=1;
      ret[count-1]=malloc(sizeof(int)*2);
      ret[count-1][0]=arr[i];
      ret[count-1][1]=arr[i+1];
      min=arr[i+1]-arr[i];
    } else if(arr[i+1]-arr[i]==min) {
      count++;
      ret[count-1]=malloc(sizeof(int)*2);
      ret[count-1][0]=arr[i];
      ret[count-1][1]=arr[i+1];
    }
  }

  *returnSize=count;
  *returnColumnSizes=malloc(sizeof(int)*count);

  for(int i=0;i<count;i++)
    *((*returnColumnSizes)+i)=2;

  return ret;
}


int main (int argc, char **argv) {
  int** ret;
  int arr[]= {4,2,1,3};
  int arrSize = arrsz(arr);
  int returnSize;
  int* returnColumnSize;

  debug ("sz = %d", arrSize);
  ret =  minimumAbsDifference(arr, arrSize, &returnSize, &returnColumnSize);
  debug ("-> %d -> %d", returnSize, *returnColumnSize);
  for (int i=0; i<returnSize; ++i) {
    for (int j=0; j<*returnColumnSize; ++j) {
      printf("[%d]-[%d] ", i, ret[i][j]);
    }
    printf ("\n");
  }
  return 0;
}

/**
   => ./a.out
   [main] L=150 :sz = 4
   [main] L=152 :-> 3 -> 2
   [0]-[1] [0]-[2]
   [1]-[2] [1]-[3]
   [2]-[3] [2]-[4]
**/
