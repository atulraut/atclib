/***
    870. Advantage Shuffle : Medium
    Given two arrays A and B of equal size, the advantage of A with
    respect to B is the number of indices i for which A[i] > B[i].
    Return any permutation of A that maximizes its advantage with respect to B.

    Input: A = [2,7,11,15], B = [1,10,4,11]
    Output: [2,11,7,15]

    Input: A = [12,24,8,32], B = [13,25,32,11]
    Output: [24,32,8,12]
    Note:
    1 <= A.length = B.length <= 10000
    0 <= A[i] <= 10^9
    0 <= B[i] <= 10^9

    Date : 26 March 2021
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

int cmp(const void *a, const void *b) { return (*(int *)a - *(int *)b); }

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *advantageCount2(int *A, int ASize, int *B, int BSize, int *returnSize) {

  int *ans = (int *)malloc(sizeof(int) * ASize);
  int sort_b[BSize][2];  // sort B with original index

  for (int i = 0; i < BSize; i++) {
    sort_b[i][0] = B[i];
    sort_b[i][1] = i;
  }

  qsort(A, BSize, sizeof(int), cmp);
  qsort(sort_b, BSize, sizeof(sort_b[0]), cmp);

  int l = 0, r = BSize - 1;
  for (int i = 0; i < ASize; i++) {
    if (A[i] > sort_b[l][0]) {
      ans[sort_b[l][1]] = A[i];
      l++;
    } else {
      ans[sort_b[r][1]] = A[i];
      r--;
    }
  }

  *returnSize = ASize;
  return ans;
}

typedef struct abc
{
  int num;
  int ind;
} Two;

int compare(const void *ap , const void *bp)
{
  Two* a=(Two *)ap;
  Two *b=(Two *)bp;
  return a->num>=b->num ? 1:-1;
}


/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* advantageCount(int* A, int ASize, int* B, int BSize, int* returnSize){
  Two *atwo = malloc(sizeof(Two)*ASize);
  Two *btwo = malloc(sizeof(Two)*BSize);
  int *ans = malloc(sizeof(int)*BSize);
  for(int i=0;i<BSize;i++) {
    atwo[i].num=A[i];
    atwo[i].ind=0;
    btwo[i].num=B[i];
    btwo[i].ind=i;
  }

  qsort(atwo,ASize,sizeof(atwo[0]),compare);
  qsort(btwo,BSize,sizeof(btwo[0]),compare);
  int ptr=0,count=0;

  for(int i=0;i<BSize;i++) {
    if(atwo[i].num>btwo[ptr].num) {
      ans[btwo[ptr].ind]=atwo[i].num;
      atwo[i].ind=1;
      ptr++;
    }
  }

  if(ptr!=BSize) {
    for(int i=0;i<ASize;i++) {
      if(!atwo[i].ind) {
	ans[btwo[ptr++].ind]=atwo[i].num;
      }
    }
  }
  *returnSize=ASize;
  return ans;
}

int main () {
  int A[] = {2,7,11,15};
  int B[] = {1,10,4,11};
  int returnSize;
  int ASize = sizeof(B)/sizeof(B[0]);
  int BSize = sizeof(A)/sizeof(A[0]);

  int*ret = advantageCount(A, ASize, B, BSize, &returnSize);

  for (int i=0; i<returnSize; i++)
    debug ("--> ret = %d", ret[i]);
  return 0;
}

/**
   => ./a.out
   [main] L=124 :--> ret = 2
   [main] L=124 :--> ret = 11
   [main] L=124 :--> ret = 7
   [main] L=124 :--> ret = 15
**/
