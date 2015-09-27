/* 
Program: : Count all distinct pairs with difference equal to k, by Intel
Input: arr[] = {1, 5, 3, 4, 2}, k = 3
Output: 2
There are 2 pairs with difference 3, the pairs are {1, 4} and {5, 2} 
Ref: http://www.geeksforgeeks.org/count-pairs-difference-equal-k/
*/
#include <stdio.h>
#include <string.h>

int main(void) {
    int arr[] = {1, 5, 3, 4, 2}; 
    int key = 3;
    int size = sizeof (arr) / sizeof (arr[0]);
    int ret = countPairsWithDiffK(arr, size, key);
    printf ("ret = %d \n", ret);
    ret = countPairsWithSumK (arr, size, key); 
    printf ("ret = %d \n", ret);
}

int countPairsWithDiffK(int arr[], int n, int k) {
    int count = 0;     
    // Pick all elements one by one
    for (int i = 0; i < n; i++) {       
        // See if there is a pair of this picked element
        for (int j = i+1; j < n; j++)
            if (arr[i] - arr[j] == k || arr[j] - arr[i] == k )
                  count++;
    }
    return count;
}

int countPairsWithSumK (int arr[], int size, int key) {
    int count = 0;
    for (int i=0; i<size; i++) {
        for (int j=i+1; j<size; j++)
            if ( (arr[i] + arr[j]) == key || (arr[j] + arr[i]) == key )
                count++;
    }
    return count;
}
