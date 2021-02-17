#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define SIZE 1000000

typedef struct {
    int arr[1000000];
} MyHashSet;

/** Initialize your data structure here. */

MyHashSet* myHashSetCreate() {
    MyHashSet *hashset = calloc(sizeof(MyHashSet), 1);
    return hashset;
}

void myHashSetAdd(MyHashSet* obj, int key) {
    if (obj != NULL) {
        obj->arr[key] = 1;
    }
}

void myHashSetRemove(MyHashSet* obj, int key) {
    if (obj != NULL) {
        obj->arr[key] = 0;
    }
}

/** Returns true if this set contains the specified element */
bool myHashSetContains(MyHashSet* obj, int key) {
    if (obj != NULL) {
        if (obj->arr[key] == 1) {
            return true;
        }
    }
    return false;
}

void myHashSetFree(MyHashSet* obj) {
    if (obj != NULL) {
        free(obj);
    }
}

/**
 * Your MyHashSet struct will be instantiated and called as such:
 * MyHashSet* obj = myHashSetCreate();
 * myHashSetAdd(obj, key);

 * myHashSetRemove(obj, key);

 * bool param_3 = myHashSetContains(obj, key);

 * myHashSetFree(obj);
*/
void m_TestFunc() {
  int i;
  // ["MyHashSet","add","add","contains","contains","add","contains","remove","contains"]
  int arr[] = {1, 2, 1, 3, 2, 2, 2};
  int sz = sizeof(arr)/sizeof(arr[0]);

  MyHashSet *obj = myHashSetCreate();
  printf ("[%s] -->  \n", __func__);

  for (i=0; i<sz; i++) {
    myHashSetAdd(obj, arr[i]);
  }

  bool param_3 = myHashSetContains(obj, arr[6]);
  printf ("[%s] Removing Element param=%d L=%d \n", __func__, param_3, __LINE__);

  /* Lets validate the hashing */
  printf ("[%s] Removing Element ! L=%d \n", __func__, __LINE__);
  for (i=0; i<sz; i++)
    myHashSetRemove(obj, arr[i]);

  myHashSetFree(obj);
}

int main () {
  m_TestFunc();
}
