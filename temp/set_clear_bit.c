/*
* Author  : Atul Raut
* Date    : 21 September 2015,2017
* Place   : San Diego
*/
#include <stdio.h>
#include <stdlib.h>
#include<math.h>

int setBit (int n, int k);
int clearBit (int n, int k);
int toggleBit (int n, int k);
unsigned int getFirstSetBitPos(int n);

int main() {

    printf("setBit   = %d \n", setBit (9, 5) );
    printf("clearBit = %d \n", clearBit (12, 4) );
    printf("toggleBit = %d \n", toggleBit (9, 5) );
 
    printf("getFirstSetBitPos = %u \n\n", getFirstSetBitPos(18)); // O/P = 2 
    return 0;
}

/* This will set k'th bit in n */
int setBit (int n, int k) {
    if (k<=0)
        return 0;
    return (n | (1<<(k-1)));
}

/* This will clear k'th bit in n */
int clearBit (int n, int k) {
    if (k<=0)
        return 0;
    return (n & ~(1<<(k-1)));
}

/* This will toggle k'th bit in n */
int toggleBit (int n, int k) {
    if (k<=0)
        return 0;
    return (n ^ (1<<(k-1)));
} 

/*
 * Write a one line C function to return position of first 1 from right to left, 
 * in binary representation of an Integer.
 */
unsigned int getFirstSetBitPos(int n)
{
   return log2(n&-n)+1;
}
 
