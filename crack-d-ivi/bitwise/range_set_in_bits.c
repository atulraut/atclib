/*
You are given two 32-bit numbers, N and M, and two bit positions, i and j. Write a
method to set all bits between i and j in N equal to M (e.g., M becomes a substring of
N located at i and starting at j).
EXAMPLE:
Input: N = 10000000000, M = 10101, i = 2, j = 6
Output: N = 10001010100
*/	
#include <stdio.h>
#include <stdlib.h>

int range_set_bits(int n, int m, int i, int j) {	
	int max = ~0; /* All 1’s */
	// 1’s through position j, then 0’s
	int left = max - ((1 << j) - 1);
	// 1’s after position i
	int right = ((1 << i) - 1);
	// 1’s, with 0s between i and j
	int mask = left | right;
	// Clear i through j, then put m in there
	return (n & mask) | (m << i);
}

int main() {
	int ret = 0;
	ret = range_set_bits(8, 21, 2, 6);
	printf ("--> %d \n", ret);
}
