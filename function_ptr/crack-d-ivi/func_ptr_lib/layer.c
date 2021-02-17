/*
 * Explain function pointers using library code base.
 * Explain setting function pointers setting on other file.
 */

#include <stdio.h>
#include <stdlib.h>
#include "lib.h"

struct _ctx {
  struct msg_type handle;
};


int main()
{
  struct _ctx *nt;
  nt = (struct _ctx *)malloc(sizeof (struct _ctx));
  assign(&nt->handle);
  nt->handle.cmd_send(3);
  nt->handle.cmd_recv(4);
  return 0;
}
