/***

    Copy len bytes from a scatter-gather array starting at byte offset, across up to n segments.
    You’ll also need a destination buffer argument.

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    matx
    Date: Fri Oct  2 13:56:35 PDT 2026
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

struct sg {
  void   *addr;
  size_t sg_len;
};

/*
sg_len1 = 10 // skip
sg_len2 = 15 // 13
sg_len3 = 12
sg_len4 = 2
*/

/*
 * Copy 'len' bytes from SG list into dst,
 * starting at byte 'offset' in the SG stream.
 *
 * Returns number of bytes actually copied.
 */
size_t sg_copy(struct sg *s, int n,
               size_t offset, size_t len,
               void *dst)
{
  size_t copied = 0;
  unsigned char *d = dst;

  for (int i = 0; i < n && copied < len; i++) {

    /* Offset skips this entire segment */
    if (offset >= s[i].sg_len) {
      offset -= s[i].sg_len;
      continue;
    }

    /*
     * We are now inside this segment.
     *
     * segment:
     * +---------------------------+
     * | skip |      copy          |
     * +---------------------------+
     *        ^
     *      offset
     */
    debug("sg[%d] offlet [%lu]", i, offset);
    size_t available = s[i].sg_len - offset;
    size_t remaining = len - copied;

    size_t count = (available < remaining) ? available : remaining;
    debug("available=[%lu] remaining=[%lu] count=[%lu]", available, remaining, count);
    memcpy(d + copied, (unsigned char *)s[i].addr + offset, count);
    copied += count;
    debug("->[%s] copied=[%lu] count=[%lu]", d, copied, count);
    debug("count = %lu",count);
    /* offset only applies to the first matching segment */
    offset = 0;
  }

  return copied;
}

int test(void) {
  char a[] = "ABCDEFGHIJ";   // 10 bytes
  char b[] = "KLMNO";        // 5 bytes
  char c[] = "PQRSTUV";      // 7 bytes

  struct sg list[] = {
    { a, 10 },
    { b, 5  },
    { c, 7  }
  };

  char dst[100] = {0};

  size_t copied = sg_copy(list, 3,
			  7,      // offset
			  10,     // number of bytes
			  dst);
  /*
   * sg stream:
   *
   * ABCDEFGHIJ KLMNO PQRSTUV
   * 0123456789
   *
   * offset = 7
   *
   *        |
   *        v
   * ABCDEFGHIJKLMNOPQRSTUV
   *        H I J K L M N O P Q
   *        <----- 10 bytes ----->
   */

  printf("Copied = %zu bytes\n", copied);
  printf("Result = ");

  for (size_t i = 0; i < copied; i++)
    printf("%c", dst[i]);

  printf("\n");

  return 0;
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**
   L=[70][advance_c/misc/102_matx_sg_copy.c]->[sg_copy] :| sg[0] offlet [7]
   L=[75][advance_c/misc/102_matx_sg_copy.c]->[sg_copy] :| available=[3] remaining=[10] count=[3]
   L=[77][advance_c/misc/102_matx_sg_copy.c]->[sg_copy] :| ->[HIJ]
   L=[79][advance_c/misc/102_matx_sg_copy.c]->[sg_copy] :| count = 3
   L=[70][advance_c/misc/102_matx_sg_copy.c]->[sg_copy] :| sg[1] offlet [0]
   L=[75][advance_c/misc/102_matx_sg_copy.c]->[sg_copy] :| available=[5] remaining=[7] count=[5]
   L=[77][advance_c/misc/102_matx_sg_copy.c]->[sg_copy] :| ->[HIJKLMNO]
   L=[79][advance_c/misc/102_matx_sg_copy.c]->[sg_copy] :| count = 5
   L=[70][advance_c/misc/102_matx_sg_copy.c]->[sg_copy] :| sg[2] offlet [0]
   L=[75][advance_c/misc/102_matx_sg_copy.c]->[sg_copy] :| available=[7] remaining=[2] count=[2]
   L=[77][advance_c/misc/102_matx_sg_copy.c]->[sg_copy] :| ->[HIJKLMNOPQ]
   L=[79][advance_c/misc/102_matx_sg_copy.c]->[sg_copy] :| count = 2
   Copied = 10 bytes
   Result = HIJKLMNOPQ
**/
