/***
    Ref: https://www.cs.emory.edu/~cheung/Courses/255/Syllabus/1-C-intro/Progs/bit-array2.c
    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Sat Sep 19 17:42:19 PDT 2026
    Folsom, CA.
 */

/*----------------------------------- Header --------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h> // va_arg
#include <ctype.h>
#include <limits.h>
#include <string.h>  /* malloc */
#include <stdbool.h>
#include <math.h>
#include <assert.h>
#include <stdint.h> /* uint32_t */
#include <unistd.h> /* sleep */

#define debug(str,args...) printf("L=[%d][%s]->[%s] :| "str"\n",__LINE__,__FILE__, __func__, ##args)

#define SetBit(A,k)     ( A[(k/32)] |= (1 << (k%32)) )
#define ClearBit(A,k)   ( A[(k/32)] &= ~(1 << (k%32)) )
#define TestBit(A,k)    ( A[(k/32)] & (1 << (k%32)) )

void test() {

  int A[10];
  int i;

  for ( i = 0; i < 10; i++ )
    A[i] = 0;                    // Clear the bit array

  printf("Set bit poistions 100, 200 and 300\n");
  SetBit( A, 100 );               // Set 3 bits
  SetBit( A, 200 );
  SetBit( A, 300 );


  // Check if SetBit() works:

  for ( i = 0; i < 320; i++ )
    if ( TestBit(A, i) )
      printf("Bit %d was set !\n", i);

  printf("\nClear bit poistions 200 \n");
  ClearBit( A, 200 );

  // Check if ClearBit() works:

  for ( i = 0; i < 320; i++ )
    if ( TestBit(A, i) )
      printf("Bit %d was set !\n", i);
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**
   Set bit poistions 100, 200 and 300
   Bit 100 was set !
   Bit 200 was set !
   Bit 300 was set !

   Clear bit poistions 200
   Bit 100 was set !
   Bit 300 was set !
**/
