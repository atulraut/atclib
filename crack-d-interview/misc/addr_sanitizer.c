/*
  gcc addr_sanitizer.c -o main -Wall -Werror -g -fsanitize=address
  Ref : https://embeddedbits.org/finding-memory-bugs-with-addresssanitizer/

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main () {
  char *msg = "Hello";
  char *ptr = NULL;
  //ptr = malloc(strlen(msg)); // Error
  ptr = malloc(strlen(msg)+1); // Fix

  strcpy(ptr, msg);

  printf ("--> %s \n", ptr);

  free(ptr);
  ptr = NULL;

  return 0;
}
