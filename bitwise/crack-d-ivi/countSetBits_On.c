/*
  Mapping numbers with the bit. It simply maintains a Map(or array)
  of numbers to bits for a nibble. A Nibble contains 4bits. So we need an array up to 15.
  int num_to_bits[16] = {0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4};
  Now we just need to get nibbles of given long/int/word etc recuresively.
  Ref: https://www.geeksforgeeks.org/count-set-bits-in-an-integer/
*/
#include <stdio.h>

int num_to_bits[16] = { 0, 1, 1, 2, 1, 2, 2, 3,
                        1, 2, 2, 3, 2, 3, 3, 4 };

/* Recursively get nibble of a given number
and map them in the array */
unsigned int countSetBitsRec(unsigned int num) {
    int nibble = 0;
    if (0 == num)
        return num_to_bits[0];

    // Find last nibble
    nibble = num & 0xf;

    // Use pre-stored values to find count
    // in last nibble plus recursively add
    // remaining nibbles.
    printf ("--> nibble=%d  n2b = %d num=%d total=%d\n", nibble, (num_to_bits[nibble]), countSetBitsRec(num >> 4), (num_to_bits[nibble] + countSetBitsRec(num >> 4)));
    return num_to_bits[nibble] + countSetBitsRec(num >> 4);
}

int main() {
    int num = 31;
    printf("O/P--> %d\n", countSetBitsRec(num));
    return 0;
}
