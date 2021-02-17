#include <stdio.h>
#include <stdlib.h>

void merge_sort (int *a, int m, int *b, int n, int *c, int szc) {
  int i = 0; // m
  int j = 0; // n
  int k = -1;

  if (szc != (m+n))
    printf ("[%s] Something Went Wrong szc=%d \n", __func__,  szc);
  while (i < m && j < n) { // if at least 1 number in both array
    if (a[i] < b[j]) { // if a < b copy a to c
      c[++k] = a[i++];
    } else { // copy b to c
      c[++k] = b[j++];
    }
  }
  if (i == m) { // a is ended copy remain b to c
    for (; j<n; j++)
      c[++k] = b[j];
  } else { // a not ended copy a to c
    for (; i<m; i++) {
      c[++k] = a[i];
    }
  }
  printf ("end i=%d, j=%d, k=%d\n", i, j, k);
  for (i=0; i<7; i++)
    printf("Here-->[%d]\n", c[i]);
}

int main() {
  int a[] = {3,5,7,9};
  int b[] = {2,4,6};
  int sza = sizeof(a) / sizeof(a[0]);
  int szb = sizeof(b) / sizeof(b[0]);
  int szc = sza + szb;
  int *c = (int *)malloc(sizeof(int) * (szc));
  c[szc] = 0;

  printf ("[%s] sza = %d szb = %d  szc = %d \n", __func__, sza, szb, szc);
  int i;
  merge_sort (a, sza, b, szb, c, szc);
  for (i=0; i<7; i++)
    printf("-->[%d]!\n",c[i]);
  return 0;
}
