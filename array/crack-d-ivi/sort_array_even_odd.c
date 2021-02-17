/*
  WAP : Sort Array By Parity.
        Given an array A of non-negative integers, return an array
	consisting of all the even elements of A, followed by all
	the odd elements of A.
*/

#include <stdio.h>
#include <stdlib.h>


int* sortArrayByParity(int* A, const int ASize, int* returnSize) {
  int *newArr = (int*)malloc(ASize * sizeof(int));
    int beg = 0, end = ASize-1;
    *returnSize = ASize;

    for (int i = 0; i < ASize; i++) {
        if (A[i] % 2 == 0)
            newArr[beg++] = A[i];
        else
            newArr[end--] = A[i];
    }

    return newArr;
}

/* Not good one */
int* SsortArrayByParity(int* A, int ASize, int* returnSize) {
  int i, j, temp;

  for(i=0,j=ASize-1; i<ASize; ++i,--j) {
    if((A[i]%2) != 0 && (A[j]%2) == 0) {
      temp = A[i];
      A[i] = A[j];
      A[j] = temp;
    }
  }
  return returnSize;
}

int main () {
  int arr[] = {4,1,2,4};
  int i, j, temp;

  int sz = sizeof(arr)/sizeof(arr[0]);
  int *returnSize = (int *)malloc(sz);
  returnSize = sortArrayByParity(arr, sz, returnSize);

  for(i=0; i<sz; i++) {
    printf ("-->%d \t", returnSize[i]);
  }
  printf ("\n\n");
}

/*
  O/p : -->4 	-->2 	-->4 	-->1
*/
