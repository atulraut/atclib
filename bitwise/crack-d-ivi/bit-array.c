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
  debug ("arr[%d] =%d", (100/32), A[(100/32)]);
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


/**
   => ./a.out 
   [int_set_bit_array] L=41 :Size of Array = 10
   [int_set_bit_array] L=50 :Set bit poistions 100, 200 and 300
   [int_set_bit_array] L=52 :arr[3] =16
   [int_set_bit_array] L=65 :Bit 100 was set !
   [int_set_bit_array] L=65 :Bit 200 was set !
   [int_set_bit_array] L=65 :Bit 300 was set !
   [int_set_bit_array] L=67 :
   Clear bit poistions 200 
   [int_set_bit_array] L=74 :Bit 100 was set !
   [int_set_bit_array] L=74 :Bit 300 was set !
   [int_set_bit_array] L=77 :Bit 0  set to = 0
   [int_set_bit_array] L=77 :Bit 1  set to = 0
   [int_set_bit_array] L=77 :Bit 2  set to = 0
   [int_set_bit_array] L=77 :Bit 3  set to = 0
   [int_set_bit_array] L=77 :Bit 4  set to = 0
   [int_set_bit_array] L=77 :Bit 5  set to = 0
   [int_set_bit_array] L=77 :Bit 6  set to = 0
   [int_set_bit_array] L=77 :Bit 7  set to = 0
   [int_set_bit_array] L=77 :Bit 8  set to = 0
   [int_set_bit_array] L=77 :Bit 9  set to = 0
   [int_set_bit_array] L=77 :Bit 10  set to = 0
   [int_set_bit_array] L=77 :Bit 11  set to = 0
   [int_set_bit_array] L=77 :Bit 12  set to = 0
   [int_set_bit_array] L=77 :Bit 13  set to = 0
   [int_set_bit_array] L=77 :Bit 14  set to = 0
   [int_set_bit_array] L=77 :Bit 15  set to = 0
   [int_set_bit_array] L=77 :Bit 16  set to = 0
   [int_set_bit_array] L=77 :Bit 17  set to = 0
   [int_set_bit_array] L=77 :Bit 18  set to = 0
   [int_set_bit_array] L=77 :Bit 19  set to = 0
   [int_set_bit_array] L=77 :Bit 20  set to = 0
   [int_set_bit_array] L=77 :Bit 21  set to = 0
   [int_set_bit_array] L=77 :Bit 22  set to = 0
   [int_set_bit_array] L=77 :Bit 23  set to = 0
   [int_set_bit_array] L=77 :Bit 24  set to = 0
   [int_set_bit_array] L=77 :Bit 25  set to = 0
   [int_set_bit_array] L=77 :Bit 26  set to = 0
   [int_set_bit_array] L=77 :Bit 27  set to = 0
   [int_set_bit_array] L=77 :Bit 28  set to = 0
   [int_set_bit_array] L=77 :Bit 29  set to = 0
   [int_set_bit_array] L=77 :Bit 30  set to = 0
   [int_set_bit_array] L=77 :Bit 31  set to = 0
   [int_set_bit_array] L=77 :Bit 32  set to = 0
   [int_set_bit_array] L=77 :Bit 33  set to = 0
   [int_set_bit_array] L=77 :Bit 34  set to = 0
   [int_set_bit_array] L=77 :Bit 35  set to = 0
   [int_set_bit_array] L=77 :Bit 36  set to = 0
   [int_set_bit_array] L=77 :Bit 37  set to = 0
   [int_set_bit_array] L=77 :Bit 38  set to = 0
   [int_set_bit_array] L=77 :Bit 39  set to = 0
   [int_set_bit_array] L=77 :Bit 40  set to = 0
   [int_set_bit_array] L=77 :Bit 41  set to = 0
   [int_set_bit_array] L=77 :Bit 42  set to = 0
   [int_set_bit_array] L=77 :Bit 43  set to = 0
   [int_set_bit_array] L=77 :Bit 44  set to = 0
   [int_set_bit_array] L=77 :Bit 45  set to = 0
   [int_set_bit_array] L=77 :Bit 46  set to = 0
   [int_set_bit_array] L=77 :Bit 47  set to = 0
   [int_set_bit_array] L=77 :Bit 48  set to = 0
   [int_set_bit_array] L=77 :Bit 49  set to = 0
   [int_set_bit_array] L=77 :Bit 50  set to = 0
   [int_set_bit_array] L=77 :Bit 51  set to = 0
   [int_set_bit_array] L=77 :Bit 52  set to = 0
   [int_set_bit_array] L=77 :Bit 53  set to = 0
   [int_set_bit_array] L=77 :Bit 54  set to = 0
   [int_set_bit_array] L=77 :Bit 55  set to = 0
   [int_set_bit_array] L=77 :Bit 56  set to = 0
   [int_set_bit_array] L=77 :Bit 57  set to = 0
   [int_set_bit_array] L=77 :Bit 58  set to = 0
   [int_set_bit_array] L=77 :Bit 59  set to = 0
   [int_set_bit_array] L=77 :Bit 60  set to = 0
   [int_set_bit_array] L=77 :Bit 61  set to = 0
   [int_set_bit_array] L=77 :Bit 62  set to = 0
   [int_set_bit_array] L=77 :Bit 63  set to = 0
   [int_set_bit_array] L=77 :Bit 64  set to = 0
   [int_set_bit_array] L=77 :Bit 65  set to = 0
   [int_set_bit_array] L=77 :Bit 66  set to = 0
   [int_set_bit_array] L=77 :Bit 67  set to = 0
   [int_set_bit_array] L=77 :Bit 68  set to = 0
   [int_set_bit_array] L=77 :Bit 69  set to = 0
   [int_set_bit_array] L=77 :Bit 70  set to = 0
   [int_set_bit_array] L=77 :Bit 71  set to = 0
   [int_set_bit_array] L=77 :Bit 72  set to = 0
   [int_set_bit_array] L=77 :Bit 73  set to = 0
   [int_set_bit_array] L=77 :Bit 74  set to = 0
   [int_set_bit_array] L=77 :Bit 75  set to = 0
   [int_set_bit_array] L=77 :Bit 76  set to = 0
   [int_set_bit_array] L=77 :Bit 77  set to = 0
   [int_set_bit_array] L=77 :Bit 78  set to = 0
   [int_set_bit_array] L=77 :Bit 79  set to = 0
   [int_set_bit_array] L=77 :Bit 80  set to = 0
   [int_set_bit_array] L=77 :Bit 81  set to = 0
   [int_set_bit_array] L=77 :Bit 82  set to = 0
   [int_set_bit_array] L=77 :Bit 83  set to = 0
   [int_set_bit_array] L=77 :Bit 84  set to = 0
   [int_set_bit_array] L=77 :Bit 85  set to = 0
   [int_set_bit_array] L=77 :Bit 86  set to = 0
   [int_set_bit_array] L=77 :Bit 87  set to = 0
   [int_set_bit_array] L=77 :Bit 88  set to = 0
   [int_set_bit_array] L=77 :Bit 89  set to = 0
   [int_set_bit_array] L=77 :Bit 90  set to = 0
   [int_set_bit_array] L=77 :Bit 91  set to = 0
   [int_set_bit_array] L=77 :Bit 92  set to = 0
   [int_set_bit_array] L=77 :Bit 93  set to = 0
   [int_set_bit_array] L=77 :Bit 94  set to = 0
   [int_set_bit_array] L=77 :Bit 95  set to = 0
   [int_set_bit_array] L=77 :Bit 96  set to = 0
   [int_set_bit_array] L=77 :Bit 97  set to = 0
   [int_set_bit_array] L=77 :Bit 98  set to = 0
   [int_set_bit_array] L=77 :Bit 99  set to = 0
   [int_set_bit_array] L=77 :Bit 100  set to = 16
   [int_set_bit_array] L=77 :Bit 101  set to = 0
   [int_set_bit_array] L=77 :Bit 102  set to = 0
   [int_set_bit_array] L=77 :Bit 103  set to = 0
   [int_set_bit_array] L=77 :Bit 104  set to = 0
   [int_set_bit_array] L=77 :Bit 105  set to = 0
   [int_set_bit_array] L=77 :Bit 106  set to = 0
   [int_set_bit_array] L=77 :Bit 107  set to = 0
   [int_set_bit_array] L=77 :Bit 108  set to = 0
   [int_set_bit_array] L=77 :Bit 109  set to = 0
   [int_set_bit_array] L=77 :Bit 110  set to = 0
   [int_set_bit_array] L=77 :Bit 111  set to = 0
   [int_set_bit_array] L=77 :Bit 112  set to = 0
   [int_set_bit_array] L=77 :Bit 113  set to = 0
   [int_set_bit_array] L=77 :Bit 114  set to = 0
   [int_set_bit_array] L=77 :Bit 115  set to = 0
   [int_set_bit_array] L=77 :Bit 116  set to = 0
   [int_set_bit_array] L=77 :Bit 117  set to = 0
   [int_set_bit_array] L=77 :Bit 118  set to = 0
   [int_set_bit_array] L=77 :Bit 119  set to = 0
   [int_set_bit_array] L=77 :Bit 120  set to = 0
   [int_set_bit_array] L=77 :Bit 121  set to = 0
   [int_set_bit_array] L=77 :Bit 122  set to = 0
   [int_set_bit_array] L=77 :Bit 123  set to = 0
   [int_set_bit_array] L=77 :Bit 124  set to = 0
   [int_set_bit_array] L=77 :Bit 125  set to = 0
   [int_set_bit_array] L=77 :Bit 126  set to = 0
   [int_set_bit_array] L=77 :Bit 127  set to = 0
   [int_set_bit_array] L=77 :Bit 128  set to = 0
   [int_set_bit_array] L=77 :Bit 129  set to = 0
   [int_set_bit_array] L=77 :Bit 130  set to = 0
   [int_set_bit_array] L=77 :Bit 131  set to = 0
   [int_set_bit_array] L=77 :Bit 132  set to = 0
   [int_set_bit_array] L=77 :Bit 133  set to = 0
   [int_set_bit_array] L=77 :Bit 134  set to = 0
   [int_set_bit_array] L=77 :Bit 135  set to = 0
   [int_set_bit_array] L=77 :Bit 136  set to = 0
   [int_set_bit_array] L=77 :Bit 137  set to = 0
   [int_set_bit_array] L=77 :Bit 138  set to = 0
   [int_set_bit_array] L=77 :Bit 139  set to = 0
   [int_set_bit_array] L=77 :Bit 140  set to = 0
   [int_set_bit_array] L=77 :Bit 141  set to = 0
   [int_set_bit_array] L=77 :Bit 142  set to = 0
   [int_set_bit_array] L=77 :Bit 143  set to = 0
   [int_set_bit_array] L=77 :Bit 144  set to = 0
   [int_set_bit_array] L=77 :Bit 145  set to = 0
   [int_set_bit_array] L=77 :Bit 146  set to = 0
   [int_set_bit_array] L=77 :Bit 147  set to = 0
   [int_set_bit_array] L=77 :Bit 148  set to = 0
   [int_set_bit_array] L=77 :Bit 149  set to = 0
   [int_set_bit_array] L=77 :Bit 150  set to = 0
   [int_set_bit_array] L=77 :Bit 151  set to = 0
   [int_set_bit_array] L=77 :Bit 152  set to = 0
   [int_set_bit_array] L=77 :Bit 153  set to = 0
   [int_set_bit_array] L=77 :Bit 154  set to = 0
   [int_set_bit_array] L=77 :Bit 155  set to = 0
   [int_set_bit_array] L=77 :Bit 156  set to = 0
   [int_set_bit_array] L=77 :Bit 157  set to = 0
   [int_set_bit_array] L=77 :Bit 158  set to = 0
   [int_set_bit_array] L=77 :Bit 159  set to = 0
   [int_set_bit_array] L=77 :Bit 160  set to = 0
   [int_set_bit_array] L=77 :Bit 161  set to = 0
   [int_set_bit_array] L=77 :Bit 162  set to = 0
   [int_set_bit_array] L=77 :Bit 163  set to = 0
   [int_set_bit_array] L=77 :Bit 164  set to = 0
   [int_set_bit_array] L=77 :Bit 165  set to = 0
   [int_set_bit_array] L=77 :Bit 166  set to = 0
   [int_set_bit_array] L=77 :Bit 167  set to = 0
   [int_set_bit_array] L=77 :Bit 168  set to = 0
   [int_set_bit_array] L=77 :Bit 169  set to = 0
   [int_set_bit_array] L=77 :Bit 170  set to = 0
   [int_set_bit_array] L=77 :Bit 171  set to = 0
   [int_set_bit_array] L=77 :Bit 172  set to = 0
   [int_set_bit_array] L=77 :Bit 173  set to = 0
   [int_set_bit_array] L=77 :Bit 174  set to = 0
   [int_set_bit_array] L=77 :Bit 175  set to = 0
   [int_set_bit_array] L=77 :Bit 176  set to = 0
   [int_set_bit_array] L=77 :Bit 177  set to = 0
   [int_set_bit_array] L=77 :Bit 178  set to = 0
   [int_set_bit_array] L=77 :Bit 179  set to = 0
   [int_set_bit_array] L=77 :Bit 180  set to = 0
   [int_set_bit_array] L=77 :Bit 181  set to = 0
   [int_set_bit_array] L=77 :Bit 182  set to = 0
   [int_set_bit_array] L=77 :Bit 183  set to = 0
   [int_set_bit_array] L=77 :Bit 184  set to = 0
   [int_set_bit_array] L=77 :Bit 185  set to = 0
   [int_set_bit_array] L=77 :Bit 186  set to = 0
   [int_set_bit_array] L=77 :Bit 187  set to = 0
   [int_set_bit_array] L=77 :Bit 188  set to = 0
   [int_set_bit_array] L=77 :Bit 189  set to = 0
   [int_set_bit_array] L=77 :Bit 190  set to = 0
   [int_set_bit_array] L=77 :Bit 191  set to = 0
   [int_set_bit_array] L=77 :Bit 192  set to = 0
   [int_set_bit_array] L=77 :Bit 193  set to = 0
   [int_set_bit_array] L=77 :Bit 194  set to = 0
   [int_set_bit_array] L=77 :Bit 195  set to = 0
   [int_set_bit_array] L=77 :Bit 196  set to = 0
   [int_set_bit_array] L=77 :Bit 197  set to = 0
   [int_set_bit_array] L=77 :Bit 198  set to = 0
   [int_set_bit_array] L=77 :Bit 199  set to = 0
   [int_set_bit_array] L=77 :Bit 200  set to = 0
   [int_set_bit_array] L=77 :Bit 201  set to = 0
   [int_set_bit_array] L=77 :Bit 202  set to = 0
   [int_set_bit_array] L=77 :Bit 203  set to = 0
   [int_set_bit_array] L=77 :Bit 204  set to = 0
   [int_set_bit_array] L=77 :Bit 205  set to = 0
   [int_set_bit_array] L=77 :Bit 206  set to = 0
   [int_set_bit_array] L=77 :Bit 207  set to = 0
   [int_set_bit_array] L=77 :Bit 208  set to = 0
   [int_set_bit_array] L=77 :Bit 209  set to = 0
   [int_set_bit_array] L=77 :Bit 210  set to = 0
   [int_set_bit_array] L=77 :Bit 211  set to = 0
   [int_set_bit_array] L=77 :Bit 212  set to = 0
   [int_set_bit_array] L=77 :Bit 213  set to = 0
   [int_set_bit_array] L=77 :Bit 214  set to = 0
   [int_set_bit_array] L=77 :Bit 215  set to = 0
   [int_set_bit_array] L=77 :Bit 216  set to = 0
   [int_set_bit_array] L=77 :Bit 217  set to = 0
   [int_set_bit_array] L=77 :Bit 218  set to = 0
   [int_set_bit_array] L=77 :Bit 219  set to = 0
   [int_set_bit_array] L=77 :Bit 220  set to = 0
   [int_set_bit_array] L=77 :Bit 221  set to = 0
   [int_set_bit_array] L=77 :Bit 222  set to = 0
   [int_set_bit_array] L=77 :Bit 223  set to = 0
   [int_set_bit_array] L=77 :Bit 224  set to = 0
   [int_set_bit_array] L=77 :Bit 225  set to = 0
   [int_set_bit_array] L=77 :Bit 226  set to = 0
   [int_set_bit_array] L=77 :Bit 227  set to = 0
   [int_set_bit_array] L=77 :Bit 228  set to = 0
   [int_set_bit_array] L=77 :Bit 229  set to = 0
   [int_set_bit_array] L=77 :Bit 230  set to = 0
   [int_set_bit_array] L=77 :Bit 231  set to = 0
   [int_set_bit_array] L=77 :Bit 232  set to = 0
   [int_set_bit_array] L=77 :Bit 233  set to = 0
   [int_set_bit_array] L=77 :Bit 234  set to = 0
   [int_set_bit_array] L=77 :Bit 235  set to = 0
   [int_set_bit_array] L=77 :Bit 236  set to = 0
   [int_set_bit_array] L=77 :Bit 237  set to = 0
   [int_set_bit_array] L=77 :Bit 238  set to = 0
   [int_set_bit_array] L=77 :Bit 239  set to = 0
   [int_set_bit_array] L=77 :Bit 240  set to = 0
   [int_set_bit_array] L=77 :Bit 241  set to = 0
   [int_set_bit_array] L=77 :Bit 242  set to = 0
   [int_set_bit_array] L=77 :Bit 243  set to = 0
   [int_set_bit_array] L=77 :Bit 244  set to = 0
   [int_set_bit_array] L=77 :Bit 245  set to = 0
   [int_set_bit_array] L=77 :Bit 246  set to = 0
   [int_set_bit_array] L=77 :Bit 247  set to = 0
   [int_set_bit_array] L=77 :Bit 248  set to = 0
   [int_set_bit_array] L=77 :Bit 249  set to = 0
   [int_set_bit_array] L=77 :Bit 250  set to = 0
   [int_set_bit_array] L=77 :Bit 251  set to = 0
   [int_set_bit_array] L=77 :Bit 252  set to = 0
   [int_set_bit_array] L=77 :Bit 253  set to = 0
   [int_set_bit_array] L=77 :Bit 254  set to = 0
   [int_set_bit_array] L=77 :Bit 255  set to = 0
   [int_set_bit_array] L=77 :Bit 256  set to = 0
   [int_set_bit_array] L=77 :Bit 257  set to = 0
   [int_set_bit_array] L=77 :Bit 258  set to = 0
   [int_set_bit_array] L=77 :Bit 259  set to = 0
   [int_set_bit_array] L=77 :Bit 260  set to = 0
   [int_set_bit_array] L=77 :Bit 261  set to = 0
   [int_set_bit_array] L=77 :Bit 262  set to = 0
   [int_set_bit_array] L=77 :Bit 263  set to = 0
   [int_set_bit_array] L=77 :Bit 264  set to = 0
   [int_set_bit_array] L=77 :Bit 265  set to = 0
   [int_set_bit_array] L=77 :Bit 266  set to = 0
   [int_set_bit_array] L=77 :Bit 267  set to = 0
   [int_set_bit_array] L=77 :Bit 268  set to = 0
   [int_set_bit_array] L=77 :Bit 269  set to = 0
   [int_set_bit_array] L=77 :Bit 270  set to = 0
   [int_set_bit_array] L=77 :Bit 271  set to = 0
   [int_set_bit_array] L=77 :Bit 272  set to = 0
   [int_set_bit_array] L=77 :Bit 273  set to = 0
   [int_set_bit_array] L=77 :Bit 274  set to = 0
   [int_set_bit_array] L=77 :Bit 275  set to = 0
   [int_set_bit_array] L=77 :Bit 276  set to = 0
   [int_set_bit_array] L=77 :Bit 277  set to = 0
   [int_set_bit_array] L=77 :Bit 278  set to = 0
   [int_set_bit_array] L=77 :Bit 279  set to = 0
   [int_set_bit_array] L=77 :Bit 280  set to = 0
   [int_set_bit_array] L=77 :Bit 281  set to = 0
   [int_set_bit_array] L=77 :Bit 282  set to = 0
   [int_set_bit_array] L=77 :Bit 283  set to = 0
   [int_set_bit_array] L=77 :Bit 284  set to = 0
   [int_set_bit_array] L=77 :Bit 285  set to = 0
   [int_set_bit_array] L=77 :Bit 286  set to = 0
   [int_set_bit_array] L=77 :Bit 287  set to = 0
   [int_set_bit_array] L=77 :Bit 288  set to = 0
   [int_set_bit_array] L=77 :Bit 289  set to = 0
   [int_set_bit_array] L=77 :Bit 290  set to = 0
   [int_set_bit_array] L=77 :Bit 291  set to = 0
   [int_set_bit_array] L=77 :Bit 292  set to = 0
   [int_set_bit_array] L=77 :Bit 293  set to = 0
   [int_set_bit_array] L=77 :Bit 294  set to = 0
   [int_set_bit_array] L=77 :Bit 295  set to = 0
   [int_set_bit_array] L=77 :Bit 296  set to = 0
   [int_set_bit_array] L=77 :Bit 297  set to = 0
   [int_set_bit_array] L=77 :Bit 298  set to = 0
   [int_set_bit_array] L=77 :Bit 299  set to = 0
   [int_set_bit_array] L=77 :Bit 300  set to = 4096
   [int_set_bit_array] L=77 :Bit 301  set to = 0
   [int_set_bit_array] L=77 :Bit 302  set to = 0
   [int_set_bit_array] L=77 :Bit 303  set to = 0
   [int_set_bit_array] L=77 :Bit 304  set to = 0
   [int_set_bit_array] L=77 :Bit 305  set to = 0
   [int_set_bit_array] L=77 :Bit 306  set to = 0
   [int_set_bit_array] L=77 :Bit 307  set to = 0
   [int_set_bit_array] L=77 :Bit 308  set to = 0
   [int_set_bit_array] L=77 :Bit 309  set to = 0
   [int_set_bit_array] L=77 :Bit 310  set to = 0
   [int_set_bit_array] L=77 :Bit 311  set to = 0
   [int_set_bit_array] L=77 :Bit 312  set to = 0
   [int_set_bit_array] L=77 :Bit 313  set to = 0
   [int_set_bit_array] L=77 :Bit 314  set to = 0
   [int_set_bit_array] L=77 :Bit 315  set to = 0
   [int_set_bit_array] L=77 :Bit 316  set to = 0
   [int_set_bit_array] L=77 :Bit 317  set to = 0
   [int_set_bit_array] L=77 :Bit 318  set to = 0
   [int_set_bit_array] L=77 :Bit 319  set to = 0
**/
