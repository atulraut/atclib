/***
    http://www.mathcs.emory.edu/~cheung/Courses/255/Syllabus/1-C-intro/bit-array.html

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
/* ========================================
   Bit Operations as macros
   ======================================== */
/***
        Implement bit Array in C.
	http://www.mathcs.emory.edu/~cheung/Courses/255/Syllabus/1-C-intro/bit-array.html
	            --
	5 % 32 == 32)5
 */
#include <stdio.h>
#define debug(str,args...) printf("[%s] L=%d :"str"\n", __func__, __LINE__, ##args)

//SCT - OAX
#define setBit(A,k)     ( A[(k/32)] |= (1 << (k%32)) )
#define clearBit(A,k)   ( A[(k/32)] &= ~(1 << (k%32)) )
#define toggleBit(A,k)  ( A[(k/32)] ^= (1 << (k%32)) )

#define testBit(A,k)    ( A[(k/32)] & (1 << (k%32)) )

void int_set_bit_array () {
  int A[10];
  int i;

  debug ("Size of Array = %ld", (sizeof(A)/sizeof(A[0])) );
  /***
    Size of Array = 10
    10 * 4 (Int is 4 Bytes in Size) = 40
    40 * 8 (1 Byte == 8 Bit) = 320 Bits
  */
  for ( i = 0; i < 10; i++ )
    A[i] = 0;                    // Clear the bit array

  debug("Set bit poistions 100, 200 and 300");
  setBit( A, 100 );               // Set 3 bits
  setBit( A, 200 );
  setBit( A, 300 );

  /* Test Code //
  for (i=0; i< 101; i++)
    debug ("[AR] [%d]/32=%d [%d]mod32=%d", i, i/32, i, i%32);
  return;
  */

  // Check if SetBit() works:
  for ( i = 0; i < 320; i++ )
    if ( testBit(A, i) )
      debug("Bit %d was set !", i);

  debug("\nClear bit poistions 200 ");
  clearBit( A, 200 );

  // Check if ClearBit() works:

  for ( i = 0; i < 320; i++ )
    if ( testBit(A, i) )
      debug("Bit %d was set !", i);

  for ( i = 0; i < 320; i++ )
    debug("Bit %d  set to = %d", i, testBit(A, i));
}

void char_set_bit () {
  int i;
  char c = 0;
  char *cc = &c;

  for (i=0; i<8; i++) {
    setBit (cc, i);
  }

   for ( i = 0; i < 8; i++ )
    debug("Bit %d  set to = %d", i, testBit(cc, i));
}

void char_array() {

  char arr[257] = {0};

  for (int i=0; i<257; i++)
    debug ("arr[%d] = %d", i, arr[i]);
}

int main( int argc, char* argv[] ) {
  int_set_bit_array ();
  //char_set_bit();

  //char_array();
}
