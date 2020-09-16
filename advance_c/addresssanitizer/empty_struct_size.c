/***
    https://embeddedbits.org/finding-memory-bugs-with-addresssanitizer/
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct empty {
};

int main(int argc, const char *argv[]) {

  printf("[%s] sizeof struct empty is %ld\n",__func__, sizeof(struct empty));

  return 0;
}

/***
    atul@Raigad:~/dev/c/to_push/atclib/advance_c/addresssanitizer
    => ./empty
    [main] sizeof struct empty is 0

*/
