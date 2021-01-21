#ifndef AT_LIB
#define AT_LIB

/***
    Command To Compile using address sanitizer :
    gcc main.c -o main -Wall -Werror -g -fsanitize=address
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <assert.h>

/***
    In case File Debug Option needs to Enabled.
*/
//#define debug(str,args...) printf("[%s] [%s()] L=%d :"str"\n",__FILE__, __func__, __LINE__, ##args)

#define debug(str,args...) printf("[%s] L=%d :"str"\n", __func__, __LINE__, ##args)
#endif
