/*
    Given an array nums of integers, return how many of them contain an even number of digits.
    Example 1:
    Input: nums = [12,345,2,6,7896]
    Output: 2
    Explanation:
    12 contains 2 digits (even number of digits).
    345 contains 3 digits (odd number of digits).
    2 contains 1 digit (odd number of digits).
    6 contains 1 digit (odd number of digits).
    7896 contains 4 digits (even number of digits).
    Therefore only 12 and 7896 contain an even number of digits.

    Example 2:
    Input: nums = [555,901,482,1771]
    Output: 1
    Explanation:
    Only 1771 contains an even number of digits.
*/
#include <stdio.h>

int findNumbers(int* nums, int numsSize){
    int i, temp;
    int cur=0, org = 0, arrayIndex = 0;
    int leetanswer = 0;
    for(i=0; i<numsSize; i++) {
        temp = nums[i];
        while (temp > 0) {
            temp /= 10;
            cur++;
        }
        printf ("->i= %d Cur=%d \t", i, cur);
        if(cur%2 == 0) {
            org = (cur > org) ? cur:org;
            arrayIndex = i;
            leetanswer++;
            printf ("->i=%d arrayIndex=%d \n", i, arrayIndex);
        }
        cur = 0;
    }
    return (leetanswer);
}

int main() {
    int ar[] = {1234,345,22222222,666,789};
    int res = findNumbers(ar, 5);
    printf("O/P = %d \n", res);

    return 0;
}
