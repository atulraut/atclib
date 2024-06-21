/***

    Generate Binary Strings of Length N

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Thu 20 Jun 2024 10:06:57 PM PDT
    Folsom, CA.
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

#define debug(str,args...) printf("L=[%d] [%s] :| "str"\n", __LINE__, __func__, ##args)

struct op {
  char** items;
  int len;
};

void bs_helper(struct op* res, char* slate, int n) {
  if (n == 0) { // Base case
    int len = strlen(slate);
    char* entry = (char *)calloc(len, sizeof(char));
    memcpy(entry, slate, len);
    res->items[res->len++] = entry;
  } else { // Recursive Case
    slate[n-1] = '0';
    bs_helper(res, slate, n-1);
    slate[n-1] = '1';
    bs_helper(res, slate, n-1);
  }
}

struct op* get_binary_strings(int n) {
  struct op* res = (struct op *)malloc(sizeof(struct op *));
  res->items = (char **)malloc(pow(2, n) * sizeof(char *));
  res->len = 0;

  char* slate = (char *)malloc(n * sizeof(char));
  for (int i=0; i<n; ++i)
    slate[i] = '0';

  slate[n-1] = '\0';
  bs_helper(res, slate, n);
  return res;
}

void test() {
  int n = 3;

  struct op* op1 = get_binary_strings(n);
  for (int i=0; i<op1->len; ++i)  {
    debug("Output[%d] = %s",i, op1->items[i]);
  }

  // free the resources
  for (int i=0; i<op1->len; ++i) {
    char* temp = op1->items[i];
    free (temp);
    temp = NULL;
  }
  free (op1->items);
  free (op1);
  op1 = NULL;
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**
   => ./a.out
   L=[63] [test] :| Output[0] = 000
   L=[63] [test] :| Output[1] = 100
   L=[63] [test] :| Output[2] = 010
   L=[63] [test] :| Output[3] = 110
   L=[63] [test] :| Output[4] = 001
   L=[63] [test] :| Output[5] = 101
   L=[63] [test] :| Output[6] = 011
   L=[63] [test] :| Output[7] = 111
**/
