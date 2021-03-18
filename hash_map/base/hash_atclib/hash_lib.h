#ifndef HASH_LIB
#define HASH_LIB

struct node {
  int val;
  int key;
  struct node *next;
};

struct table {
  int sz;
  struct node **list;
};

void m_TestFunc();
struct table* m_createTable(int size);
int m_getHashCode(struct table *t, int key);
void m_insert (struct table *t, int key);
int m_lookup (struct table *t, int key);
void m_Display(void *);
void quit(void *);

#endif
