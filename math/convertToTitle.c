/***
    https://leetcode.com/problems/excel-sheet-column-title
    Excel Sheet Column Title

    Given an integer columnNumber, return its corresponding column title as it appears in an Excel sheet.

    For example:
    A -> 1
    B -> 2
    C -> 3
    ...
    Z -> 26
    AA -> 27
    AB -> 28
    ...

    Input: columnNumber = 1
    Output: "A"

    Input: columnNumber = 28
    Output: "AB"

    Input: columnNumber = 701
    Output: "ZY"

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address convertToTitle.c -lm

    Date: 12/30/2021
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

/*----------------------------------- Micro --------------------------------------*/
#define debug(str,args...) printf("[%s] L=%d :"str"\n", __func__, __LINE__, ##args)
#define atsizeof(object) (char *)(&object+1) - (char*)(&object)
#define arrsz(x)  (sizeof(x) / sizeof((x)[0]))
#define max(a,b)		\
  ({ __typeof__ (a) _a = (a);	\
    __typeof__ (b) _b = (b);	\
    _a > _b ? _a : _b; })
#define min(a,b)		\
  ({ __typeof__ (a) _a = (a);	\
    __typeof__ (b) _b = (b);	\
    _a < _b ? _a : _b; })
/*----------------------------------- Micro --------------------------------------*/

char* convertToTitle(int columnNumber) {
  char *title = malloc(sizeof(char)*16);
  int count = 0;
  int max = 16;

  while (columnNumber) {
    title[count] = (columnNumber-1)%26+ 'A';
    count++;
    if (count > max) {
      title = realloc(title, sizeof(char)*max*2);
      max *= 2;
    }
    columnNumber -= 1;
    columnNumber /= 26;
  }
  title[count] = 0;
  count--;

  for (int i = 0; i <= count/2; i++) {
    char temp = title[i];
    title[i] = title[count - i];
    title[count - i] = temp;
  }

  return title;
}

/**
   https://leetcode.com/problems/excel-sheet-column-number/
   Excel Sheet Column Number

   Given a string columnTitle that represents the column title
   as appear in an Excel sheet, return its corresponding column number.

   For example:
   A -> 1
   B -> 2
   C -> 3
   ...
   Z -> 26
   AA -> 27
   AB -> 28
   ...

   Input: columnTitle = "A"
   Output: 1

   Input: columnTitle = "AB"
   Output: 28

   Input: columnTitle = "ZY"
   Output: 701

   Constraints:
   1 <= columnTitle.length <= 7
   columnTitle consists only of uppercase English letters.
   columnTitle is in the range ["A", "FXSHRXW"].
*/
int titleToNumber(char* columnTitle) {
  int sum = 0;
  while(*columnTitle)
    sum = 26*sum+(*(columnTitle++)-'A'+1);
  return sum;
}

int main (int argc, char **argv) {
  int retur = 0;
  char* ret;
  char cTitle[] = "ZY";

  ret = convertToTitle(701);
  debug("Output = %s", ret);

  retur = titleToNumber(cTitle);
  debug("Output = %d", retur);

  return 0;
}

/**
   => ./a.out
   [main] L=89 :Output = ZY
   [main] L=101 :Output = 701
**/
