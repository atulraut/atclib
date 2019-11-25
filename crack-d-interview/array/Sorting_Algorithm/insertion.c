/*
 * WAP for Insertion Sort
 * Hanuman Ki Jai
 */
#include <stdio.h>

/*
  1. During each iteration first element inthe unsorted set is picked up
  & inserted into the correct position int the sorted set.
*/
void insertionSort(int list[], int n) {
  // sort list[0] to list[n-1] in ascedning order
  for(int h=1; h<n; h++) {
    int key = list[h];
    int j=h-1; // start comparing with previous item
    while(j>=0 && key < list[j]) {
      list[j+1] = list[j];
      --j;
    }
    list[j+1] = key;
  }//end for
}//end insertionSort


int main() {
  printf("Insertion Sort!\n");
  int i, sz;

  int list[] = {7, 2, 4, 1, 5, 3};
  sz = sizeof(list)/sizeof(list[0]);
  printf("Original Array \n");
  for(i=0; i<sz; i++)
    printf ("->[%d]", list[i]);
  printf("\n");
  insertionSort(list, sz);
  printf("Sorted Array \n");
  for(i=0; i<sz; i++)
    printf ("->[%d]", list[i]);
  printf("\n");
  return 0;
}

/*
Divide Array into 2:
--------------------
Step 0:
Sorted | Unsorted
---------------------
    |
---------------------------
  7 | 2 | 4 | 1 | 5 | 3 |
---------------------------
  0 | 1   2   3   4   5
---------------------------
Step 1: Pick 1st Element
----------------------
  1 | X | 5 | 2 | 9 |
----------------------
  0 | 1   2   3   4
----------------------
Value <-- 2
-------------
*/
