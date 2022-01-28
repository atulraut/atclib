/***
    https://leetcode.com/problems/sequential-digits/
    Sequential Digits

    An integer has sequential digits if and only if each
    digit in the number is one more than the previous digit.

    Return a sorted list of all the integers in the
    range [low, high] inclusive that have sequential digits.

    Input: low = 100, high = 300
    Output: [123,234]

    Input: low = 1000, high = 13000
    Output: [1234,2345,3456,4567,5678,6789,12345]

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: 27 Jan 2021
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
#define max(a,b)				\
  ({ __typeof__ (a) _a = (a);			\
    __typeof__ (b) _b = (b);			\
    _a > _b ? _a : _b; })
#define min(a,b)				\
  ({ __typeof__ (a) _a = (a);			\
    __typeof__ (b) _b = (b);			\
    _a < _b ? _a : _b; })
/*----------------------------------- Micro --------------------------------------*/

void ft_swap(int *a, int *b) {
  int	tmp;

  tmp = *a;
  *a = *b;
  *b = tmp;
}

void ft_sort(int *res, int size) {
  int	i;
  int	j;

  i = 0;
  j = 0;
  while (i < size) {
    while (j < size) {
      if (res[j] > res[i])
	ft_swap(&res[j], &res[i]);
      j++;
    }
    j = 0;
    i++;
  }
}

int* sequentialDigits(int low, int high, int *returnSize) {
  int	*res;
  int	num;
  int	digit;
  int	next;
  int i;

  digit = 1;
  i = 0;
  while (digit < 10) {
    num = digit;
    next = digit;
    while (num <= high && next < 10) {
      if (num >= low)
	i++;
      next += 1;
      num = num * 10 + next;
    }
    digit++;
  }
  *returnSize = i;
  res = malloc(sizeof(int) * i);

  digit = 1;
  i = 0;
  while (digit < 10) {
    num = digit;
    next = digit;
    while (num <= high && next < 10) {
      if (num >= low)
	res[i++] = num;
      next += 1;
      num = num * 10 + next;
    }
    digit++;
  }
  ft_sort(res, *returnSize);
  return (res);
}

void test() {
  int* ret;
  int low = 100;
  int high = 300;
  int returnSize;
  ret = sequentialDigits(low, high, &returnSize);

  for (int i=0; i<returnSize; ++i)
    debug("Output = %d", ret[i]);
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**
   => ./a.out
   [test] L=108 :Output = 123
   [test] L=108 :Output = 234
**/
