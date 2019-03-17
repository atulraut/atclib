/*
	Write a program to swap odd and even bits in an integer with as few instructions as
	possible (e.g., bit 0 and bit 1 are swapped, bit 2 and bit 3 are swapped, etc).
*/
#include <stdio.h>
#include <stdlib.h>

/*
	SOLUTION
	Mask all odd bits with 10101010 in binary (which is 0xAA), then shift them left to put them in
	the even bits. Then, perform a similar operation for even bits. This takes a total 5 instructions.
*/	
	
int swapOddEvenBits(int x) {
    unsigned char odd_bits = x & 0xAA;	/* Get all Odd bits of X  */
    unsigned char even_bits = x & 0x55;	/* Get all Even bits of X */
    printf ("--> odd %d \n", odd_bits);
    printf ("--> even %d \n", even_bits);
    odd_bits >>= 1;
    even_bits <<= 1;
		
    printf ("--> odd %d \n", odd_bits);
    printf ("--> even %d \n", even_bits);

	return ( ((x & 0xaaaaaaaa) >> 1) | ((x & 0x55555555) << 1) );
}



unsigned char swapOddEvenBits2(unsigned char num)
{
    unsigned char odd_bits = num & 0xAA;	/* Get all Odd bits of X  */
    unsigned char even_bits = num & 0x55;	/* Get all Even bits of X */

    odd_bits >>= 1;
    even_bits <<= 1;

    return (odd_bits | even_bits);
}

int main() {
	int ret = 0;
	ret = swapOddEvenBits(6);
	printf ("--> %d \n", ret);
}

/*
Output => ./a.out 
--> odd 2 
--> even 4 
--> odd 1 
--> even 8 
--> 9 
*/
