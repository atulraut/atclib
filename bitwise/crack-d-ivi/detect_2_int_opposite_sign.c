#include <stdio.h>
#include <stdlib.h>

#define debug(str,args...) printf("[%s] L=%d :"str"\n", __func__, __LINE__, ##args)

int detect_sign() {
  int x = -1;
  int y = 1;
  int ret;

  ret = ((x^y) < 0);

  debug (" Ret = %d \n", ret);

  return ret;
}

void test () {
  if(detect_sign())
    debug ("Signs are opposite's! \n");
  else
    debug ("Same Sign! \n");
}

void test1() {
  debug ("ret = %d", ((-1^1)));
  debug ("ret = %d", ((-1^1) < 0));
}

int main() {
  test();
  test1();
  return 0;
}

/**
   => ./a.out
   [detect_sign] L=12 : Ret = 1

   [main] L=20 :Signs are opposite's!
**/
