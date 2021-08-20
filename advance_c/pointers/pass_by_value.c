/***
    Pointers are passed by Value.
    i.e. The copy of address in pointer is created.

    Date: 18 August 2021.
    Fair Oaks, CA.
 */

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

/***
 * Whenever you are passing address of variable
 * basically you are passing copy of that address
 * passing pointer by value.
 * Remember pointers are passed by value.
 * i.e. the copy of address in pointer is created
 */

/***
 * https://www.youtube.com/watch?v=4Tv3uebRasg
 * 30 Sec.
 */

#define debug(str,args...) printf("[%s] L=%d :"str"\n", __func__, __LINE__, ##args)

int a = 20;

/***
 * Call by address
 * op = 20
 */
void passbyref_works(int *p) {
  *p = a;
}

/***
 * Call by Value
 * op = 10
 */
void passbyref_NOTworks(int *p) {
  p = &a;
}

void test() {
  int x = 10;
  int *p = &x;
  passbyref_works(p);
  debug("x= %d", x);
  //passbyref_NOTworks(p);
  debug("x= %d", x);
}

int main (int argc, char **argv) {
  int ret = 0;

  test();
  debug("Output = %d", ret);
  return 0;
}

/**

 **/
