/*
 * Given an array of integers A sorted in non-decreasing order,
 * return an array of the squares of each number, also in sorted
 * non-decreasing order.
  Input: [-4,-1,0,3,10]
  Output: [0,1,9,16,100]
  Input: [-7,-3,2,3,11]
  Output: [4,9,9,49,121]
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* sortedSquares(int *a, int aSize, int *returnSize) {

    int *out = (int *)malloc(sizeof(aSize * sizeof(int)));
    int i, j, rsz;

    printf ("sz = %d\n", aSize);
    for(i=0; i<aSize; ++i) {
      out[i] = a[i] * a[i];
      printf ("--> a= %d out = %d \n", a[i], out[i]);
    }
    rsz = sizeof(out)/sizeof(out[0]);
    returnSize = &aSize;//&rsz;
    return out;
}

int main() {
  int  input[] =  {-7,-3,2,3,11};
  int aSize = sizeof(input)/sizeof(input[0]);
  int returnSize, *out, i;

  out =  sortedSquares(input, aSize, &returnSize);
  printf ("--> retSz = %d \n", returnSize);
  for(i=0; i<aSize; i++) {
    printf ("--> out = %d \n", out[i]);
  }
  free(out);
}
