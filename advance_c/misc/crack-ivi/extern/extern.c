#include <stdio.h>

#define debug(str,args...) printf("[%s] L=%d :"str"\n", __func__, __LINE__, ##args)

int my_var;

void print_value () {
  debug ("my_var = %d", my_var);
}
