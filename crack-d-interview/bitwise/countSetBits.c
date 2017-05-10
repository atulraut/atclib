/*
Implementation of Brian Kernighan’s Algorithm:
   1  Initialize count: = 0
   2  If integer n is not zero
      (a) Do bitwise & with (n-1) and assign the value back to n
          n = n&(n-1)
      (b) Increment count by 1
      (c) go to step 2
   3  Else return count
   Ref : http://www.geeksforgeeks.org/count-set-bits-in-an-integer/
 */
#include<stdio.h>

/*
 Ref: http://graphics.stanford.edu/~seander/bithacks.html#CountBitsSetKernighan
 Brian Kernighan's method goes through as many iterations as there are set bits. 
 So if we have a 32-bit word with only the high bit set, then it will only go once through the loop.
 if v = 5 - 4 2 1
            1 0 1 - 2 bits are set
*/
int getcnt () {
    unsigned int v = 5; // count the number of bits set in v
    unsigned int c = 0; // c accumulates the total bits set in v
    for (c = 0; v; c++) {
      v = v & (v - 1); // clear the least significant bit set
    }
    printf ("\n cnt v= %d c = %d \n", v, c);
}

/* Function to get no of set bits in binary
   representation of passed binary no. */
int countSetBits(int n)
{
    unsigned int count = 0;
    while (n) {
      n &= (n-1);
      count++;
    }
    return count;
}

/* Program to test function countSetBits */
int main() {
    int i = 3;
    printf("count = %d \n", countSetBits(i));
    getchar();
    return 0;
}
