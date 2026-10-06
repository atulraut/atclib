/***
    https://leetcode.com/problems/word-ladder
    Word Ladder

    A transformation sequence from word beginWord to word
    endWord using a dictionary wordList is a sequence of
    words beginWord -> s1 -> s2 -> ... -> sk such that:

    Every adjacent pair of words differs by a single letter.
    Every si for 1 <= i <= k is in wordList. Note that
    beginWord does not need to be in wordList.
    sk == endWord
    Given two words, beginWord and endWord, and a dictionary
    wordList, return the number of words in the shortest
    transformation sequence from beginWord to endWord, or 0
    if no such sequence exists.

    Input: beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log","cog"]
    Output: 5
    Explanation: One shortest transformation sequence is "hit" -> "hot" -> "dot" -> "dog" -> cog", which is 5 words long.

    Input: beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log"]
    Output: 0
    Explanation: The endWord "cog" is not in wordList, therefore there is no valid transformation sequence.

    Constraints:
    1 <= beginWord.length <= 10
    endWord.length == beginWord.length
    1 <= wordList.length <= 5000
    wordList[i].length == beginWord.length
    beginWord, endWord, and wordList[i] consist of lowercase English letters.
    beginWord != endWord
    All the words in wordList are unique.

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: 02/11/2022 23:22
    Folsom, CA.
*/

/*----------------------------------- Header --------------------------------------*/
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

/*----------------------------------- Micro --------------------------------------*/
#define debug(str,args...) printf("[%s] L=%d :"str"\n", __func__, __LINE__, ##args)
#define atsizeof(object) (char *)(&object+1) - (char*)(&object)
#define arrsz(x)  (sizeof(x) / sizeof((x)[0]))
#define max(a,b)				\
  ({ __typeof__ (a) _a = (a);			\
    __typeof__ (b) _b = (b);			\
    _a > _b ? _a : _b; })
#define min(a,b)				\
  ({ __typeof__ (a) _a = (a);			\
    __typeof__ (b) _b = (b);			\
    _a < _b ? _a : _b; })
/*----------------------------------- Micro --------------------------------------*/

#define QEUEU_MAX 20000

typedef struct myQueue {
  int cur;
  int dep;
}myQueue;

myQueue *myqueue = NULL;
int * visited = NULL;

int front = 0;
int tail = 0;

void createQueue(int queue_size, int visited_size) {
  myqueue = calloc(queue_size, sizeof(myQueue));
  visited = calloc(visited_size, sizeof(int));

  front = 0;
  tail = 0;
}

void enqueue( int cur, int dep ) {
  visited[cur] = 1;
  if(front == QEUEU_MAX) {
    printf(" queue is full \n" );
    return;
  }
  myqueue[front].cur = cur;
  myqueue[front].dep = dep;
  front++;
}

myQueue dequeue(void) {
  myQueue ret;
  ret.cur = -1;
  ret.dep = -1;
  if(tail == front) {
    //        printf("queue is empty\n");
    return ret;
  }
  //    printf("dequeue %d %d\n", myqueue[tail].cur, myqueue[tail].dep);
  ret = myqueue[tail];
  tail++;
  return ret;
}

bool isSame(char *a, char *b) {
  int i =0;
  int cnt =0;
  while(a[i]!='\0') {
    if(a[i]!=b[i]) cnt++;
    if(cnt ==2) return false;
    i++;
  }
  return true;
#if 0
  int len = strlen(a);
  char * tmp_a = calloc(len+2, sizeof(char));
  char * tmp_b = calloc(len+2, sizeof(char));
  for(int i=0; i < len; i++) {
    memcpy(tmp_a, a, sizeof(char)*len);
    memcpy(tmp_b, b, sizeof(char)*len);

    tmp_a[i]='*';
    tmp_b[i]='*';

    if(!strcmp(tmp_a , tmp_b))
      return true;
  }
  return false;
#endif
}

int ladderLength(char* beginWord, char* endWord, char** wordList, int wordListSize) {
  int ret = 0;
  int flag = 0;
  int dest = 0;
  for(int i =0; i < wordListSize; i++) {
    if(!strcmp(endWord, wordList[i])) {
      dest = i;
      flag++;
    }

  }
  if(flag == 0)
    return 0;  // didnot include the endWord in wordList.

  createQueue(QEUEU_MAX, wordListSize);

  // BFS
  for(int i =0; i < wordListSize; i++) {
    if(isSame(beginWord, wordList[i])) {
      if(i == dest) return 2;
      enqueue(i, 2);  // set visited in enqueue.
    }
  }

  //dequeue, myqueue.cur, myqueue.dep
  while(1) {
    myQueue tmp = dequeue();

    for(int i =0; i < wordListSize; i++) {
      if(visited[i]==0 && isSame(wordList[tmp.cur], wordList[i])) {
	//               printf("--- enqueue\n");
	if(i == dest) return tmp.dep+1;
	enqueue(i, tmp.dep+1);  // set visited in enqueue.
      }
    }

    if(front == tail)
      break;
  }
  return 0;
}

void test() {
  int ret = 0;
  char beginWord[] = "hit";
  char endWord[]   = "cog";
  char *wordList[] = {"hot","dot","dog","lot","log","cog"};
  int wordListSize = 6;

  ret = ladderLength(beginWord, endWord, wordList, wordListSize);
  debug("Output = %d", ret);
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**
   => ./a.out
   [test] L=190 :Output = 5
**/
