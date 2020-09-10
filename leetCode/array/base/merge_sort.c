/***
    Leetcode :   Merge Sorted Array
    https://leetcode.com/explore/featured/card/fun-with-arrays/525/inserting-items-into-an-array/3253/
    Given two sorted integer arrays nums1 and nums2, merge nums2 into nums1 as one sorted array.
    Note:
    The number of elements initialized in nums1 and nums2 are m and n respectively.
    You may assume that nums1 has enough space (size that is equal to m + n) to hold additional elements from nums2.
    Example:
    Input:
    nums1 = [1,2,3,0,0,0], m = 3
    nums2 = [2,5,6],       n = 3O
    Output: [1,2,2,3,5,6]
*/
#include "../../at_lib.h"


void merge(int* nums1, int nums1Size, int m, int* nums2, int nums2Size, int n) {
/*
  int i=m-1, k=m+n-1, j=n-1;
    for (; k>=0 && i>=0 && j>=0;k--)
    {
        if (nums1[i] > nums2[j])
        {
            nums1[k] = nums1[i];
            i--;
        }
        else
        {
            nums1[k] = nums2[j];
            j--;
        }
    }
    if (k >= 0)
    {
        for(;j>=0 && k>=0;j--,k--)
            nums1[k] = nums2[j];
    }
  */
  /*
    nums1 = [1,2,3,0,0,0], m = 3
    nums2 = [2,5,6],       n = 3

    nums[idx1]: 2
    nums[idx2]: 2

    nums1 = [1,2,2,3,5,6]

    idx = nums1Size + nums2Size - 1


    idx1 = nums1Size - 1;
    idx2 = nums2Size - 1;

    time: O(nums1Size + nums2Size)
    space: O(1)

    */

    int idx1, idx2, idx;

    idx = m + n - 1;
    idx1 = m - 1;
    idx2 = n - 1;

    while (idx1 >= 0 && idx2 >=0) {
        if (nums1[idx1] > nums2[idx2]) {
            nums1[idx] = nums1[idx1];
            idx1 -= 1;
            idx -= 1;
        } else {
            nums1[idx] = nums2[idx2];
            idx2 -= 1;
            idx -= 1;
        }
    }

    // rest numbers in nums2 are smaller
    while (idx2 >= 0) {
        nums1[idx] = nums2[idx2];
        idx2 -= 1;
        idx -= 1;
    }
}

int main () {

  int nums1[] = {1,2,3,0,0,0};
  int m = 3;
  int nums2[] = {2,5,6};
  int n = 3;

  int nums1Size = sizeof(nums1) / sizeof(nums1[0]);
  int nums2Size = sizeof(nums2) / sizeof(nums2[0]);
  merge(nums1, nums1Size, m, nums2, nums2Size, n);

  for (int i=0; i<6; i++) {
    printf ("[%s]--> %d \n",__func__, nums1[i]);
  }
}
