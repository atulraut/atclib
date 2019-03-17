/*
	Write a function to determine the number of bits required to convert integer A to
	integer B.
	Input: 31, 14
	Output: 2
*/
#include <stdio.h>
#include <stdlib.h>

/* SOLUTION
	This seemingly complex problem is actually rather straightforward. To approach this, ask
	yourself how you would figure out which bits in two numbers are different. Simple: with an
	xor.
	Each 1 in the xor will represent one different bit between A and B. We then simply need to
	count the number of bits that are 1.
*/
	
int bitSwapRequired(int a, int b) {	
	int count = 0;		
	for (int c = a ^ b; c != 0; c = c >> 1) {
		printf ("--> c %d \n", c);		
		count += c & 1;
		printf ("--> cnt=%d (c&1) = %d \n", count, (c&1));
	
	}	
	return count;
}

int main() {
	int ret = 0;
	ret = bitSwapRequired(31, 14);
	printf ("--> %d \n", ret);
}

/*
4  3 2 1 0	
16 8 4 2 1
1  1 1 1 1 - 31
     1 1 1 - 14
---------------
           - Diff is 2 Hence ans is 2.
*/
