#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>

struct tree_node {
	int data;
	struct tree_node *left;
	struct tree_node *right;
};

typedef struct tree_node tree_node;

tree_node *create_node(int);
void m_inorder(void *);
void m_preorder(void *);
void m_insert(void *, int);
void m_insert(void *, int);
void m_search(void *, int);
void m_delete_tree(void *);

#endif 
