/*
 * Aim 	 : Doubly Circular Link List.
 * Author : Atul Ramesh Raut
 * Date   : Sun Jul 17 04:04:49 PM PDT 2022
 * File   : main.c
 *
 ***/

#include <stdio.h>
#include <stdlib.h>
#include "atlist.h"

int main() {
  struct list_head todo_list;
  struct todo_struct *todo = (struct todo_struct*)malloc(sizeof(struct todo_struct));
  INIT_LIST_HEAD(&todo_list);
  // LIST_HEAD(todo_list); Another way to initialized

}
