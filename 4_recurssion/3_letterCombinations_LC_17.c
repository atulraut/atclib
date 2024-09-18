/***

    https://leetcode.com/problems/letter-combinations-of-a-phone-number/submissions/
    Check -
    https://github.com/atulraut/interviewKickstart/blob/main/4_recurssion/8_Coding_Week_5_Practice_Problems/1_Words_From_Phone_Number_IK_Solution.c

    Medium : 17. Letter Combinations of a Phone Number
    Given a string containing digits from 2-9 inclusive, return all
    possible letter combinations that the number could represent.
    Return the answer in any order.

    A mapping of digit to letters (just like on the telephone buttons) is
    given below. Note that 1 does not map to any letters.

    Input: digits = "23"
    Output: ["ad","ae","af","bd","be","bf","cd","ce","cf"]

    Input: digits = ""
    Output: []

    Input: digits = "2"
    Output: ["a","b","c"]

    Constraints:
    0 <= digits.length <= 4
    digits[i] is a digit in the range ['2', '9'].

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Tue 13 Aug 2024 07:05:04 AM PDT
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

/*  SD ,                                                  PS        */
void ph_helper(char** output, char** ph_map, char* in_digits, int* retSz, char* slate, int idx) {

  // base case:
  if (in_digits[idx] == '\0') {
    char* rst_seq = (char *) malloc( (idx+1) * sizeof(char) ); // size including '\0'
    strncpy(rst_seq, slate, idx+1);
    output[(*retSz)++] = rst_seq;
    return;
  }

  // recursive case:
  int map_idx = in_digits[idx] - '0';

  for (char* c = &ph_map[map_idx][0]; *c != '\0'; ++c) {
    slate[idx] = *c;
    debug ("map_index->[%d] *c->[%d]  *c->[%c]", idx, *c, *c);
    ph_helper(output, ph_map, in_digits, retSz, slate, idx+1);
  }
}

char** letterCombinations(char* in_digits, int* returnSize) {
  char* pn_map[10] = {"", "", "abc", "def",
		      "ghi", "jkl", "mno", "pqrs",
		      "tuv", "wxyz"
  };
  *returnSize = 0;
  int len = strlen(in_digits);
  if (!len)
    return NULL;

  char** output = (char **)malloc(pow(4, len) * sizeof(char *)); // at most 4^len possible strings
  char slate[len+1];
  slate[len] = '\0';

  ph_helper(output, pn_map, in_digits, returnSize, slate, 0);
  return output;
}

void test() {
  char input_digits[] = "23";
  int returnSize;
  char **ret = letterCombinations(input_digits, &returnSize);

  debug ("Reached!");

  for (int i=0; i<returnSize; ++i)
    debug("Combinations : %s", ret[i]);
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**
   => ./a.out
   L=[62] [ph_helper] :| map_index->[0] *c->[97]  *c->[a]
   L=[62] [ph_helper] :| map_index->[1] *c->[100]  *c->[d]
   L=[62] [ph_helper] :| map_index->[1] *c->[101]  *c->[e]
   L=[62] [ph_helper] :| map_index->[1] *c->[102]  *c->[f]
   L=[62] [ph_helper] :| map_index->[0] *c->[98]  *c->[b]
   L=[62] [ph_helper] :| map_index->[1] *c->[100]  *c->[d]
   L=[62] [ph_helper] :| map_index->[1] *c->[101]  *c->[e]
   L=[62] [ph_helper] :| map_index->[1] *c->[102]  *c->[f]
   L=[62] [ph_helper] :| map_index->[0] *c->[99]  *c->[c]
   L=[62] [ph_helper] :| map_index->[1] *c->[100]  *c->[d]
   L=[62] [ph_helper] :| map_index->[1] *c->[101]  *c->[e]
   L=[62] [ph_helper] :| map_index->[1] *c->[102]  *c->[f]
   L=[90] [test] :| Reached!
   L=[93] [test] :| Combinations : ad
   L=[93] [test] :| Combinations : ae
   L=[93] [test] :| Combinations : af
   L=[93] [test] :| Combinations : bd
   L=[93] [test] :| Combinations : be
   L=[93] [test] :| Combinations : bf
   L=[93] [test] :| Combinations : cd
   L=[93] [test] :| Combinations : ce
   L=[93] [test] :| Combinations : cf
**/
