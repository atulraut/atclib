/***
    Medium: 1048. Longest String Chain
    https://leetcode.com/problems/longest-string-chain/

    Given a list of words, each word consists of English lowercase letters.

    Let's say word1 is a predecessor of word2 if and only if we can
    add exactly one letter anywhere in word1 to make it equal to word2.
    For example, "abc" is a predecessor of "abac".

    A word chain is a sequence of words [word_1, word_2, ..., word_k]
    with k >= 1, where word_1 is a predecessor of word_2, word_2 is a
    predecessor of word_3, and so on.

    Return the longest possible length of a word chain with words chosen
    from the given list of words.

    Input: words = ["a","b","ba","bca","bda","bdca"]
    Output: 4
    Explanation: One of the longest word chain is "a","ba","bda","bdca".

    Input: words = ["xbc","pcxbcf","xb","cxbc","pcxbc"]
    Output: 5

    Constraints:
    1 <= words.length <= 1000
    1 <= words[i].length <= 16
    words[i] only consists of English lowercase letters.

    Date: 17 May 2021
    San Diego, CA.
    Status : Pending
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


int dfs(unordered_set<string> &words, unordered_map<string, int> &memo, string currentWord) {
  // If the word is encountered previously we just return its value present in the map (memoization).
  if (memo.find(currentWord) != memo.end()) {
    return memo[currentWord];
  }
  // This stores the maximum length of word sequence possible with the 'currentWord' as the
  int maxLength = 1;

  // creating all possible strings taking out one character at a time from the `currentWord`
  for (int i = 0; i < currentWord.length(); i++) {
    string newWord = currentWord.substr(0, i) + currentWord.substr(i + 1);
    // If the new word formed is present in the list, we do a dfs search with this newWord.
    if (words.find(newWord) != words.end()) {
      int currentLength = 1 + dfs(words, memo, newWord);
      maxLength = max(maxLength, currentLength);
    }
  }
  memo[currentWord] = maxLength;

  return maxLength;
}


int longestStrChain(vector<string> &words) {
  unordered_map<string, int> memo;
  unordered_set<string> wordsPresent;
  for (const string &word : words) {
    wordsPresent.insert(word);
  }
  int ans = 0;
  for (const string &word : words) {
    ans = max(ans, dfs(wordsPresent, memo, word));
  }
  return ans;
}


int longestStrChain1(char ** words, int wordsSize){
  int ret = 0;
  return ret;
}

int main () {
  int ret = 0;
  char *words[] = {"a","b","ba","bca","bda","bdca"};
  int wordsSize = sizeof(words)/sizeof(words[0]);
  debug ("wordsSize = %d", wordsSize);

  ret = longestStrChain(words, wordsSize);
  debug("Output = %d", ret);
  return 0;
}

/**

 **/
