#ifndef ADD_H_LIST
#define ADD_H_LIST

struct list_node {
    int data;
    struct list_node *next;
} list_node;

struct list {
  struct list_node *head;
} list;

/* Creating Two Linked List */
extern struct list *list1;
extern struct list *list2;
extern struct list *l_base;

int counter;
struct list* m_Init (struct list *);
void m_Addfirst(void*);
void m_Addlast(void *);
void m_Delfirst(void *);
void m_Display(void *);
void m_Dellast(void *);
void middleNode(void *);
void m_Freelist(void *);
void m_Revlist(void *);
void m_RevlistKthNode(void *);
void m_Sortlist(void *);
void m_DelNode(void *, struct list_node *);
void m_ReturnNthNode_From_End(void *);
void m_RemoveDuplicateNodes(void *);
void m_SearchData(void *);
void quit(void *);
void addTwoNumbers(void *); // LeetCode

#endif
