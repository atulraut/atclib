/***
    https://leetcode.com/problems/rearrange-spaces-between-words/
    Rearrange Spaces Between Words

    You are given a string text of words that are placed among
    some number of spaces. Each word consists of one or more
    lowercase English letters and are separated by at least
    one space. It's guaranteed that text contains at least one
    word.

    Rearrange the spaces so that there is an equal number of
    spaces between every pair of adjacent words and that number
    is maximized. If you cannot redistribute all the spaces
    equally, place the extra spaces at the end, meaning the
    returned string should be the same length as text.

    Return the string after rearranging the spaces.

    Input: text = "  this   is  a sentence "
    Output: "this   is   a   sentence"
    Explanation: There are a total of 9 spaces and 4 words.
    We can evenly divide the 9 spaces between the w
    ords: 9 / (4-1) = 3 spaces.

    Input: text = " practice   makes   perfect"
    Output: "practice   makes   perfect "
    Explanation: There are a total of 7 spaces and 3 words.
    7 / (3-1) = 3 spaces plus 1 extra space. We place this extra
    space at the end of the string.

    Input: text = "hello   world"
    Output: "hello   world"
    Example 4:

    Input: text = "  walks  udp package   into  bar a"
    Output: "walks  udp  package  into  bar  a "
    Example 5:

    Input: text = "a"
    Output: "a"


    Constraints:

    1 <= text.length <= 100
    text consists of lowercase English letters and ' '.
    text contains at least one word.

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings reorderSpaces.c -lm

    Date: 10182021 Oct
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

typedef struct Node_ {
  int start;
  int end;
  struct Node_ *next;
} Node;


static void insertToken(Node** head, Node** tail, int start, int end) {
  Node* node = (Node *)malloc(sizeof(Node));
  node->start = start;
  node->end = end;
  node->next = NULL;
  if (*head == NULL) {
    *head = node;
    *tail = node;
  } else {
    (*tail)->next = node;
    *tail = node;
  }
}

char* reorderSpaces(char* text) {
  char* ans = NULL;
  int length = 0;
  char* pos = NULL;
  int spaces = 0;
  int tokens = 0;
  int divid = 0;
  int extra = 0;
  Node* head = NULL;
  Node* tmp = NULL;
  Node* tail = NULL;
  int i = 0;

  debug("Enter!");
  pos = text;
  while (*pos != '\0') {
    if (*pos == ' ')
      spaces++;
    else {
      if (pos == text || *(pos - 1) == ' ') {
	tokens++;
	insertToken(&head, &tail, length, length);
      } else {
	tail->end = length;
      }
    }
    length++;
    pos++;
  }

  if (tokens > 1) {
    divid = spaces / (tokens - 1);
    extra = spaces % (tokens - 1);
  } else
     extra = spaces;
  ans = (char *)malloc(length + 1);
  if (ans == NULL) {
    perror("Memory Allocation Error");
    abort();
  }
  pos = ans;
  while (head != NULL) {
    for (i = head->start; i <= head->end; i++) {
      *pos = text[i];
      pos++;
    }

    tmp = head;
    head = head->next;
    free(tmp);
    if (head != NULL) {
      for (i = 0; i < divid; i++) {
	*pos = ' ';
	pos++;
      }
    }

  }

  for (i = 0; i < extra; i++) {
    *pos = ' ';
    pos++;
  }
  *pos = '\0';
  return ans;
}


char* reorderSpaces1(char* text) {
  char tmp[100];
  memset(tmp,0,sizeof(tmp));
  int i, j, k , index = 0, space_count = 0, word_count = 0, interspace = 0;
  int first = 0;

  debug("Enter!");
  for(i = 0; i < strlen(text); i++) {
    if(text[i] == ' ') {
      space_count++;
    }
    if(text[i] >= 97 && text[i] <= 122) {
      if(i == 0)
	word_count++;
      else if(text[i - 1] == ' ')
	word_count++;
    }
  }
  if(word_count == 1)
    interspace = space_count;
  else
    interspace = space_count/(word_count - 1);

  for(i = 0; i < strlen(text); i++) {
    if(text[i] >= 97 && text[i] <= 122) {
      tmp[index] = text[i];
      if(i != strlen(text) - 1)
	index++;
      else if(i == strlen(text) - 1) {
	if(space_count == 0) {
	  for(k = 0; k < strlen(text); k++) {
	    text[k] = tmp[k];
	  }
	} else {
	  for(j = 0; j < space_count; j++) {
	    if(index + 1 < strlen(text))
	      tmp[++index] = ' ';
	  }
	  for(k = 0; k < strlen(text); k++) {
	    text[k] = tmp[k];
	  }
	}
	return text;
      }

      if(text[i + 1] == ' ') {
	if(space_count == 0 && (index == strlen(text) - 1)) {
	  for(k = 0; k < strlen(text); k++) {
	    text[k] = tmp[k];
	  }
	  return text;
	} else {
	  for(j = 0; j < interspace; j++) {
	    tmp[index] = ' ';
	    space_count--;
	    if(space_count == 0 && (index == strlen(text) - 1)) {
	      for(k = 0; k < strlen(text); k++) {
		text[k] = tmp[k];
	      }
	      return text;
	    } else
	      index++;
	  }
	}
      }
    }
  }

  for(k = 0; k < strlen(text); k++) {
    text[k] = tmp[k];
  }

  return text;
}

void getSpaceCnt(char* str, int* spaceCnt) {
  int i = 0;
  while (str[i] != '\0') {
    if (str[i] == ' ')
      ++*spaceCnt;
    i++;
  }
  debug ("space Count = %d", *spaceCnt);
}

void getWordsCnt(char* str, int* wordCnt) {
  int i = 0;
  while (str[i] != '\0') {
    if (str[i] == ' ' && str[i+1] != ' ')
      ++*wordCnt;
    i++;
  }
  debug ("word Count = %d", *wordCnt-1);
}

char* reorderSpaces__AR(char* text) {
  int totalSpaceCnt = 0;
  int totalWordsCnt = 0;
  int finalSpaceCnt = 0;
  int k = -1;

  getSpaceCnt(text, &totalSpaceCnt);
  getWordsCnt(text, &totalWordsCnt);

  finalSpaceCnt = totalSpaceCnt/(totalWordsCnt-1);
  for (int i=0; i!= '\0'; ++i) {
    if (text[i] == ' ' && text[i+1] == ' ')
      continue;
    else
      text[++k] = text[i];
  }
  debug("Final Space Count = %d", finalSpaceCnt);
  debug("text = %s", text);
  return text;
}

int main (int argc, char **argv) {
  char* ret;
  char text[] = "  this   is  a sentence ";

  debug("Input = %s", text);
  ret = reorderSpaces1(text);
  debug("Output = %s", ret);
  return 0;
}

/**
   => ./a.out
   [main] L=276 :Input =   this   is  a sentence
   [reorderSpaces] L=102 :Enter!
   [main] L=278 :Output = this   is   a   sentence
**/
