/***

    Implement align malloc

    https://chatgpt.com/c/6abc5be4-eecc-83e8-8bb3-32c6276d2371

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Fri Oct 16 20:45:35 PDT 2026
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

void *aligned_malloc(size_t size, size_t alignment) {

  if (alignment == 0 || (alignment & (alignment - 1)) != 0)
    return NULL;  // alignment must be power of 2

  /*
   * Extra memory:
   *   alignment - 1  -> room to move forward to aligned address
   *   sizeof(void *) -> store original malloc pointer
   */
  void *raw = malloc(size + alignment - 1 + sizeof(void *));
  if (raw == NULL)
    return NULL;

  /*
   * Skip space needed to save raw pointer,
   * then round UP to alignment boundary.
   */
  uintptr_t addr = (uintptr_t)raw + sizeof(void *);

  uintptr_t aligned = (addr + alignment - 1) & ~(uintptr_t)(alignment - 1);

  /*
   * Store original malloc pointer immediately
   * before aligned address.
   *
   *             aligned
   *                |
   *                v
   * +------+--------+-------------------+
   * | ...  | raw ptr| usable memory     |
   * +------+--------+-------------------+
   * ^               ^
   * raw             returned pointer
   */
  ((void **)aligned)[-1] = raw;

  return (void *)aligned;
}

void aligned_free(void *ptr) {
  if (ptr == NULL)
    return;

  /* Recover original malloc pointer */
  void *raw = ((void **)ptr)[-1];

  free(raw);
}

int test(void) {
  void *p = aligned_malloc(100, 64);

  if (p == NULL) {
    printf("Allocation failed\n");
    return 1;
  }

  printf("Aligned address = %p\n", p);
  printf("Address %% 64   = %lu\n",
	 (unsigned long)((uintptr_t)p % 64));

  aligned_free(p);

  return 0;
}

int main (int argc, char **argv) {
  return test();
}

/**
   Aligned address = 0x10442d800
   Address % 64   = 0
**/
