/***
    LeetCodde Roman to Integer
    https://leetcode.com/problems/roman-to-integer/

    Roman numerals are represented by seven different symbols: I, V, X, L, C, D and M.
    Symbol       Value
    I             1
    V             5
    X             10
    L             50
    C             100
    D             500
    M             1000

    For example, 2 is written as II in Roman numeral, just two one's added together
    12 is written as XII, which is simply X + II. The number 27 is written as XXVII,
    which is XX + V + II.

    Roman numerals are usually written largest to smallest from left to right.
    However, the numeral for four is not IIII. Instead, the number four is written
    as IV. Because the one is before the five we subtract it making four.
    The same principle applies to the number nine, which is written as IX.
    There are six instances where subtraction is used:
    I can be placed before V (5) and X (10) to make 4 and 9.
    X can be placed before L (50) and C (100) to make 40 and 90.
    C can be placed before D (500) and M (1000) to make 400 and 900.
    Given a roman numeral, convert it to an integer.

    Example 1:
    Input: s = "III"
    Output: 3

    Example 2:
    Input: s = "IV"
    Output: 4

    Example 3:
    Input: s = "IX"
    Output: 9

    Example 4:
    Input: s = "LVIII"
    Output: 58
    Explanation: L = 50, V= 5, III = 3.

    Example 5:
    Input: s = "MCMXCIV"
    Output: 1994
    Explanation: M = 1000, CM = 900, XC = 90 and IV = 4.

*/
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

/***
    In case File Debug Option needs to Enabled.
*/

#define debug(str,args...) printf("[%s] L=%d :"str"\n", __func__, __LINE__, ##args)


int map_char_to_num(char ch) {
  switch (ch) {
  case 'I':
    return 1;
  case 'V':
    return 5;
  case 'X':
    return 10;
  case 'L':
    return 50;
  case 'C':
    return 100;
  case 'D':
    return 500;
  case 'M':
    return 1000;
  default:
    return 0;
  }
  return 0;
}

int str_to_num(char a, char b, int *i) {
  if ((a == 'I' && (b == 'V' || b == 'X')) ||
      (a == 'X' && (b == 'L' || b == 'C')) ||
      (a == 'C' && (b == 'D' || b == 'M'))) {
    *i = *i + 1;
    return (map_char_to_num(b) - map_char_to_num(a));
  }
  return (map_char_to_num(a));
}

int romanToInt(char * s) {
  int i;
  long long ret = 0;
  for (i = 0; i < strlen(s); i++)
    ret += str_to_num(s[i], s[i + 1], &i);
  return ret;
}

/* atclib : 4ms */
int romanToInt2(char * s) {
  int value[100]; // Index out of bound if redueced the size.
  value['I'] = 1;
  value['V'] = 5;
  value['X'] = 10;
  value['L'] = 50;
  value['C'] = 100;
  value['D'] = 500;
  value['M'] = 1000;
  value['\0'] = 0;
  int sum = 0;

  for(int i = 0; s[i] !='\0'; i++){
    if(value[s[i]] < value[s[i + 1]])
      sum = sum - value[s[i]];
    else
      sum += value[s[i]];
  }
  return sum;
}

int main () {
  char str[] = "MCMXCIV";
  char str2[] = "LVIII";
  char str3[] = "IV";
  debug ("--> %d ", romanToInt(str));

  return 0;
}

/**
   => ./a.out
   [main] L=88 :--> 1994
**/
