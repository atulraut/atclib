/***
    list of unordered records with timestamp, name, data * output: arranged
    records satisfying all of below.
    1. Group by name
    2. Sort each group by timestamp in descending order
    3. Sort groups by timestamp

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm
    Date: Wed Jul 27 11:15:41 PM PDT 2022
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

#define debug(str,args...) printf("[%s] L=%d :"str"\n", __func__, __LINE__, ##args)

#define TSIZE 5

enum type_of_record {EMPTY, DELETED, OCCUPIED};

struct student {
  int studentId;
  char studentName[20];
};

struct Record {
  struct student info;
  enum type_of_record status;
};
