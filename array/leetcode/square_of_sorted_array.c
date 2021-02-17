/*
 * Given an array of integers A sorted in non-decreasing order,
 * return an array of the squares of each number, also in sorted
 * non-decreasing order.
  Input: [-4,-1,0,3,10]
  Output: [0,1,9,16,100]
  Input: [-7,-3,2,3,11]
  Output: [4,9,9,49,121]
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

/**
 * Leet code accepted
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* sortedSquares(int* A, int ASize, int* returnSize){
    int r = ASize - 1;
    for (int i = 0; i < ASize; ++i) {
        if (A[i] > -1) { r = i; break; }
    }

    // Determine l index
    int l = r - 1;
    
    // Construct ans
    int* ans = malloc(ASize*sizeof(int));
    int* cur = ans;    
    while (l > -1 && r < ASize) {
        int labs = A[l] > 0 ? A[l] : -A[l];
        int rabs = A[r] > 0 ? A[r] : -A[r];

        if (labs < rabs) { *cur++ = A[l]*A[l]; --l; }
        else             { *cur++ = A[r]*A[r]; ++r; }
    }

    while (l > - 1)   { *cur++ = A[l]*A[l]; --l; }
    while (r < ASize) { *cur++ = A[r]*A[r]; ++r; }

    *returnSize = ASize;
    return ans;  
}

int main() {
    int retSz, *ret, i;
    int arr[] = {-4,-1,0,3,10}; // leetcode work
//   int arr[] = {4,5,3,2,10}; // leetcode didnt work 
    int sz = sizeof(arr)/sizeof(arr[0]);
    ret = sortedSquares(arr, sz, &retSz);
    for(i=0; i<retSz; i++) {
        printf("Hello World = %d \n", ret[i]);
    }
    free(ret);
    return 0;
}
