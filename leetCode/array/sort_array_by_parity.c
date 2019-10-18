/*
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */

#include <stdio.h>
#include <stdlib.h>

int* sortArrayByParity(int *a, const int asize, int *retsize) {
  int i;
  int beg = 0, end = asize-1;
  int *newarr = (int *)malloc(sizeof(int) * asize);
  if (NULL == newarr)
    return;
  *retsize = asize;

  for(i=0; i<asize; i++) {
    if(a[i] % 2 == 0)
      newarr[beg++] = a[i];
    else
      newarr[end--] = a[i];
  }
  for (i=0; i<asize; i++) {
    printf ("-> %d\n", newarr[i]);
  }
  return newarr;
}

int main() {
  int ar[] = {2,1,3,4};
  int asz;
  int *sz = sortArrayByParity(ar, 4, &asz);

  for (int i=0; i<asize; i++) {
    printf ("-> %d\n", newarr[i]);
  }
  free(sz);
}
