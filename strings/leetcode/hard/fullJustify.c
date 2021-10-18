/***
    https://leetcode.com/problems/text-justification/
    Text Justification

    Given an array of strings words and a width maxWidth,
    format the text such that each line has exactly
    maxWidth characters and is fully (left and right) justified.

    You should pack your words in a greedy approach; that is,
    pack as many words as you can in each line. Pad extra
    spaces ' ' when necessary so that each line has exactly
    maxWidth characters.

    Extra spaces between words should be distributed as evenly
    as possible. If the number of spaces on a line does not
    divide evenly between words, the empty slots on the left
    will be assigned more spaces than the slots on the right.

    For the last line of text, it should be left-justified
    and no extra space is inserted between words.

    Note:

    A word is defined as a character sequence consisting
    of non-space characters only.
    Each word's length is guaranteed to be greater than 0
    and not exceed maxWidth.
    The input array words contains at least one word.

    Input: words = ["This", "is", "an", "example", "of",
    "text", "justification."], maxWidth = 16
    Output:
    [
    "This    is    an",
    "example  of text",
    "justification.  "
    ]

    Input: words = ["What","must","be","acknowledgment","shall","be"], maxWidth = 16
    Output:
    [
    "What   must   be",
    "acknowledgment  ",
    "shall be        "
    ]
    Explanation: Note that the last line is "shall be    " instead of
    "shall     be", because the last line must be left-justified
    instead of fully-justified.
    Note that the second line is also left-justified becase it contains
    only one word.

    Input: words = ["Science","is","what","we","understand","well",
    "enough","to","explain","to","a","computer.","Art","is",
    "everything","else","we","do"], maxWidth = 20
    Output:
    [
    "Science  is  what we",
    "understand      well",
    "enough to explain to",
    "a  computer.  Art is",
    "everything  else  we",
    "do                  "
    ]

    Constraints:
    1 <= words.length <= 300
    1 <= words[i].length <= 20
    words[i] consists of only English letters and symbols.
    1 <= maxWidth <= 100
    words[i].length <= maxWidth


    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings *.c -lm

    Date: 18 Oct 2021
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

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
#define MAX_WORDS 300
#define MAX_WIDTH 100
#define MAX_LINES MAX_WORDS

/**
 * 8ms
 */
char** fullJustify(char** words, int wordsSize, int maxWidth, int* returnSize) {
  int lens[MAX_WORDS];
  static char* lines[MAX_LINES];
  char**c = &lines[0];

  // first cache word length
  int i;
  for (i=0; i<wordsSize; ++i) {
    lens[i] = strlen(words[i]);
  }

  char* line;
  int j, space, offset;
  int start, end, num, q, r, ln, space_needed;

  // loop through entire word list
  for(i=ln=start=end=0, space=maxWidth; i<wordsSize;++i) {
    space_needed = lens[i] + ((i==start)? 0 : 1);
    // if current word fits
    if (space >= space_needed) {
      end = i; // advance end to include current word
      space -= space_needed;
      if ((space) && (i!= (wordsSize-1))) {
	continue;
      }
    } else {
      // exclude current word if there isn't enough space for it
      end = i-1;
    }
    // distribute space across words
    if ((start == end)||(end==(wordsSize-1))) {
      q = r = 0;
    } else {
      num = end - start + 1;
      q = space / (num - 1);
      r = space % (num - 1);
    }
    // clear and terminate line
    line = malloc(maxWidth+1);
    memset(line, 0x20, maxWidth);
    line[maxWidth] = 0;
    lines[ln++] = line;
    offset = 0;
    for (j=start; j<=end; ++j) {
      memcpy(&line[offset], words[j], lens[j]);
      offset += lens[j] + 1 + q;
      if (r) {
	++offset;
	--r;
      }
    }
    printf("\n");
    if (i==wordsSize){
      break;
    }
    // start a blank line on the word after end
    start = end +1;
    end = 0;
    i= start -1;
    space = maxWidth;
  }

  *returnSize = ln;
  return c;
}

int getLen(char* s){
  int len = 0;
  while (s[len]) len++;
  return len;
}

char *centerJustify(char **words, int wordsSize, int *len, int startIndex, int endIndex, int maxWidth){
  int width = 0;
  for (int i=startIndex; i<=endIndex; i++) width += len[i];
  int totalSpace = maxWidth - width;
  int space = totalSpace / (endIndex - startIndex);
  int bonusSpace = totalSpace % (endIndex - startIndex);
  char *line = (char*)malloc(sizeof(char)*(maxWidth + 1));
  int index = 0;
  for (int i=startIndex; i<=endIndex; i++){
    // add space characters from the second word.
    if (i > startIndex){
      for (int j=0; j<space; j++) line[index++] = ' ';
      if (bonusSpace-- > 0) line[index++] = ' ';
    }
    // add the word to the line
    for (int j=0; j<len[i]; j++){
      line[index++] = words[i][j];
    }
  }
  line[index] = 0;

  return line;
}

char *leftJustify(char **words, int wordsSize, int *len, int startIndex, int endIndex, int maxWidth){
  char *line = (char*)malloc(sizeof(char)*(maxWidth + 1));
  int index = 0;
  for (int i=startIndex; i<=endIndex; i++){
    // add space characters from the second word.
    if (i > startIndex) line[index++] = ' ';
    // add the word to the line
    for (int j=0; j<len[i]; j++){
      line[index++] = words[i][j];
    }
  }
  for(int i = index; i<maxWidth; i++) line[index++] = ' ';
  line[index] = 0;

  return line;
}

/**
 * 0ms
 */
char** fullJustify2(char** words, int wordsSize, int maxWidth, int* returnSize) {
  if (wordsSize == 0){
    // return a line with all space charaters
    char **out = (char**)malloc(sizeof(char*));
    out[0] = (char*)malloc(sizeof(char) * maxWidth + 1);
    int index = 0;
    for (int i=0; i<maxWidth; i++) out[0][index++] = ' ';
    out[0][index] = 0;
    *returnSize = 1;
    return out;
  }
  int *len = (int*)calloc(wordsSize, sizeof(int));
  for (int i=0; i<wordsSize; i++){
    len[i] = getLen(words[i]);
  }

  int *startIndex = (int*)malloc(sizeof(int) * wordsSize);
  int startLen = 0;
  int width = 0, newWidth;
  startIndex[startLen++] = 0;
  for (int i=0; i<wordsSize; i++){
    newWidth = width + len[i];
    if (width > 0) newWidth++;

    if (newWidth > maxWidth){
      startIndex[startLen++] = i;
      width = len[i];
    }
    else width = newWidth;
  }

  char **out = (char**)malloc(sizeof(char*) * startLen);
  int index = 0;
  for (int i=0; i<startLen - 1; i++){
    if (startIndex[i + 1] - startIndex[i] >= 2)
      out[index++] = centerJustify(words, wordsSize, len, startIndex[i], startIndex[i + 1] - 1, maxWidth);
    else
      out[index++] = leftJustify(words, wordsSize, len, startIndex[i], startIndex[i + 1] - 1, maxWidth);
  }
  out[index] = leftJustify(words, wordsSize, len, startIndex[startLen - 1], wordsSize - 1, maxWidth);

  free(startIndex);
  *returnSize = startLen;
  return out;
}

int main (int argc, char **argv) {
  char** ret = 0;
  char* words[] = {"This", "is", "an", "example", "of", "text", "justification."};
  int wordsSize = sizeof(words)/sizeof(words[0]);
  int maxWidth = 16;
  int returnSize;

  debug ("wordsSize = %d", wordsSize);
  ret = fullJustify(words, wordsSize, maxWidth, &returnSize);
  for (int i=0; i<returnSize; ++i)
    debug("Output = %s", ret[i]);
  return 0;
}

/**
   => ./a.out
   [main] L=272 :wordsSize = 7
   [main] L=275 :Output = This    is    an
   [main] L=275 :Output = example  of text
   [main] L=275 :Output = justification.
**/
