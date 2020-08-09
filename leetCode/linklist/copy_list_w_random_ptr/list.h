#ifndef ADD_H_LIST
#define ADD_H_LIST
/*
typedef struct list_n {
    int data;
    struct list_n *next;
} LIST_NODE;

typedef struct list_t {
  struct list_n *head;
} LIST;
*/

struct node {
  int val;
  int index;
  struct node *next;
  struct node *random;
};

struct node *head;
int cnt;

void m_Addfirst(void*);
struct node* m_copyRandomList(void *);
void m_set_random_ptr (void *);
void m_Display(void *);
void m_SearchData(void *);
void quit(void *);

#endif
