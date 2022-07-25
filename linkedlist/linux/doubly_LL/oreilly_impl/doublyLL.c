#include "atlist.h"

void todo_add_entry(struct todo_struct *new) {
  struct list_head *ptr;
  struct todo_struct *entry;

  for (ptr = todo_list.next; ptr != &todo_list; ptr = ptr->next) {
    entry = list_entry(ptr, struct todo_struct, list);
    if (entry->priority < new->priority) {
      list_add_tail(&new->list, ptr);
      return;
    }
  }
  list_add_tail(&new->list, &todo_struct)
}
