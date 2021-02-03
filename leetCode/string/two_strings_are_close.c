/***
    Determine if Two Strings Are Close Using C.
    https://leetcode.com/problems/determine-if-two-strings-are-close/

    Two strings are considered close if you can attain one from the other
    using the following operations:

    Operation 1: Swap any two existing characters.
    For example, abcde -> aecdb
    Operation 2: Transform every occurrence of one existing character into
    another existing character, and do the same with the other character.
    For example, aacabb -> bbcbaa (all a's turn into b's, and all b's turn into a's)

    You can use the operations on either string as many times as necessary.

    Given two strings, word1 and word2, return true if word1 and word2 are close,
    and false otherwise.

    Example 1:
    Input: word1 = "abc", word2 = "bca"
    Output: true
    Explanation: You can attain word2 from word1 in 2 operations.
    Apply Operation 1: "abc" -> "acb"
    Apply Operation 1: "acb" -> "bca"

    Example 2:
    Input: word1 = "a", word2 = "aa"
    Output: false
    Explanation: It is impossible to attain word2 from word1, or vice versa,
    in any number of operations.

    Example 3:
    Input: word1 = "cabbba", word2 = "abbccc"
    Output: true
    Explanation: You can attain word2 from word1 in 3 operations.
    Apply Operation 1: "cabbba" -> "caabbb"
    Apply Operation 2: "caabbb" -> "baaccc"
    Apply Operation 2: "baaccc" -> "abbccc"

    Example 4:
    Input: word1 = "cabbba", word2 = "aabbss"
    Output: false
    Explanation: It is impossible to attain word2 from word1, or vice versa,
    in any amount of operations.

    Constraints:
    1 <= word1.length, word2.length <= 105
    word1 and word2 contain only lowercase English letters.

     Date : 1-31-21
    San Diego, CA
*/

#include <stdio.h>
#include "../../at_lib.h"

/***
    https://www.youtube.com/watch?v=ROmxkLMc0ow
    8ms
*/
bool closeStrings(char * word1, char * word2){
  int i;
  int word1_count[26];
  int word2_count[26];

  for(i=0; i<26; i++) {
    word1_count[i]=0;
    word2_count[i]=0;
  }

  int word1_length = strlen(word1);
  for(i=0; i<word1_length; i++)
    word1_count[word1[i]-'a']+=1;

  int word2_length=strlen(word2);
  for(i=0; i<word2_length; i++)
    word2_count[word2[i]-'a']+=1;

  // Step 1:
  for(i=0; i<26; i++) {
    if(word1_count[i] !=0 && word2_count[i] == 0)
      return false;
    if(word2_count[i] !=0 && word1_count[i] == 0)
      return false;
  }
  // Step 2:
  for(i=0; i<26; i++)
    {
      bool find=false;
      for(int j=0; j<26; j++) {
	if(word1_count[i] == word2_count[j]) {
	  word2_count[j] = 0;
	  find=true;
	  break;
	}
      }
      if(find==false)
	return false;
    }
  return true;
}

int m_sort (char *str, int sz) {
  char temp;
  int i, j;
  for (i = 0; i < sz-1; i++) {
    for (j = i+1; j < sz; j++) {
      if (str[i] > str[j]) {
	temp   = str[i];
	str[i] = str[j];
	str[j] = temp;
      }
    }
  }
  printf("The sorted string is : %s", str);
  return 0;
}

/***
    40ms
 */
bool closeStrings_atclib(char * word1, char * word2){
  int i;
  char word1Map[26] = {0};
  char word2Map[26] = {0};
  int word1Bit = 0;
  int word2Bit = 0;

  int len1 = strlen(word1);
  int len2 = strlen(word2);
  if(len1 < 0 || len2 < 0)
    return false;
  if (len1 != len2)
    return false;

  for(i=0; i<len1; ++i) {
    word1Map[word1[i] -'a']++;
    printf ("[%s] Bit to Set : %d word1Bit = %d \t", __func__, (word1[i] - 'a'), word1Bit);
    word1Bit = word1Bit | (1 << (word1[i] - 'a')); // Set Bit
    printf ("[%s] word1Bit    : %d \n", __func__, word1Bit);
  }

   for(i=0; i<len2; ++i) {
    word2Map[word2[i] -'a']++;
    word2Bit = word2Bit | (1 << (word2[i] - 'a')); // Set Bit
  }

  if (word1Bit != word2Bit)
    return false;

  //sort(word1Map.begin(), word1Map.end());
  //sort(word2Map.begin(), word2Map.end());
  m_sort(word1Map, 26);
  m_sort(word2Map, 26);

  for (int i = 0; i < 26; i++) {
    printf ("==> w1 = %c w2 = %c \n", word1Map[i], word2Map[i]);
    if (word1Map[i] != word2Map[i])
      return false;
  }
  return true;
}

int main () {
  char word1[] = "abc";
  char word2[] = "bca";

  bool ret = closeStrings_atclib(word1, word2);

  printf ("[%s] result = %d \n", __func__, ret);
}

/***
    Using Bitwise Operation and Frequency Array Map

    The previous approach iterates over the map of size 262626 to check if the
    word1 and word2 have the same characters (Condition 1). However, there is
    another efficient way to implement this.

    We just want a way to know if a character exists in a word or not. Instead of
    iterating over a frequency map to check this condition, we could simply store
    this information in a single integer. This could be done by making use of Bitwise Operators.

    We could use a integer wordBit, where each bit in the wordBit
    Bit stores the information about each of the 26 characters (a-z). The rightmost bit
    represents the character a, the next left bit would represent character b and so on.

    A character exists in the word if it's a corresponding bit is set to 1.
    The following figure illustrates this idea.
    To set a bit represented by a character we must use the bitwise OR operator. Example,

    wordBit ∣ wordBit << 2, sets the 2nd bit, wordBit=100

    wordBit ∣ wordBit << 5, sets the 5th bit, wordBit=100100.

    It must be noted that this approach works because the size of the integer is
    323232 bits (In Java and C++) and we only need to 262626 bits to store our information.

    Algorithm :
    Build arrays word1Map and word2Map of size 26 to store the frequencies of each
    character (a-z) as in Approach 2.

    For the first condition, we must check if the characters in word1 and word2 are
    the same. We use word1Bit and word2Bit to store the bit information of word1 and
    word2 respectively. While building the frequency map, we update the word bits as
    well to mark the occurrence of a character.

    For the second condition, we could simply sort the array in increasing order and return
    true if arrays are equal, otherwise return false.


    Complexity Analysis
    Time Complexity : O(n), where nnn is the length of the word.
    The complexity is similar to Approach 2.
    Space Complexity: O(1), as we use constant extra space, frequency
    map of size 262626 and word bits of type integer.
*/

/***
=> ./a.out
[closeStrings_atclib] Bit to Set : 0 word1Bit = 0 	[closeStrings_atclib] word1Bit    : 1
[closeStrings_atclib] Bit to Set : 1 word1Bit = 1 	[closeStrings_atclib] word1Bit    : 3
[closeStrings_atclib] Bit to Set : 2 word1Bit = 3 	[closeStrings_atclib] word1Bit    : 7
 */
