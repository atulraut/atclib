/*
  Given an array of integers, return indices of the two numbers such
  that they add up to a specific target.

  You may assume that each input would have exactly one solution, and
  you may not use the same element twice.

  Example:
  Given nums = [2, 7, 11, 15], target = 9,
  Because nums[0] + nums[1] = 2 + 7 = 9,
  return [0, 1].
*/

#include <stdio.h>
#include <stdlib.h>

 int* get_sum (int *arr, int size, int target) {
   int i, j;
   int *temp = (int *) malloc (2*sizeof(int));
   for(i=0; i<size; i++) {
     for (j=i+1; j<size; j++) {
       if ((arr[i] + arr[j]) == target) {
	 printf ("i=%d j=%d ", i,j);
	 temp[0] = i;
	 temp[1] = j;
	 return temp;
       }
     }
     printf ("\n");
   }
 }

 int main() {
   int i, j;
   //   int arr[] = {2, 7, 11, 15};
   int target = 9;
   int arr[] = {3,2,3};
   target = 6;
   int sz = sizeof(arr) / sizeof(arr[0]);
   int *temp  = get_sum(arr, sz, target);
   sz = sizeof(temp) / sizeof(temp[0]);
   for (i=0; i<sz; i++)
     printf ("--> [%d] ", temp[i]);
   printf ("\n");
 }
