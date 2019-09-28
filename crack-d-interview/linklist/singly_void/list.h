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
LIST * m_Init (LIST *);
void m_Addfirst(void*);
void m_Addlast(void *);
void m_Delfirst(void *);
void m_Display(void *);
void m_Dellast(void *);
void m_Freelist(void *);
void m_Revlist(void *);
void m_RevlistKthNode(void *);
void m_Sortlist(void *);
void m_DelNode(void *, LIST_NODE *);
void m_ReturnNthNode_From_End(void *);
void m_RemoveDuplicateNodes(void *ptr);
void m_SearchData(void *ptr);
void quit(void *);
/*
void m_Insert(int,int);
void m_Deletenode(int);
void m_Printrev ();
void m_RevRec();
*/
#endif
