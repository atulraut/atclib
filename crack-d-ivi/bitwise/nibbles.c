/*
  How to swap the two nibbles in a byte ?
  nibbles : It means half byte, or 4 bits.
  Logic explain : http://www.geeksforgeeks.org/swap-two-nibbles-byte/
*/
#include <stdio.h>

#define HI_NIBBLE(b) (((b) >> 4) & 0x0F)
#define LO_NIBBLE(b) ((b) & 0x0F)

unsigned char swapNibbles(unsigned char x) {
  return ( (x & 0x0F)<<4 | (x & 0xF0)>>4 );
}
 
unsigned char swap_nibbles(unsigned char c) {
	unsigned char temp1, temp2;
	unsigned char x = 100;

	//	c = x;
	temp1 = c & 0x0F; /* 0x0F == 15 */
	temp2 = c & 0xF0; /* 0xF0 == 240*/
	//	printf ("[1]c = %d t1 = %x t2 = %x \n",c, temp1, temp2);
	printf ("[1]c = %d t1 = %u t2 = %u \n",c, temp1, temp2);
	temp1=temp1 << 4;
	temp2=temp2 >> 4;	
	printf ("[2] t1 = %u t2 = %u \n", temp1, temp2);
	printf ("[3] t1|t2 = %x u=%u \n", (temp1|temp2), (temp1|temp2));
	return(temp2|temp1); //adding the bits
}

int main(void) {
	char ch=0x34;
	unsigned char x = 100;
	printf("\n ATUL --> [%u] \n", swap_nibbles(x));
//	printf("\nThe exchanged value is %x",swap_nibbles(x));
	return 0;
}
