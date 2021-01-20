#include <stdio.h>
#include <stdlib.h>

int merge_sort (int a[], int m, int b[], int n, int c[]);

int main() {
  int A[] = {3,5,7,9};
  int B[] = {2,4,6};
  int szA = sizeof(A) / sizeof(A[0]);
  int szB = sizeof(B) / sizeof(B[0]);
  int *C = (int *)malloc((sizeof(szA+szB)));;
  int i;
  merge_sort (A, 4, B, 3, C);
  for (i=0; i<7; i++)
    printf("-->[%d]!\n", C[i]);
  return 0;
}

int merge_sort (int *a, int m, int *b, int n, int *c) {
  int i = 0; // m
  int j = 0; // n
  int k = -1; int p;
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
