/*
  Given two lists Aand B, and B is an anagram of A. B is an anagram of A means B is
  made by randomizing the order of the elements in A.
  We want to find an index mapping P, from A to B. A mapping P[i] = j means the ith
  element in A appears in B at index j.
  These lists A and B may contain duplicates. If there are multiple answers, output any of them.
  For example, given
  A = [12, 28, 46, 32, 50]
  B = [50, 12, 32, 46, 28]
  We should return :  [1, 4, 3, 2, 0]
  as P[0] = 1 because the 0th element of A appears at B[1], and P[1] = 4 because the 1st
  element of A appears at B[4], and so on.
  Note:
     A, B have equal lengths in range [1, 100].
     A[i], B[i] are integers in range [0, 10^5].
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* anagramMappings(int* A, int ASize, int* B, int BSize, int* returnSize) {
  int i, j;
  if(ASize != BSize) {
    printf ("Array not anagram, Hence returning! ");
  }
  int *ret = (int *)malloc(ASize * sizeof(int));
  for(i=0; i<ASize; i++) {
    for(j=0; j<BSize; j++) {
      if(A[i] == B[j]) {
	ret[i] = j;
	printf("i=%d j=%d\n", i, j);
	break;	// To Avoid looping second loop once it found equal elements
      }
    }
  }
  return ret;
}

int main() {
  int i, j, ASize, BSize;
  int sz = 4;

  int A[] = {12, 28, 46, 32, 50};
  int B[] = {50, 12, 32, 46, 28};

  ASize = sizeof(A)/sizeof(A[0]);
  BSize = sizeof(B)/sizeof(B[0]);

  int *ret = NULL;

  ret = anagramMappings(A, ASize, B, BSize, ret);

  printf("\n\n");
  for(i=0; i<ASize; i++) {
    printf("-->i=%d <--> %d \n",i, ret[i]);
    }
  printf("\n");
  free(ret);
  printf ("End\n");
}


