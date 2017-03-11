/*
 * Reverse an array without using iteration. 
 * San Diego
 * Date : 11 March 2017
*/
#include <stdio.h>

void reverseArray (int *arr, int fst, int sz);

int main() {
    int i = 0, fst=0, sz=0;
    int arr[5] = {5,4,3,2,1};
    sz = sizeof(arr)/sizeof(arr[0]);
    for (i=0; i<5; i++) {
        printf("->[%d]", arr[i] );
    }
    printf("\n");
    reverseArray (arr, fst, sz);
    for (i=0; i<5; i++) {
        printf("->[%d]", arr[i] );
    }
    printf("\n");
    return 0;
}

void reverseArray (int *arr, int fst, int sz) {
    int temp = 0;
    printf ("arr[%d], arr[%d] \n", arr[fst], arr[sz]);
    if (fst > sz)
        return;
    temp = arr[fst];
    arr[fst] = arr[sz-1];
    arr[sz-1] = temp;
    reverseArray (arr, ++fst, --sz);
}
