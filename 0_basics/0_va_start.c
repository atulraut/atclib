/***
    va_start
    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Sat Apr 11 09:54:04 PM PDT 2026

    Folsom, CA.

/*----------------------------------- Header --------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h> // va_arg
#include <ctype.h>
#include <limits.h>
#include <string.h>  /* malloc */
#include <stdbool.h>
#include <math.h>
#include <assert.h>
#include <stdint.h> /* uint32_t */
#include <unistd.h> /* sleep */

#define debug(str,args...) printf("L=[%d][%s]->[%s] :| "str"\n",__LINE__,__FILE__, __func__, ##args)

#include <stdio.h>
#include <stdarg.h>

int sum(int count, ...) {
  va_list ap;
  va_start(ap, count);

  int total = 0;
  for (int i = 0; i < count; i++) {
    total += va_arg(ap, int);
    debug(" total->%d", total);
  }

  va_end(ap);
  return total;
}

int main() {

  debug("%d\n", sum(3, 10, 20, 30)); // Output: 60
  return 0;
}

/**
   L=[35][va_start.c]->[sum] :|  total->10
   L=[35][va_start.c]->[sum] :|  total->30
   L=[35][va_start.c]->[sum] :|  total->60
   L=[44][va_start.c]->[main] :| 60
**/

/*
 * Theory :
    In C, va_list, va_start, and va_arg are used to handle functions with
    variable number of arguments (like printf).

    They are defined in #include <stdarg.h>.

    1. va_list - This is a type used to hold information about the
                 variable arguments.
        Think of it as a pointer/handle that lets you walk through the extra arguments.
        va_list args;
    2. va_start - This initializes the va_list so you can start accessing the
       variable arguments.
        Syntax:
        va_start(va_list ap, last_fixed_param);
        ap → your va_list
        last_fixed_param → the last named parameter before ...
        Example:
        va_start(args, count);
     3. va_arg - This retrieves the next argument from the list.
        Syntax:
        type value = va_arg(va_list ap, type);
        You must specify the correct type.
        Example:
        int x = va_arg(args, int);
     4. va_end
       (Not asked, but important) Cleans up the va_list.
       va_end(args);
     5. Above Example - How it works (simple idea)  ... means “extra arguments”
        va_start → start reading them
	va_arg → read one-by-one
	va_end → cleanup
	Important rules :-
	You must know the type of each argument
	No type safety (common source of bugs)
	Order matters
	Always call va_end
 */
