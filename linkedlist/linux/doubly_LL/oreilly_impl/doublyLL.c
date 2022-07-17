#include "list.h"

struct list_head {
  struct list_head *next;
  struct list_head *prev;
};

struct todo_struct {
  struct list_head list;
  int priority; /* Local Driver Specific */
  /* ... add other driver specific fields */
};

struct list_head todo_list;
INIT_LIST_HEAD(&todo_list);
// LIST_HEAD(todo_list); Another way to initialized
