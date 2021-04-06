/***
    981. Time Based Key-Value Store
    Create a timebased key-value store class TimeMap, that supports
    two operations.

    1. set(string key, string value, int timestamp)
    Stores the key and value, along with the given timestamp.

    2. get(string key, int timestamp)
    Returns a value such that set(key, value, timestamp_prev) was
    called previously, with timestamp_prev <= timestamp.
    If there are multiple such values, it returns the one with
    the largest timestamp_prev.
    If there are no values, it returns the empty string ("").

    Example 1:
    Input:
    inputs = ["TimeMap","set","get","get","set","get","get"],
    inputs = [[],["foo","bar",1],["foo",1],["foo",3],["foo","bar2",4],["foo",4],["foo",5]]
    Output: [null,null,"bar","bar",null,"bar2","bar2"]
    Explanation:
    TimeMap kv;
    kv.set("foo", "bar", 1); // store the key "foo" and value "bar"
    along with timestamp = 1
    kv.get("foo", 1);  // output "bar"
    kv.get("foo", 3); // output "bar" since there is no value corresponding
    to foo at timestamp 3 and timestamp 2, then the only value is at
    timestamp 1 ie "bar"
    kv.set("foo", "bar2", 4);
    kv.get("foo", 4); // output "bar2"
    kv.get("foo", 5); //output "bar2"

    Example 2:
    Input:
    inputs = ["TimeMap","set","set","get","get","get","get","get"],
    inputs= [[],["love","high",10],["love","low",20],["love",5],["love",10],["love",15],["love",20],["love",25]]
    Output: [null,null,null,"","high","high","low","low"]

    Note:
    All key/value strings are lowercase.
    All key/value strings have length in the range [1, 100]
    The timestamps for all TimeMap.set operations are strictly increasing.
    1 <= timestamp <= 10^7
    TimeMap.set and TimeMap.get functions will be called a total of 120000
    times (combined) per test case.
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

#define NHASH 10

typedef struct timestamp {
  char *key;
  char *value;
  int tstamp;
  struct timestamp *next;
} TimeMap;

TimeMap *systab[NHASH];

static void swap (TimeMap *s, TimeMap *m) {
  int temp;
  temp = s->tstamp;
  s->tstamp = m->tstamp;
  m->tstamp = temp;
}

void m_sort_Record(int h) {
  TimeMap *sys;
  int flag = 0;
  TimeMap  *start = systab[h];
  TimeMap  *trav, *min;

  for(sys=systab[h]; sys->next!=NULL; sys=sys->next) {
    start  = sys;
    min = start;
    trav = start->next;
    while (trav) {
      if (min->value > trav->value) { // Ascending Order
	min = trav;
	flag = 1; // to check we really needs to swap data
      }
      trav = trav->next;
    }
    if(flag) {
      swap (start, min);
      flag = 0; // Reset the flag
    }
    start = start->next;
  }
}

int get_hash(char *word) {
  int h = 0, wordNum = 0;
  int w = 3;
  while (word[h] != '\0') {
    wordNum += w * word[h++];
    w += 2;
  }
  int loc = wordNum % NHASH + 1;
  return loc;
}

/** Initialize your data structure here. */
TimeMap* timeMapCreate() {
  TimeMap* obj = (TimeMap*)malloc(sizeof(TimeMap*));
  if (NULL == obj)
    return NULL;
  return obj;
}

void timeMapSet(TimeMap* obj, char* key, char *value, int timestamp) {
  int k;
  TimeMap* sys = NULL;
  int h = get_hash(key);
  bool iscreate = 0;

  debug ("str = %s h = %d", key, h);
  if (NULL == systab[h]) {
    iscreate = 1;
  } else {
    /***
     * IF you reach here means, already one entry with key present.
     * Now add same key entry with different value & every time sort it.
     */
    sys = systab[h];
    if (key) {
      obj->key = (char *)malloc(sizeof(char) * strlen(key) + 1);
      k = snprintf(obj->key, strlen(key)+1, "%s\n", key);
      debug("%s j=%d", obj->key, k);
    }

    /* This may get NULL! */
    if(value) {
      obj->value = (char *)malloc(sizeof(char) * strlen(value) + 1);
      k = snprintf(obj->value, strlen(value)+1, "%s\n", value);
    } else {
      debug("sys->key %s value=%s", sys->key, sys->value);
      if (sys) {
	obj->value = (char *)malloc(sizeof(char) * strlen(sys->value) + 1);
	k = snprintf(obj->value, strlen(sys->value)+1, "%s\n", sys->value);
      }
    }
    obj->tstamp = timestamp;

    obj->next = sys;
    systab[h] = obj;
    /* Sort List in Ascending Order! */
    debug("Reached!");
    //m_sort_Record(h);
  }

  if(iscreate) {
    obj->key = (char *)malloc(sizeof(char) * strlen(key) + 1);
    debug ("str = %s h = %d", key, h);
    snprintf(obj->key, strlen(key)+1, "%s\n", key);
    if (value) {
      debug("Reached! %s", value);
      int len = strlen(value) + 1;
      obj->value = (char *)malloc(sizeof(char) * len);
      k = snprintf(obj->value, len, "%s\n", value);
    }
    obj->tstamp = timestamp;

    // sys->next = NULL;//systab[h];
    systab[h] = obj;
  }
}

char * timeMapGet(TimeMap* obj, char * key, int timestamp) {
  //int h = get_hash(key);
  //TimeMap *obj1 = systab[h];
  //  debug("Returing = %s", obj1->value);
  return obj->value;
}

void timeMapFree(TimeMap* obj) {
  if (obj) {
    if (obj->key)
      free(obj->key);
    if(obj->value)
      free(obj->value);
    free(obj);
  }
}

void m_print_table () {
  debug("Enter !");
  for (int i=0; i < NHASH; i++) {
    TimeMap *sym = systab[i];
    if (sym == NULL)
      continue;     /* don't print the bucket if it doesn't have anything in it! */

    while (sym != NULL) {
      printf ("i=[%d] %s %s tstamp= %d\t",i, sym->key, sym->value, sym->tstamp);
      sym = sym->next;
    }
    printf("\n");
    //debug ("NULL! ");
  }
}

/**
 * Your TimeMap struct will be instantiated and called as such:
 * TimeMap* obj = timeMapCreate();
 * timeMapSet(obj, key, value, timestamp);

 * char * param_2 = timeMapGet(obj, key, timestamp);

 * timeMapFree(obj);
*/
int main () {
  TimeMap* obj0 = timeMapCreate();
  timeMapSet(obj0, "foo", "bar", 1);

  char * param_0 = timeMapGet(obj0, "foo", 1);
  debug("param_0 = %s tv=%d", param_0, obj0->tstamp);


  TimeMap* obj1 = timeMapCreate();
  timeMapSet(obj1, "foo", NULL, 1);

  char * param_1 = timeMapGet(obj1, "foo", 1);
  debug("param_1 = %s tv=%d", param_1, obj1->tstamp);


  TimeMap* obj2 = timeMapCreate();
  timeMapSet(obj2, "foo", "bar", 10);

  char * param_2 = timeMapGet(obj2, "foo", 10);
  debug("param_2 = %s tv=%d", param_2, obj2->tstamp);


  TimeMap* obj3 = timeMapCreate();
  timeMapSet(obj3, "foo", NULL, 12);

  char * param_3 = timeMapGet(obj3, "foo", 12);
  debug("param_3 = %s tv=%d ", param_3, obj3->tstamp);
  /*
  timeMapFree(obj0);
  timeMapFree(obj1);
  timeMapFree(obj2);
  timeMapFree(obj3);
*/
  //m_print_table();
}
