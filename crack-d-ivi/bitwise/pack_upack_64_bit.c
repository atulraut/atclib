/***
    BitWise: Packing Unpacking 64/32 bit data.
    Juniper Networks Questions :
    Date : 6/2/2020
    San Diego, CA
 */

/***
    Case I :
    How to store a 64 bit integer in two 32 bit integers and convert back again
*/
#include <stdio.h>
#include "../../at_lib.h"

void pack_unpack_64_32_bit() {

  /* Pack: 2, 32 bit into 1 64 bit */
  uint32_t x = 0xdead0000, y = 0xbeef0000;
  uint64_t z = ((uint64_t)x) << 32 | (uint64_t)y;

  printf("[%s] Pack 32 to 64 : 32x = 0x%x 32y = 0x%x 64z = 0x%lx \n", __func__, x, y, z);
  /* Unpack: u64 z = 0xdeadbeef; */
  x = (uint32_t)(z >> 32);
  y = (uint32_t)z;
  printf("[%s] Unpack 64 to 32 : 32x = 0x%x 32y = 0x%x 64z = 0x%lx \n", __func__, x, y, z);

}

/***
    Case I :
    Converting 32 bit unsigned in to 8 bit u int :
*/
void unpack_32_bit_into_8_bit() {

  uint32_t num32 = 0xdeadbeef;

  uint8_t a = num32;       /* 0xef */
  uint8_t b = num32 >> 8;  /* 0xbe */
  uint8_t c = num32 >> 16; /* 0xad */
  uint8_t d = num32 >> 24; /* 0xde */
  printf("\n[%s] Unpack 32 to 8: num32 = 0x%x a = 0x%x b = 0x%x c = 0x%x d = 0x%x \n", __func__, num32, a, b, c, d);
}

int main() {
  pack_unpack_64_32_bit();
  unpack_32_bit_into_8_bit();
}

/***
    > ./a.out
    [pack_unpack_64_32_bit] Pack 32 to 64 : 32x = 0xdead0000 32y = 0xbeef0000 64z = 0xdead0000beef0000
    [pack_unpack_64_32_bit] Unpack 64 to 32 : 32x = 0xdead0000 32y = 0xbeef0000 64z = 0xdead0000beef0000

    [unpack_32_bit_into_8_bit] Unpack 32 to 8: num32 = 0xdeadbeef a = 0xef b = 0xbe c = 0xad d = 0xde
*/
