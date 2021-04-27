/*
 * Implement a function rotateArray(vector<int> arr, int r) which rotates the array by r places.
 *  Eg 1 2 3 4 5 on being rotated by 2 gives 4 5 1 2 3.
 * Program of square root sqrt or power of two.
 * San Diego
 * Date : 11 March 2017
*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>
#include <string.h>  /* malloc */
#include <stdbool.h>
#include <math.h>
#include <assert.h>
#include <stdint.h> /* uint32_t */
#include <unistd.h> /* sleep */

#define debug(str,args...) printf("[%s] L=%d :"str"\n", __func__, __LINE__, ##args)

void rotateArray(int *, int, int);
void reverseArr(int *, int, int);
void reverseArray (int *, int, int);

int atclib_sqrt(num, power) {
  printf ("ATUL = %d, pwr = %d\n",num, power);
    if(power==0) return 1;
    if(power==1) return num;
    return( num * atclib_sqrt(num, power-1) );
}

void rotateArray(int *in, int arrsz, int rotate) {
    reverseArr(in, 0, arrsz-1);
    reverseArr(in, 0, rotate-1);
    reverseArr(in, rotate, arrsz-1);
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

/* using recursion */
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

void swap(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

// 26 April 2021, San Diego, CA.
void reverse_Intel(int *a, int n) {
    if (n <= 0)
      return;
    debug("n = %d a[0]=%d a[%d-1]=%d", n, a[0], n, a[n-1]);
    swap(&a[0], &a[n-1]);
    reverse_Intel(++a, n-2);
}

int main() {
    int i;
    int arr[5] = {1, 2, 3, 4, 5};
    int sz = sizeof(arr)/sizeof(arr[0]);
    /*O/P: 4 5 1 2 3. */
    int ret;
    //rotateArray(arr, sz, 3);

    reverse_Intel(arr, sz);
    ret = atclib_sqrt(2, 2);
    printf("ret = %d !\n", ret);
    printf("ANS = %d !\n", sz);
    for (i=0; i<5; i++) {
        printf ("-->[%d]\t", arr[i]);
    }
    printf ("\n");
    return 0;
}

/***
    => ./a.out
    [reverse_Intel] L=69 :n = 5 a[0]=1 a[5-1]=5
    [reverse_Intel] L=69 :n = 3 a[0]=2 a[3-1]=4
    [reverse_Intel] L=69 :n = 1 a[0]=3 a[1-1]=3
    ATUL = 2, pwr = 2
    ATUL = 2, pwr = 1
    ret = 4 !
    ANS = 5 !
    -->[5]	-->[4]	-->[3]	-->[2]	-->[1]
*/
