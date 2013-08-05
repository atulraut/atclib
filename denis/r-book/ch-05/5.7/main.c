/*
* Aim : The routines day_of_year & month_day with 
* array indexing.
* Auther : Atul Ramesh Raut
* Date   : Thursday August 01, 2013. 05:40AM
***/

#include <stdio.h>
#include <stdlib.h>

int day_of_year (int year, int month, int day);
void month_day (int year, int yearday, int *pmonth, int *pday);

static char daytab[2][13] = {
  {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
  {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

int main () {
  int day;
  int *pmonth, int *pday;
  day = day_of_year (2000, 10, 19);
  printf ("day_of_year = %d\n", day);
  month_day (1981, 19, &pmonth, &pday);
  printf ("pmonth = %d, pday = %d\n", *pmonth, *pday);
}

/*
* day_of_year : set day of year from manth & day
* converts the month & day into, day of the year 
* e.g. March 1, 60th day of a non-leap year & 61st day of leap year.
***/
int day_of_year (int year, int month, int day) {
  int i, leap;
  leap = year%4 == 0 && year % 100 != 0 || year % 400 == 0;
  printf ("leap = %d\n", leap);
  for (i=1; i< month; i++)
    day += daytab[leap][i];
  return day;
}

/*
 * month_day : converts the day of the year into the month & day.
 * month_day(1988, 60, &m, &d) set--> m-2 & d-29 (February 29th)
***/
void month_day (int year, int yearday, int *pmonth, int *pday) {
  int i, leap;
  leap = year%4 == 0 && year % 100 != 0 || year % 400 == 0;
  printf ("leap = %d\n", leap);

}

