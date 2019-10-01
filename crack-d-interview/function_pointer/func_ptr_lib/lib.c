#include <stdio.h>
#include "lib.h"

int nt1(int pcnt) {
  printf ("it works = %d \n", pcnt);
  return 0;
}

int nt2(int pcnt) {
  printf ("it works = %d \n", pcnt);
  return 0;
}

void assign (void *_ptr) {
  struct msg_type *han = (struct msg_type *)_ptr;

  han->cmd_send = nt1;
  han->cmd_recv = nt2;
  printf ("assign done !\n");
}
