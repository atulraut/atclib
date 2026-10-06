#ifndef LIST_H
#define LIST_H

#include <stdio.h>

typedef struct node_t {
  int data;
  struct node_t *next;
} NODE;

typedef struct list_t {
  NODE *head;
} LIST;

LIST *init_list (void *);
NODE *create_node (int);
void m_Addfirst (void *);
void m_Display(void *);
void m_Addlast(void *);
void m_Delfirst(void *);
void m_Dellast(void *);
void m_Freelist(void *);
void m_Revlist(void *);
void m_RevlistKthNode(void *);
void m_Sortlist(void *);
//void m_DelNode(void *, LIST_NODE *);
void m_ReturnNthNode_From_End(void *);
void m_RemoveDuplicateNodes(void *ptr);
void m_SearchData(void *ptr);
#endif
