/***
    Implement merging two u8int_t variable into u32int_t.

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Sun Jul  2 09:33:51 AM PDT 2023
    Folsom, CA.
 */

/*----------------------------------- Header --------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>
#include <string.h>  /* malloc */
#include <stdbool.h>
#include <math.h>
#include <assert.h>
#include <stdint.h> /* uint32_t */
#include <unistd.h> /* sleep */

/*----------------------------------- Micro --------------------------------------*/
#define debug(str,args...) printf("[%s] L=%d :"str"\n", __func__, __LINE__, ##args)

// Pack
void mergeBits(uint32_t* ret, uint8_t var1, uint8_t var2, uint8_t var3, uint8_t var4) {
  // Pack

  *ret |=  (var1 << 0);
  debug ("[UNPack]-> %d ", (*ret >> 0) );
  *ret |=  (var2 << 8);
  debug ("[UNPack]-> %d ", (*ret >> 8) );
  *ret |=  (var3 << 16);
  debug ("[UNPack]-> %d ", (*ret >> 16) );
  *ret |=  (var4 << 24);
  debug ("[UNPack]-> %d ", (*ret >> 24) );

  debug ("[UNPack]-> %d %d %d %d", ((*ret >> 0)& 0xFF), ((*ret >> 8)& 0xFF), ((*ret >> 16)& 0xFF), ((*ret >> 24) & 0xFF) );
  //debug ("[UNPack]-> %d %d %d %d", (*ret << 24), (*ret << 16), (*ret << 8), (*ret << 0) );
}


//Unpack
int send_msg() {
  uint8_t var1 = 5;
  uint8_t var2 = 6;
  uint8_t var3 = 7;
  uint8_t var4 = 8;
  uint32_t* ret = (uint32_t *)malloc(sizeof(uint32_t) * 32);
  *ret = 0;

  mergeBits(ret, var1, var2, var3, var4);
  // UNpack
  //*ret |= (*ret >> 24) | (*ret >> 16) |  (*ret >> 8) | (*ret >> 0) ;
  debug ("[UNPack]-> %d ", (*ret >> 24) & 0xFF);
  debug ("[UNPack]-> %d ", (*ret >> 16) & 0xFF);
  debug ("[UNPack]-> %d ", (*ret >> 8) & 0xFF);
  debug ("[UNPack]-> %d ", (*ret >> 0) & 0xFF);

}

void test() {
  int ret = 0;
  send_msg();
}

int main (int argc, char **argv) {
  test();
  return 0;
}
