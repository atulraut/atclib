/***
    https://www.sanfoundry.com/c-program-implement-bit-array/

    The C programming language does not provide support for array of bits.
    SetBit(A, k): set the kth bit in the bit array A:

    Step-by-step:
      int i = k/32;            // i = array index (use: A[i])
      int pos = k%32;          // pos = bit position in A[i]
      unsigned int flag = 1;   // flag = 0000.....00001
      flag = flag << pos;      // flag = 0000...010...000   (shifted k positions)
      A[i] = A[i] | flag;      // Set the bit at the k-th position in A[i]

      Date : 15 March 2021
      San Diego, CA
*/

#include <stdio.h>
#define debug(str,args...) printf("[%s] L=%d :"str"\n", __func__, __LINE__, ##args)

#define SIZE (58) /* amount of bits */
#define ARRAY_SIZE(x) (x/8+(!!(x%8)))

void toggle_bit(char *array, int index) {
  array[index / 8] ^= 1 << (index % 8);
}

char get_bit(char *array, int index) {
  return 1 & (array[index / 8] >> (index % 8));

}

int main(void) {
  /* initialize empty array with the right size */
  char x[ARRAY_SIZE(SIZE)] = { 0 };
  int i;

  for (i = 0; i < SIZE; i += 2)
    toggle_bit(x, i);

  toggle_bit(x, 56);

  for (i = 0; i < SIZE; i++)
    printf("%d: %d\n", i, get_bit(x, i));

  return 0;
}

/**
   => ./a.out
   0: 1
   1: 0
   2: 1
   3: 0
   4: 1
   5: 0
   6: 1
   7: 0
   8: 1
   9: 0
   10: 1
   11: 0
   12: 1
   13: 0
   14: 1
   15: 0
   16: 1
   17: 0
   18: 1
   19: 0
   20: 1
   21: 0
   22: 1
   23: 0
   24: 1
   25: 0
   26: 1
   27: 0
   28: 1
   29: 0
   30: 1
   31: 0
   32: 1
   33: 0
   34: 1
   35: 0
   36: 1
   37: 0
   38: 1
   39: 0
   40: 1
   41: 0
   42: 1
   43: 0
   44: 1
   45: 0
   46: 1
   47: 0
   48: 1
   49: 0
   50: 1
   51: 0
   52: 1
   53: 0
   54: 1
   55: 0
   56: 0
   57: 0
**/
