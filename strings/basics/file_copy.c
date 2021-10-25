/***
    Write your own copy() function.

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: 24 Oct 2021
    Fair Oaks, CA.
 */

/*----------------------------------- Header --------------------------------------*/
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

/*----------------------------------- Micro --------------------------------------*/
#define debug(str,args...) printf("[%s] L=%d :"str"\n", __func__, __LINE__, ##args)
#define atsizeof(object) (char *)(&object+1) - (char*)(&object)
#define arrsz(x)  (sizeof(x) / sizeof((x)[0]))
#define max(a,b)		\
  ({ typeof (a) _a = (a);	\
    typeof (b) _b = (b);	\
    _a > _b ? _a : _b; })
#define min(a,b)		\
  ({ typeof (a) _a = (a);	\
    typeof (b) _b = (b);	\
    _a < _b ? _a : _b; })
/*----------------------------------- Micro --------------------------------------*/

#define MAX_LINE_LEN 1000 /* maximum line length supported. */

int main(int argc, char* argv[]) {
  char* file_path_from;
  char* file_path_to;
  FILE* f_from;
  FILE* f_to;
  char buf[MAX_LINE_LEN+1];

  file_path_from = "from.txt";
  file_path_to   = "to.txt";
  f_from = fopen("from.txt", "r");
  if (!f_from) {
    debug ("Oops, no input file to read!");
    exit(1);
  }
  f_to = fopen(file_path_to, "w+");
  if (!f_to) {
    debug ("Oops, no output frile to write!");
    exit(1);
  }

  /* Copy source to target, line by line. */
  while (fgets(buf, MAX_LINE_LEN+1, f_from)) {
    if (fputs(buf, f_to) == EOF) {
      exit(1);
    }
  }

  if (!feof(f_from)) {
    exit(1);
  }
  if (fclose(f_from) == EOF) {
    exit(1);
  }
  if (fclose(f_to) == EOF) {
    exit(1);
  }
  return(0);
}

/**

 **/
