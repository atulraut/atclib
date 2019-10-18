#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
  How to print the arguments recieved by main() ?
  argv is array of character pointer
*/
int main (int argc, char *argv[]) {
  int i;
  for(i=0; i<argc; i++) {
    printf ("--> %s \n", argv[i]);
  }
}
