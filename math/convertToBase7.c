/***
    https://leetcode.com/problems/base-7
    504. Base 7
    Given an integer num, return a string of its base 7 representation.

    Input: num = 100
    Output: "202"

    Input: num = -7
    Output: "-10"

    Constraints:
    -107 <= num <= 107

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: 12/31/2021
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

char* convertToBase7(int num){
  int l = 0;
  int x = abs(num);
  if(num==0)
    l++;
  while(x>0) {
    l++;
    x=x/7;
  }
  if(num<0)
    l++;
  l++;
  char *arr=malloc(sizeof(char)*l);
  int a = l-2, r;
  num=abs(num);

  if(num==0) {
    arr[a]='0';
    a--;
  }
  while(num>0) {
    r=num%7;
    num=num/7;
    arr[a]=r+'0';
    a--;
  }
  if(a==0)
    arr[a]='-';
  arr[l-1]='\0';
  return arr;
}

char* convertToBase7_(int num) {
  int neg;
  char *ans = malloc(20);
  int i, j;
  j = 0;

  if(num < 0)
    neg = 1, num = -num;
  else if(num > 0)
    neg = 0;
  else
    ans[j++] = '0';

  while(num) {
    ans[j++] = num % 7 + '0';
    num /= 7;
  }
  if(neg)
   ans[j++] = '-';
  ans[j--] = 0;

  i = 0;
  while(i < j) {
    char t = ans[i];
    ans[i] = ans[j];
    ans[j] = t;
    i++, j--;
  }
  return ans;
}

int main (int argc, char **argv) {
  char* ret;

  ret = convertToBase7(100);
  debug("Output = %s", ret);
  return 0;
}

/**
   => ./a.out
   [main] L=82 :Output = 202
**/
