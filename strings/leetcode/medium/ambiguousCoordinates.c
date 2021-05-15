/***
    Medium: Ambiguous Coordinates
    https://leetcode.com/problems/ambiguous-coordinates/

    We had some 2-dimensional coordinates, like "(1, 3)" or "(2, 0.5)".
    Then, we removed all commas, decimal points, and spaces, and
    ended up with the string s.  Return a list of strings representing
    all possibilities for what our original coordinates could have been.

    Our original representation never had extraneous zeroes, so we never
    started with numbers like "00", "0.0", "0.00", "1.0", "001", "00.01",
    or any other number that can be represented with less digits.  Also,
    a decimal point within a number never occurs without at least one
    digit occuring before it, so we never started with numbers like ".1".

    The final answer list can be returned in any order.  Also note that
    all coordinates in the final answer have exactly one space between
    them (occurring after the comma.)

    Example 1:
    Input: s = "(123)"
    Output: ["(1, 23)", "(12, 3)", "(1.2, 3)", "(1, 2.3)"]

    Example 2:
    Input: s = "(00011)"
    Output:  ["(0.001, 1)", "(0, 0.011)"]
    Explanation:
    0.0, 00, 0001 or 00.01 are not allowed.

    Example 3:
    Input: s = "(0123)"
    Output: ["(0, 123)", "(0, 12.3)", "(0, 1.23)", "(0.1, 23)", "(0.1, 2.3)", "(0.12, 3)"]

    Example 4:
    Input: s = "(100)"
    Output: [(10, 0)]
    Explanation:
    1.0 is not allowed.

    Note:
    4 <= s.length <= 12.
    s[0] = "(", s[s.length - 1] = ")", and the other elements in s are digits.

    Date: 14 May 2021.
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

void addResult(char *str1, char *str2, char ***ret, int *retSize) {
    *ret = realloc(*ret, sizeof(char *)*(*retSize + 1));
    (*ret)[*retSize] = calloc(20, sizeof(char));
    sprintf((*ret)[*retSize], "(%s, %s)", str1, str2);
    *retSize += 1;
}

void decimalPointsHandler(char *s1, char *s2, char *xStr, char ***ret, int *retSize) {
    // Use xStr pointer to know which string(x-axis or y-axis) we need to process
    char *curStr = (xStr == NULL ? s1 : s2);
    int len = strlen(curStr);

    // non decimal point case
    if ((*curStr == '0' && len == 1) || *curStr != '0') {
        if (xStr == NULL)
            decimalPointsHandler(s1, s2, curStr, ret, retSize);
        else
            addResult(xStr, curStr, ret, retSize);
    }
    // use decimal point case
    char *tmp = calloc(len+2, sizeof(char));
    tmp[0] = curStr[0];

    if (curStr[len-1] != '0') {
        for (int i = 1; i < len; i++) {
            tmp[i] = '.';
            strcpy(&(tmp[i+1]), &(curStr[i]));
            if ((tmp[0] == '0' && tmp[1] == '.') || (tmp[0] != '0'))
            {
                if (xStr == NULL)
                    decimalPointsHandler(s1, s2, tmp, ret, retSize);
                else
                    addResult(xStr, tmp, ret, retSize);
            }
            tmp[i] = curStr[i];
        }
    }
    free(tmp);
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** ambiguousCoordinates(char * S, int* returnSize) {
    int len =strlen(S);
    S[len-1] = 0;

    char **ret = malloc(sizeof(char *));
    *returnSize = 0;

    char *coordinate = calloc(len+1, sizeof(char));
    strcpy(coordinate, S);
    // handle commas
    for (int i = 1; i < len-2; i++) {
        coordinate[i+1] = 0;
        // Handle decimal point
        decimalPointsHandler(&(coordinate[1]), &(S[i+1]), NULL, &ret, returnSize);
        coordinate[i+1] = S[i+1];
    }
    free(coordinate);
    return ret;
}

int main () {
  int ret = 0;
  char s[] = "(123)";
  int returnSize;

  char** output = ambiguousCoordinates(s, &returnSize);

  for (int i=0; i<returnSize; ++i)
    debug("Output = %s", output[i]);

  return 0;
}

/**
   => ./a.out
   [main] L=132 :Output = (1, 23)
   [main] L=132 :Output = (1, 2.3)
   [main] L=132 :Output = (12, 3)
   [main] L=132 :Output = (1.2, 3)
**/
