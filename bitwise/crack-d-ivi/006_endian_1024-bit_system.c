/***
    Big-Endian to Little-Endian Conversion on a 1024-bit System

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Mon Oct 12 09:53:09 PDT 2026
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
#include <inttypes.h>

#define debug(str,args...) printf("L=[%d][%s]->[%s] :| "str"\n",__LINE__,__FILE__, __func__, ##args)

#define SIZE 128   // 1024 bits / 8

void swap_endian(uint8_t *data, size_t n) {
    for (size_t i = 0; i < n / 2; i++) {
        uint8_t temp = data[i];
        data[i] = data[n - 1 - i];
        data[n - 1 - i] = temp;
    }
}

/**
   What if input comes from a 32-bit system?
 **/
uint32_t swap32(uint32_t x) {
    return ((x & 0x000000FFU) << 24) |
           ((x & 0x0000FF00U) <<  8) |
           ((x & 0x00FF0000U) >>  8) |
           ((x & 0xFF000000U) >> 24);
}

void test_1(void) {
    uint8_t data[SIZE];

    // Initialize 128 bytes
    for (int i = 0; i < SIZE; i++)
        data[i] = (uint8_t)i;

    swap_endian(data, SIZE);

    for (int i = 0; i < SIZE; i++)
        printf("->[%02X] ", data[i]);

    printf("\n");
}

/**
   This swaps the bytes of the 32-bit value.
   Whether you should call it during decoding depends on the
   receiver's native endianness.
**/
void test_2() {
  uint32_t x = 0x12345678;
  uint32_t y = swap32(x);
  debug("->[%u]", y);
}

int main (int argc, char **argv) {
  test_1();
  test_2();
  return 0;
}

/**
   atulraut@jinji -> ./a.out
   ->[7F] ->[7E] ->[7D] ->[7C] ->[7B] ->[7A] ->[79] ->[78] ->[77] ->[76] ->[75] ->[74] ->[73] ->[72] ->[71] ->[70] ->[6F] ->[6E] ->[6D] ->[6C] ->[6B] ->[6A] ->[69] ->[68] ->[67]   ->[66] ->[65] ->[64] ->[63] ->[62] ->[61] ->[60] ->[5F] ->[5E] ->[5D] ->[5C] ->[5B] ->[5A] ->[59] ->[58] ->[57] ->[56] ->[55] ->[54] ->[53] ->[52] ->[51] ->[50] ->[4F]
   ->[4E] ->[4D] ->[4C] ->[4B] ->[4A] ->[49] ->[48] ->[47] ->[46] ->[45] ->[44] ->[43] ->[42] ->[41] ->[40] ->[3F] ->[3E] ->[3D] ->[3C] ->[3B] ->[3A] ->[39] ->[38] ->[37] ->[36]    ->[35] ->[34] ->[33] ->[32] ->[31] ->[30] ->[2F] ->[2E] ->[2D] ->[2C] ->[2B] ->[2A] ->[29] ->[28] ->[27] ->[26] ->[25] ->[24] ->[23] ->[22] ->[21] ->[20] ->[1F] ->[1E] ->[1D]   ->[1C] ->[1B] ->[1A] ->[19] ->[18] ->[17] ->[16] ->[15] ->[14] ->[13] ->[12] ->[11] ->[10] ->[0F] ->[0E] ->[0D] ->[0C] ->[0B] ->[0A] ->[09] ->[08] ->[07] ->[06] ->[05] ->[04]    ->[03] ->[02] ->[01] ->[00]
**/
