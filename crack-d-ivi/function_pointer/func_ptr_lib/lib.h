#include <stdio.h>

struct msg_type {
  int (*cmd_send) (int pcnt);
  int (*cmd_recv) (int pcnt);
};

int nt1(int pcnt);
int nt2(int pcnt);
void assign (void *);
