#include <stdio.h>
#include <stdlib.h>
#include "base.h"
#include "init.h"
#include "interrupt.h"

extern int *isUpgraded;

int main () {

  base ();

  printf ("\n[main] isUpgraded = %d \n", *isUpgraded);
 
  return 0;
}
