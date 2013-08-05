#include <stdio.h>
#include <stdlib.h>
#include "base.h"
#include "init.h"

int base () {
  int i = 10;
  printf ("\n[base] called 0 ");
  isUpgraded = NULL;
  printf ("\n[base] called 1 ");
  isUpgraded = &i;
  printf ("\n[base] called 2 = %d ", *isUpgraded);
  init (isUpgraded);
  printf ("\n[base] isUpgraded = %d \n", *isUpgraded);
  return 0;
}
