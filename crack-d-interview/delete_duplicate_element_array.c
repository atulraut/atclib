/*
* Name - Atul Raut
* Date - March 1, 2016 San Diego, CA-92126
* Ref  - http://www.c4learn.com/c-programs/to-delete-duplicate-elements-in-array.html
***/
#include<stdio.h>
int del_dup_array (int *arr, int size);
int main() {
  int arr[6] = {1,2,3,4,2,2}; 
  int i, j, k, size=5;
  
  size = sizeof(arr) / sizeof(arr[0]);
  printf("\nArray with Unique list  : %d \n", size);
  size = del_dup_array (arr, size);
  for (i = 0; i < size; i++) {
     printf("%d ", arr[i]);
  }
   return (0);
}

int del_dup_array (int *arr, int size) {
  int i, j, k;
  for (i = 0; i < size; i++) {
    for (j = i + 1; j < size;) {
        if (arr[j] == arr[i]) {
          for (k =j; k<size; k++) {
            if ((size-1) == k)
              arr[k+1] = 0;
              printf ("i=%d, j=%d, k=%d, k=[%d], k+1=[%d] size = %d\n",i,j,k,  arr[k], arr[k + 1], size);
              arr[k] = arr[k + 1];
            }
            size--;
        } else
        j++;
    }
  } 
  return size;
}
