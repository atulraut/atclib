/***
    शिवजयंती!

    Ch-1 : ADT Information hiding.

    OSTYPE=linux-gnu make

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Wed 19 Feb 2025 02:49:39 PM PST
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

#include "new.h"
#include "Object.h"
#include "Set.h"

void test() {

  void* s = new(Set);            // Set.h
  void* a = add(s, new(Object)); // Object.h
  void* b = add(s, new(Object)); // Object.h
  void* c = new(Object);         // Object.h

  if (contains(s, a) && contains(s, b))
    puts("Bags/Sets Okay 1!");

  if (contains(s, c))
    puts("Okay 2!");

  if (differ(a, add(s, a)))
    puts("differ 3!");

  if (contains(s, drop(s, a)))
    puts("Bags Drop 4!");

  delete(drop(s, b));
  delete(drop(s, c));
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**
=> ./bags
L=[52] [Bag.c] [new] :| p->[0x563580cfb2a0K]
L=[52] [Bag.c] [new] :| p->[0x563580cfb6d0K]
L=[75] [Bag.c] [add] :| element->count->[1] set->count->[1]
L=[52] [Bag.c] [new] :| p->[0x563580cfb6f0K]
L=[75] [Bag.c] [add] :| element->count->[1] set->count->[2]
L=[52] [Bag.c] [new] :| p->[0x563580cfb710K]
L=[91] [Bag.c] [contains] :| Enter ->
L=[91] [Bag.c] [contains] :| Enter ->
Bags/Sets Okay 1!
L=[91] [Bag.c] [contains] :| Enter ->
L=[75] [Bag.c] [add] :| element->count->[2] set->count->[3]
L=[118] [Bag.c] [differ] :| Enter ->
L=[97] [Bag.c] [drop] :| Enter ->
L=[91] [Bag.c] [contains] :| Enter ->
Bags Drop 4!
L=[97] [Bag.c] [drop] :| Enter ->
L=[97] [Bag.c] [drop] :| Enter ->

atul@rajgad:~/dev/atclib/at_oo_c/1_OoO_Prog_ANSI_C/1_ADT
=> ./sets
L=[35] [Set.c] [new] :| p->[0x55fe116f5044K] *p->[10]
L=[35] [Set.c] [new] :| p->[0x55fe116f5048K] *p->[10]
L=[51] [Set.c] [add] :| Enter ->
L=[35] [Set.c] [new] :| p->[0x55fe116f504cK] *p->[10]
L=[51] [Set.c] [add] :| Enter ->
L=[35] [Set.c] [new] :| p->[0x55fe116f5050K] *p->[10]
L=[84] [Set.c] [contains] :| Enter ->
L=[70] [Set.c] [find] :| Enter ->
L=[84] [Set.c] [contains] :| Enter ->
L=[70] [Set.c] [find] :| Enter ->
Bags/Sets Okay 1!
L=[84] [Set.c] [contains] :| Enter ->
L=[70] [Set.c] [find] :| Enter ->
L=[51] [Set.c] [add] :| Enter ->
L=[101] [Set.c] [differ] :| Enter ->
L=[90] [Set.c] [drop] :| Enter ->
L=[70] [Set.c] [find] :| Enter ->
L=[84] [Set.c] [contains] :| Enter ->
L=[70] [Set.c] [find] :| Enter ->
L=[90] [Set.c] [drop] :| Enter ->
L=[70] [Set.c] [find] :| Enter ->
L=[41] [Set.c] [delete] :| Enter ->
L=[90] [Set.c] [drop] :| Enter ->
L=[70] [Set.c] [find] :| Enter ->
L=[41] [Set.c] [delete] :| Enter ->
 **/
