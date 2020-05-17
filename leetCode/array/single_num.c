/*
Given a non-empty array of integers, every element appears twice except
for one. Find that single one.
Note:
Your algorithm should have a linear runtime complexity. Could you implement
it without using extra memory?
Example 1:
Input: [2,2,1]
Output: 1
Example 2:

Input: [4,1,2,1,2]
Output: 4

XOR: with same number gives zeros.
NPUT OUTPUT
A B A XOR B
0 0   0
0 1   1
1 0   1
1 1   0
Youtube: https://www.youtube.com/watch?v=krgK0UlfNYY
------------------------------
*/

#include <stdio.h>

int singleNumber(int* nums, int numsSize){
        int i=0;
        int results = 0;

        for(i=0; i<numsSize; i++) {
                results ^=  nums[i];
        }
        return results;
}
int main() {
        int arr[] = {4, 1, 2, 1, 2};
        int sz = sizeof(arr) / sizeof(arr[0]);

        printf ("[%s] o/p = %d \n",__func__, singleNumber(arr, sz));
}
