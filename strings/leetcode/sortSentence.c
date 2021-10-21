/***
    https://leetcode.com/problems/sorting-the-sentence/
    Sorting the Sentence

    A sentence is a list of words that are separated by a
    single space with no leading or trailing spaces.
    Each word consists of lowercase and uppercase English letters.

    A sentence can be shuffled by appending the 1-indexed
    word position to each word then rearranging the words
    in the sentence.

    For example, the sentence "This is a sentence" can be
    shuffled as "sentence4 a3 is2 This1" or "is2 sentence4 This1 a3".
    Given a shuffled sentence s containing no more than 9
    words, reconstruct and return the original sentence.

    Input: s = "is2 sentence4 This1 a3"
    Output: "This is a sentence"
    Explanation: Sort the words in s to their original positions
    "This1 is2 a3 sentence4", then remove the numbers.

    Input: s = "Myself2 Me1 I4 and3"
    Output: "Me Myself and I"
    Explanation: Sort the words in s to their original positions
    "Me1 Myself2 and3 I4", then remove the numbers.

    Constraints:
    2 <= s.length <= 200
    s consists of lowercase and uppercase English letters, spaces,
    and digits from 1 to 9.
    The number of words in s is between 1 and 9.
    The words in s are separated by a single space.
    s contains no leading or trailing spaces.

    Date: Oct 18, 2021
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

#define MAX_STR_SIZE 200
#define MAX_WORD_SIZE 25

char* sortSentence(char* s) {
  char* tok;
  char* list = malloc(MAX_WORD_SIZE * 9);
  char* buf = malloc(MAX_STR_SIZE + 1);
  int len;
  int idx;
  int i;
  int wc = 0;
  int car = 0;

  debug("Input = %s", s);
  memset(buf, 0, MAX_STR_SIZE);
  tok = strtok(s, " ");
  debug("tok = %s", tok);
  while(tok) {
    len = strlen(tok);
    idx = (tok[len-1] - '0') - 1;
    debug("idx = %d", idx);
    memcpy(list + idx*MAX_WORD_SIZE, tok, len-1);
    list[+idx*MAX_WORD_SIZE+len] = 0;
    debug ("list = %s", list);
    tok = strtok(NULL, " ");
    debug("tok = %s", tok);
    wc++;
  }
  debug ("wc = %d",wc);
  for(i=0; i<wc; i++) {
    car += sprintf(buf+car, "%s", list+i*MAX_WORD_SIZE);
    buf[car-1] = ' ';
  }

  buf[car-1] = '\0';
  free(list);

  debug("buf = %s", buf);
  return buf;
}

char* __sortSentence(char* s) {
  int start = 0;
  int m = 0;

  char* temp = (char*)malloc(strlen(s)*sizeof(char));
  for(int i = 1; i < 10; i++) {
    start = 0;
    for(int j = 0; j < strlen(s); j++) {
      debug ("j = %d s[j]=%c", j, s[j]);
      if(s[j] == ' ')
	start = j + 1;
      if(s[j] == 48 + i) { // 48 == '0' 49 == '1'
	debug("s[%d]=%c", j, s[j]);
	for(int k = start; k < j; k++)
	  temp[m++] = s[k];
	temp[m++] = ' ';
      }
    }
    debug("i = %d start = %d", i, start);
  }
  temp[--m] = '\0';
  return temp;
}

char* sortSentence__Pending_AR(char* s) {
  int thisIdx = 0;
  char charCnt = 0;
  int wordCnt = 0, i=-1;
  //  char** strs;

  while (s[++i] != '\0')
    if (s[i] == ' ')
      ++wordCnt;
  wordCnt += 1;
  debug("wordCnt = %d", wordCnt);

  char* str = "Atul4 Ramesh6 Raut4";
  int len = strlen(str);
  char* strs = (char*)malloc(sizeof(char) * len+1);
  strncpy(strs, str, len);
  strs[len]= '\0';
  debug ("--> %s", strs);
  debug("<--------------***----------->");
  while(strs[i]) {
    char* tok = strtok(strs, " ");
    len = strlen(tok);
    len += 1;
    i = len;
    strs = strs+len;
    debug("tok = %s", tok);
    debug("s = %s", strs);
    debug("<--------------***----------->");
  }
  printf("Hello World");
  return strs;
}

char* sortSentence__1(char* s) {
  int thisIdx = 0;
  char charCnt = 0;
  int wordCnt = 0, i=-1;
  char** strs;
  debug("AR");
  while (s[++i] != '\0')
    if (s[i] == ' ')
      ++wordCnt;
  wordCnt += 1;
  debug("wordCnt = %d", wordCnt);

  strs= (char**)malloc(sizeof(char) * wordCnt);

  i = -1;
  while (s[++i] != '\0') {
    debug ("ch = %c", s[i]);
    charCnt++;

    char* tok = strtok(s, " ");
    int len = strlen(tok);
    s = s+len+1;
    debug("tok = %s", tok);
    debug("s = %s", s);

    if(s[i] != ' ') {
      //      debug("thisIdx=%d charCnt=%d", thisIdx, charCnt);
      char ch = s[i];
      if(isdigit(ch)) {
	int digit = ch - '0'; // char to num
	strs[digit] = (char*)malloc(sizeof(char) * charCnt);
	memmove(strs+digit, s+thisIdx, charCnt-1);
	//strncpy(strs[digit], s+thisIdx, charCnt);
	strs[digit] = 0;//'\0';
	//debug("digit = %d strs=%s", digit, strs[digit]);
	charCnt = 0;
	thisIdx = 0;
      }
    }
    thisIdx = charCnt;
  }
  return s;
}

int main (int argc, char **argv) {
  char* ret;
  char s[] = "sentence4 a3 is2 This1";
  char s1[] = "is2 This1";

  //ret = sortSentence(s);
  //debug("Output = %s", ret);
  ret = __sortSentence(s);
  debug("Output = %s", ret);

  return 0;
}

/**

 **/
