/***
    Smallest substring with each letter occurring both in
    uppercase and lowercase.

    Given a string S of length N, the task is to find the
    smallest balanced substring in S. If no such substring
    is present, print -1.

    A string is balanced if every letter in the string appears
    in both uppercase and lowercase, i.e “AabB” is a balanced
    string whereas “Ab” is not a balanced string.

    Input: S = “azABaabba”
    Output: ABaab
    Explanation:
    Substring {S[2], …, S[6]} (0-based indexing) is the smallest
    substring which is balanced.

    Input: S = “Technocat”
    Output: -1

    Staus: Pending, its in CPP
    Date: 26 Sept 2021.
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

// Function to check if the current
// string is balanced or not
bool balanced(int small[], int caps[]) {
  // For every character, check if
  // there exists uppercase as well
  // as lowercase characters
  for (int i = 0; i < 26; i++) {
    if (small[i] != 0 && (caps[i] == 0))
      return 0;
    else if ((small[i] == 0) && (caps[i] != 0))
      return 0;
  }
  return 1;
}

// Function to find smallest length substring
// in the given string which is balanced
void smallestBalancedSubstring(char* s) {
  // Store frequency of
  // lowercase characters
  int small[26];

  // Stores frequency of
  // uppercase characters
  int caps[26];

  memset(small, 0, sizeof(small));
  memset(caps, 0, sizeof(caps));

  // Count frequency of characters
  for (int i = 0; i < strlen(s); i++) {
    if (s[i] >= 65 && s[i] <= 90)
      caps[s[i] - 'A']++;
    else
      small[s[i] - 'a']++;
  }

  // Mark those characters which
  // are not present in both
  // lowercase and uppercase
  unordered_map<char, int> mp;
  for (int i = 0; i < 26; i++) {

    if (small[i] && !caps[i])
      mp[char(i + 'a')] = 1;

    else if (caps[i] && !small[i])
      mp[char(i + 'A')] = 1;
  }

  // Initialize the frequencies
  // back to 0
  memset(small, 0, sizeof(small));
  memset(caps, 0, sizeof(caps));

  // Marks the start and
  // end of current substring
  int i = 0, st = 0;

  // Marks the start and end
  // of required substring
  int start = -1, end = -1;

  // Stores the length of
  // smallest balanced substring
  int minm = INT_MAX;

  while (i < strlen(s)) {
    if (mp[s[i]]) {

      // Remove all characters
      // obtained so far
      while (st < i) {

	if (s[st] >= 65 && s[st] <= 90)
	  caps[s[st] - 'A']--;
	else
	  small[s[st] - 'a']--;

	st++;
      }
      i += 1;
      st = i;
    }
    else {

      if (s[i] >= 65 && s[i] <= 90)
	caps[s[i] - 'A']++;
      else
	small[s[i] - 'a']++;

      // Remove extra characters from
      // front of the current substring
      while (1) {

	if (s[st] >= 65 && s[st] <= 90
	    && caps[s[st] - 'A'] > 1) {
	  caps[s[st] - 'A']--;
	  st++;
	}
	else if (s[st] >= 97 && s[st] <= 122
		 && small[s[st] - 'a'] > 1) {
	  small[s[st] - 'a']--;
	  st++;
	}
	else
	  break;
      }

      // If substring (st, i) is balanced
      if (balanced(small, caps)) {

	if (minm > (i - st + 1)) {

	  minm = i - st + 1;
	  start = st;
	  end = i;
	}
      }
      i += 1;
    }
  }

  // No balanced substring
  if (start == -1 || end == -1)
    debug("cout = -1");

  // Store answer string
  else {

    char ans[] = "";
    for (int i = start; i <= end; i++)
      ans += s[i];
    debug("ans =%d", ans);
  }
}

int main (int argc, char **argv) {
  int ret = 0;
  char s[] = "azABaabba";

  smallestBalancedSubstring(s);
  debug("Output = %d", ret);

  return 0;
}

/**

 **/
