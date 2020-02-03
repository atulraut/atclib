/*
 Problem :Given a word, you need to judge whether the usage of capitals in it is right or not.
We define the usage of capitals in a word to be right when one of the following cases holds:
    All letters in this word are capitals, like "USA".
    All letters in this word are not capitals, like "leetcode".
    Only the first letter in this word is capital, like "Google".
Otherwise, we define that this word doesn't use capitals in a right way.
 Example 1:
  Input: "USA"
  Output: True
 Example 2:
  Input: "FlaG"
  Output: False
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/*Need Fix*/
bool detectCapitalUse(char * word){
  char *ptr1 = word;
  char *ptr2 = word + strlen(word) -1;

  if (strlen(word) ==1 || strlen(word) == 0)
    return 1;

  while (*ptr2>*ptr1) {
    if (!isalpha(*ptr2))
      continue;
    if (!isalpha(*ptr1))
      continue;
    if (tolower(*ptr1) != tolower(*ptr2))
      return -1;
    ptr1++; ptr2--;
  }
  return 1;
}

int main() {
  char word[] = "RauSji";
  bool ret = detectCapitalUse(word);
  printf ("I/O = %d \n", ret);
  return 0;
}
