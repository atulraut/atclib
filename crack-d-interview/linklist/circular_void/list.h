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
void m_add (void *, int); 
void m_display (void *);
void m_free (void *);
void m_Printrev(void *);

#endif
