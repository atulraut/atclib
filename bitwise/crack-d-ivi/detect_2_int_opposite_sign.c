#include <stdio.h>
#include <stdlib.h>
#include "../../at_lib.h"

int detect_sign() {
  int x = -1;
  int y = 1;
  int ret;

  ret = ((x^y) < 0);

  debug (" Ret = %d \n", ret);

  return ret;
}

int main() {

  if(detect_sign())
    debug ("Signs are opposite's! \n");
  else
    debug ("Same Sign! \n");
  return 0;
}

/**
   => ./a.out
   [detect_sign] L=12 : Ret = 1

   [main] L=20 :Signs are opposite's!
**/
