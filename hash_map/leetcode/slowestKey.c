/***
    Slowest Key
    A newly designed keypad was tested, where a tester pressed
    a sequence of n keys, one at a time.

    You are given a string keysPressed of length n, where keysPressed[i]
    was the ith key pressed in the testing sequence, and a sorted list
    releaseTimes, where releaseTimes[i] was the time the ith key was
    released. Both arrays are 0-indexed. The 0th key was pressed at
    the time 0, and every subsequent key was pressed at the exact
    time the previous key was released.

    The tester wants to know the key of the keypress that had
    the longest duration. The ith keypress had a duration of
    releaseTimes[i] - releaseTimes[i - 1], and the 0th keypress
    had a duration of releaseTimes[0].

    Note that the same key could have been pressed multiple
    times during the test, and these multiple presses of the
    same key may not have had the same duration.

    Return the key of the keypress that had the longest duration.
    If there are multiple such keypresses, return the
    lexicographically largest key of the keypresses.

    Input: releaseTimes = [9,29,49,50], keysPressed = "cbcd"
    Output: "c"
    Explanation: The keypresses were as follows:
    Keypress for 'c' had a duration of 9 (pressed at time 0 and released at time 9).
    Keypress for 'b' had a duration of 29 - 9 = 20
    (pressed at time 9 right after the release of the previous character
    and released at time 29).
    Keypress for 'c' had a duration of 49 - 29 = 20
    (pressed at time 29 right after the release of the previous character and
    released at time 49).
    Keypress for 'd' had a duration of 50 - 49 = 1
    (pressed at time 49 right after the release of the previous character and
    released at time 50).
    The longest of these was the keypress for 'b' and the
    second keypress for 'c', both with duration 20.
    'c' is lexicographically larger than 'b', so the answer is 'c'.

    Input: releaseTimes = [12,23,36,46,62], keysPressed = "spuda"
    Output: "a"
    Explanation: The keypresses were as follows:
    Keypress for 's' had a duration of 12.
    Keypress for 'p' had a duration of 23 - 12 = 11.
    Keypress for 'u' had a duration of 36 - 23 = 13.
    Keypress for 'd' had a duration of 46 - 36 = 10.
    Keypress for 'a' had a duration of 62 - 46 = 16.
    The longest of these was the keypress for 'a' with duration 16.

    Constraints:

    releaseTimes.length == n
    keysPressed.length == n
    2 <= n <= 1000
    1 <= releaseTimes[i] <= 109
    releaseTimes[i] < releaseTimes[i+1]
    keysPressed contains only lowercase English letters.

    https://leetcode.com/problems/slowest-key/
    Date: 6 Sept 2021
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

char slowestKey(int* releaseTimes, int releaseTimesSize, char * keysPressed) {
  char max_key = 0;
  int max_duration = 0;

  int i=0;

  for(i=0; i<releaseTimesSize; i++) {
    int cur_duration;
    if(i==0) {
      cur_duration = releaseTimes[i] - 0;
    } else {
      cur_duration = releaseTimes[i] - releaseTimes[i - 1];
    }

    if(cur_duration == max_duration) {
      if(keysPressed[i] >= max_key) {
	max_key = keysPressed[i];
      }
      max_duration = cur_duration;
    } else if(cur_duration > max_duration) {
      max_key = keysPressed[i];
      max_duration = cur_duration;
    }
  }
  return max_key;
}

/* Atul Hash Map Implementaion */
/*
  Key   -: currentKey        {'a', 'b' 'c'}
  Value -: currentDuration   {1,   2,   4}
*/

#define NHASH 26

struct nameval {
  char ch;
  int value;
  struct nameval *next;
};

struct nameval *symtab[NHASH];

unsigned int get_hash(char c) {
  unsigned int h=0;
  unsigned char ci;

  debug ("key = %d char=%c", (c-'0' % NHASH), (c % NHASH) );
  return ((c-'0') % NHASH);
}

void print_table () {
  for (int i=0; i < NHASH; i++) {
    struct nameval* sym = symtab[i];
    if (sym == NULL)
      continue;     /* don't print the bucket if it doesn't have anything in it! */

    debug ("symtab[%d] = ", i);
    while (sym != NULL) {
      debug ("(%c: %d)", sym->ch, sym->value);
      sym = sym->next;
    }
    debug ("NULL! ");
  }
}

/* lookup: Find name in symtab, with optional create */
struct nameval* lookup(char c, int val, int isCreate) {
  struct nameval* sym = NULL;
  int key = get_hash(c);

  /* Lookup into hash table */
  for (sym = symtab[key]; sym!=NULL; sym=sym->next)
    if (sym->ch == c) {
      /*
	  If the key is already present in the map,
	  store the duration with the maximum value.
      */
      if (sym->value < val)
	sym->value = val;
      debug ("key = %d char=%c duration=%d", (c % NHASH), (c % NHASH), sym->value);
      return sym;
    }

  if(isCreate) {
    sym = (struct nameval *)calloc(sizeof(struct nameval), sizeof(char));
    sym->ch = c;
    sym->value = val;
    sym->next = symtab[key];
    symtab[key] = sym;
  }
  debug ("key = %d char=%c duration=%d", (c % NHASH), (c % NHASH), val);
  return sym;
}

char slowestKey_ATUL(int* releaseTimes, int releaseTimesSize, char* keysPressed) {
  int current_duration = releaseTimes[0];
  char key = keysPressed[0];
  int isCreate = 1;
  char slowestKey = ' ';
  int longestPressDuration = 0;

  struct nameval* sym = lookup(key, current_duration, isCreate);

  /*
    Find and store the keypress duration for each
    key in the durationMap
  */
  for (int i=1; i<releaseTimesSize; ++i) {
    current_duration = releaseTimes[i] - releaseTimes[i - 1];
    sym = lookup(keysPressed[i], current_duration, isCreate);

    debug("releaseTimes[%d-1]=%d releaseTimes[%d]=%d",i,releaseTimes[i-1],i,releaseTimes[i]);
  }

  //  print_table();
  /*
    Iterate over the map to find the slowest key
  */
  for (int i=0; i < NHASH; i++) {
    sym = symtab[i];
    if (sym == NULL)
      continue;     /* don't print the bucket if it doesn't have anything in it! */

    debug ("symtab[%d] = ", i);
    while (sym != NULL) {
      debug ("(%c: %d)", sym->ch, sym->value);
      char key = sym->ch;
      current_duration = sym->value;
      if(current_duration > longestPressDuration) { // A1 - Check Below Algo
	longestPressDuration = current_duration;
	slowestKey = key;
      } else if(current_duration == longestPressDuration && key > slowestKey)  // B2 - Check Below Algo
	slowestKey = key;

      sym = sym->next;
    }
    debug ("NULL! ");
  }
  return slowestKey;
}

int main (int argc, char **argv) {
  char ret = 0;
  int releaseTimes1[] = {9,29,49,50};
  char keysPressed1[] = "cbcd";

  int releaseTimes2[] = {12,23,36,46,62};
  char keysPressed2[] = "spuda";

  int releaseTimesSize = sizeof(releaseTimes)/sizeof(releaseTimes[0]);

  ret = slowestKey(releaseTimes,releaseTimesSize,
		   keysPressed);
  debug("Output = %c", ret);
  return 0;
}

/**
   Algorithm

   Iterate over the array releaseTimes to find the press duration
   currentDuration for each key currentKey.
   Build a map durationMap to store the keypress duration of each
   key in the form of key-value pair, currentKey -> currentDuration.
   If the key is already present in the map, store the duration
   with the maximum value.

   Iterate over each element in durationMap. Track the maximum
   duration in the variable longestPressDuration and the corresponding
   key in the variable slowestKey. For each entry of the map,
   get the duration and key and check for the following conditions:

   A1:
   If the value of duration is greater than the longestPressDuration
   found so far, then update the longestPressDuration with the value
   of duration. Also, the slowestKey will be updated with the
   corresponding key value.
   B2:
   If the value of duration is equal to the longestPressDuration,
   check if the key is lexicographically larger than the slowestKey.
   If so, update the slowestKey with the key value.

   Lexicographically larger key denotes the key that is larger than
   the other key in alphabetical order. For example, b is
   lexicographically larger than a, c is larger than b, and so on.

   At the end, return the slowestKey found after iterating over all
   the elements in the map.
**/

/*
  => ./a.out
  [lookup] L=83 :key = 115 char=s duration=12
  [lookup] L=83 :key = 112 char=p duration=11
  [slowestKey] L=104 :releaseTimes[1-1]=12 releaseTimes[1]=23
  [lookup] L=83 :key = 117 char=u duration=13
  [slowestKey] L=104 :releaseTimes[2-1]=23 releaseTimes[2]=36
  [lookup] L=83 :key = 100 char=d duration=10
  [slowestKey] L=104 :releaseTimes[3-1]=36 releaseTimes[3]=46
  [lookup] L=83 :key = 97 char=a duration=16
  [slowestKey] L=104 :releaseTimes[4-1]=46 releaseTimes[4]=62
  [slowestKey] L=116 :symtab[97] =
  [slowestKey] L=118 :(a: 16)
  [slowestKey] L=129 :NULL!
  [slowestKey] L=116 :symtab[100] =
  [slowestKey] L=118 :(d: 10)
  [slowestKey] L=129 :NULL!
  [slowestKey] L=116 :symtab[112] =
  [slowestKey] L=118 :(p: 11)
  [slowestKey] L=129 :NULL!
  [slowestKey] L=116 :symtab[115] =
  [slowestKey] L=118 :(s: 12)
  [slowestKey] L=129 :NULL!
  [slowestKey] L=116 :symtab[117] =
  [slowestKey] L=118 :(u: 13)
  [slowestKey] L=129 :NULL!
  [main] L=146 :Output = a
*/
