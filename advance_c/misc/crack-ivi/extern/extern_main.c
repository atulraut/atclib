#include <stdio.h>
#include "extern.c"

int main () {
  extern int my_var;
  my_var = 500;
  print_value ();
  //  exit(0);
  return 0;
}
