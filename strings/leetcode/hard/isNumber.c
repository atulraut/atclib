/***
    Hard: 65. Valid Number
    https://leetcode.com/problems/valid-number/

    A valid number can be split up into these components (in order):
    A decimal number or an integer.
    (Optional) An 'e' or 'E', followed by an integer.
    A decimal number can be split up into these components (in order):
    (Optional) A sign character (either '+' or '-').
    One of the following formats:
    At least one digit, followed by a dot '.'.
    At least one digit, followed by a dot '.', followed by at least one digit.
    A dot '.', followed by at least one digit.

    An integer can be split up into these components (in order):

    (Optional) A sign character (either '+' or '-').
    At least one digit.

    For example, all the following are valid numbers: ["2", "0089", "-0.1", "+3.14", "4.", "-.9", "2e10",
    "-90E3", "3e+7", "+6e-1", "53.5e93", "-123.456e789"], while the following are not valid numbers:
    ["abc", "1a", "1e", "e3", "99e2.5", "--6", "-+3", "95a54e53"].

    Given a string s, return true if s is a valid number.

    Input: s = "0"
    Output: true

    Input: s = "e"
    Output: false

    Input: s = "."
    Output: false

    Input: s = ".1"
    Output: true

    Constraints:
    1 <= s.length <= 20
    s consists of only English letters (both uppercase and lowercase), digits (0-9),
    plus '+', minus '-', or dot '.'.

    Date: 17 May 2021
    San Diego, CA.
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

#define debug(str,args...) printf("[%s] L=%d :"str"\n", __func__, __LINE__, ##args)

struct _State {
  struct _State* next[256];
};

typedef struct _State State;

State* const ABT = (State*) 0;
State* const ACC = (State*) 1;
const int EOL = '\0';

State* get_dfa_start() {
  static State states[9];
  static State *start;

  if (!start) {
    int ch;
    int i;

    i = 0;
    states[i].next[' '] = &states[0];
    states[i].next['.'] = &states[1];
    states[i].next['+'] = states[i].next['-'] = &states[2];
    for (ch = '0'; ch <= '9'; ch++) states[i].next[ch] = &states[3];

    i = 1;
    for (ch = '0'; ch <= '9'; ch++) states[i].next[ch] = &states[4];

    i = 2;
    states[i].next['.'] = &states[1];
    for (ch = '0'; ch <= '9'; ch++) states[i].next[ch] = &states[3];

    i = 3;
    states[i].next['.'] = &states[4];
    states[i].next['e'] = states[i].next['E'] = &states[5];
    states[i].next[' '] = &states[7];
    for (ch = '0'; ch <= '9'; ch++) states[i].next[ch] = &states[3];
    states[i].next[EOL] = ACC;

    i = 4;
    states[i].next['e'] = states[i].next['E'] = &states[5];
    states[i].next[' '] = &states[7];
    for (ch = '0'; ch <= '9'; ch++) states[i].next[ch] = &states[4];
    states[i].next[EOL] = ACC;

    i = 5;
    states[i].next['+'] = states[i].next['-'] = &states[6];
    for (ch = '0'; ch <= '9'; ch++) states[i].next[ch] = &states[8];

    i = 6;
    for (ch = '0'; ch <= '9'; ch++) states[i].next[ch] = &states[8];

    i = 7;
    states[i].next[' '] = &states[7];
    states[i].next[EOL] = ACC;

    i = 8;
    states[i].next[' '] = &states[7];
    for (ch = '0'; ch <= '9'; ch++) states[i].next[ch] = &states[8];
    states[i].next[EOL] = ACC;

    start = states;
  }

  return start;
}

/**
   4ms:
**/
bool isNumber4(const char* s) {
  State *pstate = get_dfa_start();
  while (pstate != ABT && pstate != ACC) {
    pstate = pstate->next[(int)*s++];
  }
  return pstate == ACC;
}

/**
   0ms :
**/
bool is_decimal(char* s, char** ret) {
  bool has_digit = false;

  if (*s == '+' || *s == '-')
    s++;
  if (*s != '.') {
    if (*s < '0' || *s > '9')
      return false;
    while (*s >= '0' && *s <= '9') {
      has_digit = true;
      s++;
    }
    if (*s != '.' && *s != 'e' && *s != 'E' && *s != '\0')
      return false;
  }
  if (*s == '.')
    s++;
  while (*s >= '0' && *s <= '9') {
    has_digit = true;
    s++;
  }
  *ret = s;
  return has_digit;
}

bool skip_integer(char* s, char** ret) {
  if (*s == '+' || *s == '-')
    s++;
  char* comp = s;
  while (*s >= '0' && *s <= '9')
    s++;
  if (s == comp)
    return false;
  *ret = s;
  return true;
}

bool isNumber(char* s) {
  if (!is_decimal(s, &s)) return false;
  if (!*s) return true;
  if (*s != 'e' && *s != 'E') return false;
  s++;
  if (!skip_integer(s, &s)) return false;
  if (*s) return false;
  return true;
}

int main () {
  int ret = 0;
  char *s = ".1";

  ret = isNumber4(s);
  debug("Output = %d", ret);
  return 0;
}

/**
   => ./a.out
   [main] L=152 :Output = 1
**/
