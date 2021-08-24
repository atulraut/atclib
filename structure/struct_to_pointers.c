/***
    Pointer's to Structure

    offsetof :
    https://elixir.bootlin.com/linux/latest/source/tools/usb/usbip/libsrc/list.h#L124
    https://gist.github.com/explogx/f71cf6f5d6b9ae06c807e66c24a583ca
    container_of :
    https://elixir.bootlin.com/linux/latest/source/tools/include/linux/kernel.h#L23
    https://www.stupid-projects.com/container_of/

    Date: 21 August 2021.
    Fair Oaks, CA.
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>
#include <string.h>  /* malloc */
#include <stdbool.h>
#include <math.h>
#include <assert.h>
#include <stdint.h> /* uint32_t */
#include <unistd.h> /* sleep */

#define debug(str,args...) printf("[%s] L=%d :"str"\n", __func__, __LINE__, ##args)

/* Testing How internall struct works hence using packed keyword */
void ptr_2_struct() {
  struct __attribute__((__packed__)) test {
    short  a;  // 2
    char   b;  // 1
    double c;  // 8
    int    d;  // 4
               // 15 - Total
  };
  // Scale factor for struct test - 15

  struct test v = {12, 'S', 4.94, 432};
  struct test *p;
  p = &v;

  debug ("a = %hd  a= %hd",  v.a, p->a);
  debug ("c = %c   c= %c",    v.b, p->b);
  debug ("lf = %lf lfa= %lf", v.c, p->c);
  debug ("d = %d   d= %d",    v.d, p->d);

  // Access using V Dot operator.
  // I want to access c double member.
  double thisdble = *((double *)(((char*)&v) + 3));
  debug ("thisdble = %lf", thisdble);

  // Access using P Array operator.
  // I want to access d int member.
  int thisint = *((int *)(((char *)p) + 11));
  debug ("thisint= %d", thisint);

  // Check scale factor, see how it works.
  p = NULL;
  // P is NULL as starting address means 0 so &p == 0+a == so a is also 0 so 0+0 = 0.
  // Same for b, so b = 2 so 0 + 2 = 2
  // Same for c, so c = 3 (per above) so 0 + 3 = 3
  // Same for d, so d = 11, so 0 + 11 = 11.
  // Note, we are trying to access address hence &p and not value at locaion 0 or 2
  // like using just p->a, this will crash the program.
  debug ("short a=%hd char b=%u double c=%u int d=%u", &p->a, &p->b, &p->c, &p->d);
}

int main (int argc, char **argv) {
  int ret = 0;

  ptr_2_struct();

  debug("Output = %d", ret);
  return 0;
}

/**
=> ./a.out
[ptr_2_struct] L=36 :a = 12  a= 12
[ptr_2_struct] L=37 :c = S   c= S
[ptr_2_struct] L=38 :lf = 4.940000 lfa= 4.940000
[ptr_2_struct] L=39 :d = 432   d= 432
[ptr_2_struct] L=44 :thisdble = 4.940000
[ptr_2_struct] L=49 :thisint= 432
[ptr_2_struct] L=53 :short a=0 char b=2 double c=3 int d=11
[main] L=61 :Output = 0
 **/
