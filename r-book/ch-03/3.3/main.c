/*
*
* Binary Search Algorithm
***/

#include <stdio.h>

int binarySearch (int [], int, int);

int main () {

  int v [] = {1,5,7,9,23,11,2,8,4,3};
  int key, count, found;
  key   = 8;
  count = 10;
  found = 0; 
  found =  binarySearch (v, count, key);
  if (found == key)
    printf ("\n found = %d\n", found);
  else 
    printf ("\n Key Not Found = %d\n", found);
  return 0;
}

int binarySearch (int v[], int count, int key) {
  int low, mid, high;
  low = 0;
  high = count-1;

  while (low <= high) {
    mid = (low+high)/2;
    //  if (v[mid] == key) {
    //    return key;
    //}
    if (key > v[mid]) {
      printf ("\nInside key >\n");
          low = mid + 1;
    }
    if (key < v[mid]) {
      printf ("\nInside key <\n");
          high = mid -1;
    }
    else 
      return key;
  }
  return -1;
}

