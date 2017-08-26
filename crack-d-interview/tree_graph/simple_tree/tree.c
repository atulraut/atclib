#include <math.h>
#include "list.h"

#define max(X,Y) ((X) > (Y) ? (X) : (Y))

tree_node *create_node(int val) {
	tree_node *node = (tree_node *)malloc(sizeof(tree_node));
	if (NULL == node)
		return NULL;
	node->data = val;
	node->left = NULL;
	node->right= NULL;
	return node;
}

void m_insert (void *_root, int val) {
	tree_node *rt = (tree_node *)_root;
	tree_node *nn = NULL;	
	tree_node *trav=NULL;
	tree_node *parent_trav=NULL;
	printf ("at max = %d \n", max (14,5));
	nn = create_node (val);
	nn->data = val;
	nn->left = NULL;
	nn->right= NULL;
	printf ("1. ATUL trav=%p, val=[%d] \n", nn, val);
	if (NULL == rt) {
		rt = nn;
		rt->left = NULL;
		rt->right= NULL;
	} else {
		parent_trav = NULL;
		trav = rt;
		while (NULL != trav) {
			parent_trav = trav;
			if (val < trav->data) {
				printf ("trav->data=%d\n", trav->data);
				trav = trav->left;
			} else {
				printf ("trav->data=%d\n", trav->data);
				trav = trav->right;
			}
		}
		if (val < parent_trav->data) {
			parent_trav->left = nn;
			printf ("parent_trav->left =%p \n", parent_trav->left);
		}
		else {
			parent_trav->right= nn;
			printf ("parent_trav->right =%p \n", parent_trav->right);
		}
	}
	printf ("root->left =%p \n", rt->left);
	printf ("root->right=%p \n", rt->right);
}

void m_preorder(void *_root) {
	tree_node *nn = (tree_node *)_root;
	printf ("\n m_inoder \n");
	printf ("->[%d]", nn->data);
	if(nn == NULL)
		return;
	if(NULL != nn->left)
		m_preorder(nn->left);
	if(NULL != nn->right)
		m_preorder(nn->right);
}

void m_inorder(void *_root) {
	tree_node *nn = (tree_node *)_root;
	if(nn == NULL)
		return;
	m_inorder(nn->left);
	printf("->[%d]\n", nn->data);
	m_inorder(nn->right);
}

void m_search(void *_root, int val) {
	tree_node *nn = (tree_node *)_root;
	tree_node *trav = NULL;
	trav = nn;
	if (trav == NULL) {
		printf ("Not found = %d \n", val);
		return;
	}
	if (val == (trav->data)) {
		printf ("[m_search] Found = [%d]\n", trav->data);
		return;
	}
	else if (val < trav->data) {
		trav = trav->left;
		m_search(trav, val);
	}
	else {
		trav = trav->right;
		m_search(trav, val);
	}
}

void m_delete_tree(void *_root) {
	tree_node *nn = (tree_node *)_root;
	tree_node *trav = nn;
	if (NULL != trav) {
		m_delete_tree(trav->left);
		m_delete_tree(trav->right);
		free(trav);
	        trav = NULL;
	}
}

static int h1,h2;
int tree_height(void *_root) {
	  tree_node *p = (tree_node *)_root;
          if(p==NULL)
	           return(0);
          if(p->left) {
                          h1=tree_height(p->left);
                          h1++;
          }
          if(p->right) {
                      h2=tree_height(p->right);
                      h2++;
          }
          return(max(h1,h2)+1);
 }
