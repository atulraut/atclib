#ifndef ADD_H_LIST
#define ADD_H_LIST

typedef struct list_n {
    int data;
    struct list_n *next;
} LIST_NODE;

typedef struct list_t {
  struct list_t *head;
} LIST;

int counter;
LIST * m_Init ();
LIST_NODE* m_CreateNodeL (int);
void m_Addfirst(int, void*);
void m_Addlast(int, void *);
void m_Delfirst();
void m_Display(void *);
void m_Dellast(void *);
void m_Freelist(void *);
void m_Revlist(void *); 
void swap (LIST_NODE *s, LIST_NODE *m);
void m_Sortlist(void *);
void m_DelNode(void *, LIST_NODE *);
void m_ReturnNthNode_From_End(void *, int);
/*
void m_Insert(int,int);
void m_Deletenode(int);
void m_Printrev ();
void m_RevRec();
*/
#endif
