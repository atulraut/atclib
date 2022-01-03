/***
    https://leetcode.com/problems/day-of-the-year
    1154. Day of the Year

    Given a string date representing a Gregorian calendar
    date formatted as YYYY-MM-DD, return the day number of the year.

    Input: date = "2019-01-09"
    Output: 9
    Explanation: Given date is the 9th day of the year in 2019.

    Input: date = "2019-02-10"
    Output: 41

    Constraints:
    date.length == 10
    date[4] == date[7] == '-', and all other date[i]'s are digits
    date represents a calendar date between Jan 1st, 1900 and Dec 31th, 2019.

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address dayOfYear.c -lm

    Date: 2, Jan, 2022
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

/* Linux Implemention */
long atoi_linux(const char *s) {
  unsigned long ret = 0;
  unsigned long d;
  int neg = 0;

  if (*s == '-') {
    neg = 1;
    s++;
  }

  while (1) {
    d = (*s++) - '0';
    if (d > 9)
      break;
    ret *= 10;
    ret += d;
  }

  return neg ? -ret : ret;
}

int dayOfYear(char* date) {
  char month[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

  int year = atoi_linux(date);
  int mon  = atoi(date + 5);
  int day  = atoi(date + 8);
  int res  = 0;

  debug("date = %s y=%d, m=%d, d=%d", date, year, mon, day);
  if (mon>2)
    if (year % 400 == 0 || (year % 4 == 0 && year % 100))
      month[1]++;

  for (int i = 0; i < mon - 1; i++) res += month[i];

  return res + day;
}

int dayOfYear__(char* date) {
  int i=0, sum = 0;
  char m[2] = {0};
  char d[2] = {0};
  int month[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  /*
     m[0] = date[6]  - '0';
     m[1] = date[7]  - '0';
     d[0] = date[9]  - '0';
     d[1] = date[10]  - '0';
  */
  debug ("m[5] = %d", date[5] - '0');
  debug ("m[6] = %d", date[6] - '0');
  debug ("d[8] = %d", date[8] - '0');
  debug ("d[9]= %d", date[9] - '0');

  while (date[i] != '\0') {
    if (date[i] == '-') {
      ++i;
      continue;
    }
    debug("AR = %d", (date[i]- '0'));
    ++i;
  }
  if (date[5] == '0') {
    int m1 = date[6]-2 - '0';
    debug (" s = %d Month = %d", m1, month[m1]);
    sum = (date[8] - '0') * 10 + date[9] - '0';
    debug ("sum = %d", sum);
    sum +=month[m1];
  }
  debug ("sum = %d", sum);
  return sum;
}

int dayOfYear_(char* date) {
  int year;
  int month;
  int day;
  int month_day[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  int count;
  int i;

  sscanf(date,"%d-%d-%d",&year,&month,&day);
  debug ("y=%d m=%d d=%d", year, month, day);
  // Start with the day value
  count = day;

  // First, if we're in March or later, add in a leap day, if appropriate
  // (year is divisible by 4, and not by 100, unless divisible by 400)
  if (month>2)
    if (((year % 4)==0) && (((year % 100)!=0) || ((year % 400)==0)))
      day++;

  // Then add in the total of normal days per month for each previous month
  for (i=0; i < month-1; i++)
    day += month_day[i];

  debug ("day = %d", day);
  return day;
}

int main (int argc, char **argv) {
  int ret = 0;
  char date[] = "2019-02-10";

  ret = dayOfYear(date);
  debug("Output = %d", ret);
  return 0;
}

/**
   => ./a.out
   [dayOfYear] L=65 :date = 2019-02-10 y=2019, m=2, d=10
   [main] L=142 :Output = 41
**/
