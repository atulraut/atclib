/*
 * Implement a function rotateArray(vector<int> arr, int r) which rotates the array by r places. 
 *  Eg 1 2 3 4 5 on being rotated by 2 gives 4 5 1 2 3.
 * San Diego
 * Date : 11 March 2017
*/
#include <stdio.h>

void rotateArray(int *, int, int);
void reverseArr(int *, int, int);
void reverseArray (int *, int, int);

int main() {
    int i;
    int arr[5] = {1, 2, 3, 4, 5};
    int sz = sizeof(arr)/sizeof(arr[0]);
    /*O/P: 4 5 1 2 3. */
    int ret;
    rotateArray(arr, sz, 3);
//    int ret = pwr(2, 2);
    printf("ANS = %d !\n", sz);
    for (i=0; i<5; i++) {
        printf ("-->[%d]\t", arr[i]);
    }
    printf ("\n");
    return 0;
}

int pwr(num, power) { 
    if(power==0) return 1; 
    if(power==1) return num; 
    return( num * raise(num, power-1) ); 
}

void rotateArray(int *in, int arrsz, int rotate){ 
    int i =0, j = arrsz-1;; 
    reverseArr(in, i, j); 
    reverseArr(in, 0, rotate-1); 
    reverseArr(in, rotate, j); 
} 

void reverseArr(int *in, int arrsz, int rotate) { 
    int i =arrsz,j = rotate; 
    while (i <= j) { 
        int tmp = in[i]; 
        in[i] = in[j]; 
        in[j] = tmp; 
        i++; j--; 
    } 
}
