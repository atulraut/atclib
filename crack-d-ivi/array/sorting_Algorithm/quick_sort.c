/***
    https://www.youtube.com/watch?v=COk73cpQbFQ

*/

#include <stdio.h>

void swap(int *i, int *j) {
  int temp = *i;
  *i = *j;
  *j = temp;
}

int partition(int *a, int start, int end) {
  int pivot = a[end];
  int partitionIndex = start; // set partition index as start initially
  for (int i=start; i<end; i++) {
    if (a[i] <= pivot) {
      swap(&a[i], &a[partitionIndex]);
      partitionIndex++;
    }
  }
  swap(&a[partitionIndex], &a[end]); // swap pivot with element as partition index
  return partitionIndex;
}

void quick_sort(int *a, int start, int end) {
  if(start < end) {
    int partitionIndex = partition(a, start, end);
    quick_sort(a, start, partitionIndex-1);
    quick_sort(a, partitionIndex+1, end);
  }
}

int main() {
  int a[] = {7,6,5,4,3,2,1,0};
  quick_sort(a, 0, 7);
  for(int i=0; i<8; i++) {
    printf ("[%d]--> %d \n", i, a[i]);
  }
}
