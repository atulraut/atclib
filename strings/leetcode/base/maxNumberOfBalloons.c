/***
    Maximum Number of Balloons

    Given a string text, you want to use the characters of text
    to form as many instances of the word "balloon" as possible.

    You can use each character in text at most once. Return the
    maximum number of instances that can be formed.

    Input: text = "nlaebolko"
    Output: 1

    Input: text = "loonbalxballpoon"
    Output: 2

    Input: text = "leetcode"
    Output: 0

    Constraints:
    1 <= text.length <= 104
    text consists of lower case English letters only.

    https://leetcode.com/problems/maximum-number-of-balloons/

    Date: 9/13/2021
    Fair Oaks, CA.
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

#define min(x,y) (((x) < (y)) ? (x) : (y))

/**
   Implementation
   1] Store the frequency of all the five characters in the
   given string text.
   2] Find the potential of each of the five characters.
   3] Return the minimum potential of the five characters.
**/
int maxNumberOfBalloons__(char* text){
  int bCount = 0, aCount = 0, lCount = 0, oCount = 0, nCount = 0;

  // Count the frequencey of all the five characters
  for (int i = 0; i < strlen(text); i++) {
    if (text[i] == 'b') {
      bCount++;
    } else if (text[i] == 'a') {
      aCount++;
    } else if (text[i] == 'l') {
      lCount++;
    } else if (text[i] == 'o') {
      oCount++;
    } else if (text[i] == 'n') {
      nCount++;
    }
  }

  // Find the potential of each character.
  // Except for 'l' and 'o' the potential is equal to the frequency.
  lCount = lCount / 2;
  oCount = oCount / 2;

  // Find the bottleneck.
  return min(bCount, min(aCount, min(lCount, min(oCount, nCount))));
}
/**
   Complexity Analysis
   Here N is equal to the length of text.
   Time complexity: O(N)
   We iterate over all the characters of string text which
   requires NN operations.
   Space complexity: O(1)
   All we need is the 55 variables to store the frequency of
   characters. Hence the space complexity is constant.
**/

/**
   Algorithm

   1] Store the frequency of all the characters in text in freqInText
   and the frequency of all the characters in pattern in freqInPattern.
   2] Find the potential of all the lowercase English letters.
   The potential will be equal to its frequency in text divided by its
   frequency in pattern.
   3] Return the minimum potential of a character.
**/
int findMaxNumberofPattern(char* text, char* pattern) {
  int n = strlen(text);
  int m = strlen(pattern);
  int answer = INT_MAX;
  int* freqInText = (int *)calloc(26, sizeof(int));
  int* freqInPattern = (int *)calloc(26, sizeof(int));

  // Frequency of characters in text.
  for (int i = 0; i < n; i++) {
    freqInText[text[i] - 'a']++;
  }
  // Frequency of characters in pattern.
  for (int i = 0; i < m; i++) {
    freqInPattern[pattern[i] - 'a']++;
  }

  // Compare the maximum string that can be produced
  // considering one character at a time.
  for (int i = 0; i < 26; i++) {
    // Do not divide by zero.
    if (freqInPattern[i] > 0) {
      answer = min(answer, freqInText[i] / freqInPattern[i]);
    }
  }

  free(freqInText);
  free(freqInPattern);
  freqInText = NULL;
  freqInPattern = NULL;

  return answer;
}

int maxNumberOfBalloons(char* text) {
  // Any string made up of lowercase English letters.
  char pattern[] = "balloon";
  return findMaxNumberofPattern(text, pattern);
}

int main (int argc, char **argv) {
  int ret = 0;

  debug("Output = %d", ret);
  return 0;
}

/**
   Complexity Analysis

   Here N equals the length of text, M equals the length of pattern,
   and K equals the maximum possible number of distinct letters in pattern.

   Time complexity: O(N + M)
   We traverse over text having length N and over the string pattern of
   length M to find the frequency of each character in each string.
   Lastly, we traverse over the frequency arrays of length KK to find
   the bottleneck character. Since this problem only uses lowercase
   English letters, K is fixed at 2626. Hence, we can consider
   the space complexity to be O(N + M).

   Space complexity: O(1)
   The integer arrays used to store the frequency of characters in text
   and pattern each require O(K) space. Since this problem only uses
   lowercase English letters, K is fixed at 26. Hence, we can consider
   the space complexity to be constant.
**/
