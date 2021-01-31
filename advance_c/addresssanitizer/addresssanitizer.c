/***
    1] https://embeddedbits.org/finding-memory-bugs-with-addresssanitizer/
    2] https://stackoverflow.com/questions/12380758/error-function-returns-address-of-local-variable
    3] https://stackoverflow.com/questions/58488551/how-should-the-heap-buffer-overflow-error-message-be-read
    4] https://github.com/google/sanitizers/wiki/AddressSanitizerAlgorithm
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, const char *argv[]) {
    char *msg = "Hello world!";
    char *ptr = NULL;

    ptr = malloc(strlen(msg));

    /* Fix */
    //    ptr = malloc(strlen(msg)+1);

    strcpy(ptr, msg);

    printf("%s\n", ptr);

    /* Fix */
    //    free(ptr);
    return 0;
}

/***
    Step I :
    $ gcc main.c -o main -Wall -Werror -g
    $ ./main
    Hello world
    Step II :
    $ gcc main.c -o main -Wall -Werror -g -fsanitize=address

To Fix below Error Check link 2 above in comment, no need to allocate memory.
==>  gcc smallest_string_with_numeric__Val.c -o main -Wall -Werror -g -fsanitize=address

=> ./main
result = 0x60200000eff0
=================================================================
==19945==ERROR: AddressSanitizer: heap-buffer-overflow on address 0x60200000eff4 at pc 0x7f168c09f1e9 bp 0x7ffefb7f91b0 sp 0x7ffefb7f8928
READ of size 5 at 0x60200000eff4 thread T0
    #0 0x7f168c09f1e8  (/usr/lib/x86_64-linux-gnu/libasan.so.2+0x601e8)
    #1 0x7f168c09f7f7 in __interceptor_vprintf (/usr/lib/x86_64-linux-gnu/libasan.so.2+0x607f7)
    #2 0x7f168c09f907 in __interceptor_printf (/usr/lib/x86_64-linux-gnu/libasan.so.2+0x60907)
    #3 0x4009c1 in getSmallestString /home/atul/dev/c/to_push/atclib/leetCode/string/smallest_string_with_numeric__Val.c:30
    #4 0x400a01 in main /home/atul/dev/c/to_push/atclib/leetCode/string/smallest_string_with_numeric__Val.c:40
    #5 0x7f168bc9583f in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x2083f)
    #6 0x4007f8 in _start (/home/atul/dev/c/to_push/atclib/leetCode/string/main+0x4007f8)

0x60200000eff4 is located 0 bytes to the right of 4-byte region [0x60200000eff0,0x60200000eff4)
allocated by thread T0 here:
    #0 0x7f168c0d7602 in malloc (/usr/lib/x86_64-linux-gnu/libasan.so.2+0x98602)
    #1 0x4008ec in getSmallestString /home/atul/dev/c/to_push/atclib/leetCode/string/smallest_string_with_numeric__Val.c:18
    #2 0x400a01 in main /home/atul/dev/c/to_push/atclib/leetCode/string/smallest_string_with_numeric__Val.c:40
    #3 0x7f168bc9583f in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x2083f)

SUMMARY: AddressSanitizer: heap-buffer-overflow ??:0 ??
Shadow bytes around the buggy address:
  0x0c047fff9da0: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x0c047fff9db0: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x0c047fff9dc0: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x0c047fff9dd0: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x0c047fff9de0: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
=>0x0c047fff9df0: fa fa fa fa fa fa fa fa fa fa fa fa fa fa[04]fa
  0x0c047fff9e00: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x0c047fff9e10: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x0c047fff9e20: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x0c047fff9e30: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x0c047fff9e40: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
Shadow byte legend (one shadow byte represents 8 application bytes):
  Addressable:           00
  Partially addressable: 01 02 03 04 05 06 07
  Heap left redzone:       fa
  Heap right redzone:      fb
  Freed heap region:       fd
  Stack left redzone:      f1
  Stack mid redzone:       f2
  Stack right redzone:     f3
  Stack partial redzone:   f4
  Stack after return:      f5
  Stack use after scope:   f8
  Global redzone:          f9
  Global init order:       f6
  Poisoned by user:        f7
  Container overflow:      fc
  Array cookie:            ac
  Intra object redzone:    bb
  ASan internal:           fe
==19945==ABORTING

*/
