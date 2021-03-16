/***
    Single-Row Keyboard :
    https://leetcode.com/problems/single-row-keyboard/
    There is a special keyboard with all keys in a single row.

    Given a string keyboard of length 26 indicating the layout of the keyboard
    (indexed from 0 to 25), initially your finger is at index 0. To type a
    character, you have to move your finger to the index of the desired character.
    The time taken to move your finger from index i to index j is |i - j|.

    You want to type a string word. Write a function to calculate how much
    time it takes to type it with one finger.

    Example 1:

    Input: keyboard = "abcdefghijklmnopqrstuvwxyz", word = "cba"
    Output: 4
    Explanation: The index moves from 0 to 2 to write 'c' then to 1 to
    write 'b' then to 0 again to write 'a'.
    Total time = 2 + 1 + 1 = 4.

    Example 2:

    Input: keyboard = "pqrstuvwxyzabcdefghijklmno", word = "leetcode"
    Output: 73

    Constraints:

    keyboard.length == 26
    keyboard contains each English lowercase letter exactly once in some order.
    1 <= word.length <= 10^4
    word[i] is an English lowercase letter.

    Author : Rauji(Atul) Raut
    Date : 13 March 2021, San Diego, CA
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>  /* malloc */

#define debug(str, args...) printf("[%s] L=%d :"str"\n", __func__, __LINE__, ##args)
#define NHASH 26

enum {
  LOOKUP = 0,
  INSERT = 1
};

struct nameval {
  char c;
  int value;
  struct nameval *next;
};

struct nameval* systab[NHASH];

/* Hash: Compute hash value of string */
int get_hash(char c) {
  int h = c % NHASH;
  return h;
}

/* lookup: Find name in symtab, with optional create */
struct nameval* lookup (char c, int val, int isCreate) {
  struct nameval* sys;
  int h = get_hash(c);

  /* Lookup into Hash Table */
  for(sys=systab[h]; sys != NULL; sys=sys->next) {
    if (sys->c == c)
      return sys;
  }

  if (isCreate) {
    struct nameval* nn = (struct nameval*)malloc(sizeof(struct nameval) + 1);
    if (NULL == nn)
      return NULL;
    nn->c = c;
    nn->value = val;
    nn->next = systab[h]; /* Hash Table Next Pointer */
    systab[h] = nn;
  }
  return sys;
}

/**
   LeetCode : Atul Implemented, not accepted by LeetCode
 **/
int calculateTime2(char* keyboard, char* word){
  int lenk = strlen(keyboard);
  int lenw = strlen(word);
  struct nameval* sys;
  int sum = 0, i;
  int prev = 0;

  debug ("lenk=%d lenw=%d", lenk, lenw);

  /* First Insert keyboard Char, it may be in any order but not > 26 */
  for (i=0; i<=lenk; i++)
    lookup (keyboard[i], i, INSERT);

  /* Loop Word in keyboard hash table & add them to get result. */
  for (i=0; i<lenw; i++) {
    sys = lookup (word[i], i, LOOKUP);
    debug("prev = %d val = %d diff=%d ", prev, sys->value, (prev - sys->value));
    sum += abs(prev - sys->value);
    debug ("Sum = %d word[%d]=%c", sum, i, word[i]);
    prev = sys->value;
  }
  debug ("sum = %d", sum);
  return sum;
}

/**
   LeetCode Accepted : 16MS
 **/
int calculateTime(char* keyboard, char* word) {
  int keyIndices[26] = {-1};

  // Get the index for each key.
  for (int i = 0; i < strlen(keyboard); i++)
    keyIndices[keyboard[i] - 'a'] = i;

  // Initialize previous index as starting index = 0.
  int prev = 0;
  int result = 0;

  // Calculate the total time.
  for (int i=0; i<strlen(word); i++) {
    // Add the distance from previous index
    // to current letter's index to the result.
    result += abs(prev - keyIndices[word[i] - 'a']);

    // Update the previous index to current index for next iteration.
    prev = keyIndices[word[i]  - 'a'];
  }
  return result;
}

int main () {
  //char keyboard1[] = "abcdefghijklmnopqrstuvwxyz";
  //char word1[] = "cba";
  char keyboard[] = "pqrstuvwxyzabcdefghijklmno";
  char word[] = "leetcode";
  int op = calculateTime(keyboard, word);
  debug ("op = %d", op);
}

/**
   Complexity Analysis

   Time complexity: O(n). Where nnn is the length of word, since we need to
   traverse the word. An additional constant of O(26)=O(1) = O(1) is
   needed to iterate through keyboard.

   Space complexity: O(1). The algorithm requires constant space to store
   indices for 26 letters.
**/
