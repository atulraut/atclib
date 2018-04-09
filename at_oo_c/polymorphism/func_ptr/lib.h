#include <stdio.h>

struct msg_type {
  int (*cmd_send) (int pcnt);
  int (*cmd_recv) (int pcnt);
};

int nt1(int pcnt) {
  printf ("it works = %d \n", pcnt);
  return 0;
}

int nt2(int pcnt) {
  printf ("it works = %d \n", pcnt);
  return 0;
}

void assign (struct msg_type *han) {
  int *ptr;
  han->cmd_send = nt1;
  han->cmd_recv = nt2;
  printf ("assign done !\n");
}
