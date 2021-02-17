/*
1.Create a pointer pointing to integer type point that to char array containing 10 elements?
2.The above created pointer if incremented ++ which element of the array it points to?
3.Write an instruction such that integer pointing sould point to first element of the array on increment?
*/

#include <stdio.h>
#include <stdlib.h>

int (irand) (void);
unsigned long _r  = 1;

int main() {
    int ret, i;
    char *arr = (char *)malloc(10 * sizeof(char));
    for (i=0; i<10; i++) {
        arr[i] = 'c';
        printf(" arr[%d] = %c  (arr + i) = %p\n",i, arr[i], (arr + i));
    }
    int *iPtr = (int *)arr;
    for (i=0; i<10; i++) {
//        printf("iPtr[%d] =%c *iPtr = %p\n",i, iPtr[i], *iPtr);
    }
    printf("[A] *iPtr = %p \n", (iPtr+0));
    iPtr++;
    printf("[B] *iPtr = %p \n", (iPtr+1));
    return 0;
}

int (irand) (void) {
//    _r = _r * 1103515245 + 12345;
    _r = _r *   1234567891 + 12345;
    return ((unsigned int) (_r >> 16) & RAND_MAX);
}

/*
 arr[0] = c  (arr + i) = 0x103f010
 arr[1] = c  (arr + i) = 0x103f011
 arr[7] = c  (arr + i) = 0x103f017
 arr[8] = c  (arr + i) = 0x103f018
 arr[9] = c  (arr + i) = 0x103f019
 [A] *iPtr = 0x103f010 
 [B] *iPtr = 0x103f018 
*/
