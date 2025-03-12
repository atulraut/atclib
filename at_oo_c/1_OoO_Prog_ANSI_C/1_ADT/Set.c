/***
    शिवजयंती!

    Ch-1 : ADT Information hiding.

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Wed 19 Feb 2025 03:53:52 PM PST
    Folsom, CA.
*/

/*----------------------------------- Header --------------------------------------*/
#include <stdio.h>
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

#include "new.h"
#include "Object.h"
#include "Set.h"

const void* Set;
const void* Object;

#if !defined MANY || MANY<1
#define MANY 10
#endif

static int heap[MANY];

void* new(const void* type, ...) {

  int* p;          /* & heap[1..] */

  for (p = heap+1; p<heap+MANY; ++p)
    if(!*p)
      break;

  assert(p < heap + MANY);
  *p = MANY;
  debug("p->[%pK] *p->[%d]", p, *p);
  return p;
}

void delete (void* _item) {

  debug ("Enter ->");
  int* item = _item;
  if (item) {
    assert(item > heap && item < heap+MANY);
    *item = 0;
  }
}

void* add(void* _set, const void* _element) {

  debug ("Enter ->");
  int* set = _set;
  const int* element = _element;

  assert(set > heap && set < (heap + MANY));
  assert(*set == MANY);
  assert(element > heap && element < heap+MANY);

  if(*element == MANY)
    *(int*)element = set - heap;
  else
    assert(*element == set-heap);


  return (void*)element;
}

void* find(const void* _set, const void* _element) {

  debug ("Enter ->");
  const int* set = _set;
  const int* element = _element;

  assert(set > heap && set < heap+MANY);
  assert(*set == MANY);
  assert(element > heap && element < heap+MANY);
  assert(*element);

  return *element == set-heap ? (void*)element : 0;
}

int contains(const void* _set, const void* _element) {

  debug ("Enter ->");
  return find (_set, _element) != 0;
}

void* drop(void* _set, const void* _element) {

  debug ("Enter ->");
  int* element = find(_set, _element);

  if(element)
    *element = MANY;

  return element;
}

int differ(const void* a, const void* b) {

  debug ("Enter ->");
  return a!= b;
}
