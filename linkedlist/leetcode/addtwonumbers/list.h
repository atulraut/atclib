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
struct list *list1;
struct list *list2;
struct list *l_base;

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
void m_Sortlist(void *);
void m_DelNode(void *, struct list_node *);
void quit(void *);
void setLLType();
void addTwoNumbers(void *); // LeetCode
void mergeTwoLinkedList(void *);

#define debug(str,args...) printf("[%s] L=%d :"str"\n", __func__, __LINE__, ##args)

#endif
