/***
    Zero-length arrays :
    GCC allows the declaration of zero-length arrays.
    A zero-length array can be useful as the last element of a
    structure that is, for example, a header for a variable-length
    object. In this case, the name of the zero-length array can be
    used as a pointer to the dynamically allocated object.
    Ref :
    https://embeddedbits.org/finding-memory-bugs-with-addresssanitizer
    https://embeddedbits.org/gcc-extensions-to-the-c-language/
*/

#include <stdio.h>
#include <stdlib.h>

struct msg_header {
  int type;
  int size;
  char content[0];
};

int main(int argc, const char *argv[]) {
  struct msg_header *msg;
  int size = 1024;

  msg = (struct msg_header *) malloc(sizeof (struct msg_header) + size);

  msg->type = 0x01;
  msg->size = size;

  printf("[%s] msg header  is at %p\n",__func__,  (void *)msg);
  printf("[%s] msg content is at %p\n",__func__,  (void *)msg->content);

  return 0;
}

/***
    => gcc zero_length_arrays.c -Wall -Werror -o array
    atul@Raigad:~/dev/c/to_push/atclib/advance_c/addresssanitizer
    => ./array
    [main] msg header  is at 0x18a5010
    [main] msg content is at 0x18a5018
*/
