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
			  //printf ("trav->data=%d\n", trav->data);
				trav = trav->left;
			} else {
			  //printf ("trav->data=%d\n", trav->data);
				trav = trav->right;
			}
		}
		if (val < parent_trav->data) {
			parent_trav->left = nn;
			//printf ("parent_trav->left =%p \n", parent_trav->left);
		}
		else {
			parent_trav->right= nn;
			//printf ("parent_trav->right =%p \n", parent_trav->right);
		}
	}
	printf ("root->left =%p \n", rt->left);
	printf ("root->right=%p \n", rt->right);
}

void m_preorder(void *_root) {
	tree_node *nn = (tree_node *)_root;
	printf ("\n m_inoder-> \n");
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

/*
 * Write a C program to determine the number of elements (or size) in a tree.
 */
int tree_size(void *_root) {
  tree_node *nn = (tree_node *)_root;
  if (nn==NULL) {
      return(0);
  } else {
      return(tree_size(nn->left) + tree_size(nn->right) + 1);
    }
}

/*
 * Write C code to determine if two trees are identical
*/
int identical(struct tree_node* a, struct tree_node* b)
{
  if (a==NULL && b==NULL){return(1);}
  else if (a!=NULL && b!=NULL)
    {
      return(a->data == b->data &&
	     identical(a->left, b->left) &&
	     identical(a->right, b->right));
    }
  else return(0);
}
/*
 * Write a C program to find the mininum value in a binary search tree.
 * Here is some sample C code. The idea is to keep on moving till you hit the left most node in the tree
 * On similar lines, to find the maximum value, keep on moving till you hit the right most node of the tree.
 */
int minValue(void* _root) {
  tree_node *node = (tree_node *)_root;
  struct tree_node* current = node;
  while (current->left != NULL) {
      current = current->left;
  }
  return(current->data);
}

/*
 * Write a C program to compute the maximum depth in a tree?
 */
int maxDepth(void* _root) {
  tree_node *node = (tree_node *)_root;
  if (node==NULL) {
      return(0);
  } else {
      int leftDepth = maxDepth(node->left);
      int rightDepth = maxDepth(node->right);
      if (leftDepth > rightDepth) return(leftDepth+1);
      else return(rightDepth+1);
    }
}

/*
 * Write a C program to create a mirror copy of a tree 
 * (left nodes become right and right nodes become left)!
 */

void *mirror_copy(void *_root) {
  tree_node *root = (tree_node *)_root;
  tree_node *temp = NULL;
  if (root == NULL)
    return (NULL);
  temp = (tree_node *)malloc(sizeof(tree_node));
  temp->data = root->data;

  temp->left  = mirror_copy(root->right);
  temp->right = mirror_copy(root->left);
  return (void *)(temp);
}

/*
 *Write a C program to create a copy of a tree
 */
tree_node *copy(void *_root)
{
  tree_node *root = (tree_node *)_root;
  tree_node *temp = NULL;
  if(root==NULL)
    return(NULL);
  temp = (tree_node *) malloc(sizeof(tree_node));
  temp->data = root->data;
  temp->left = copy(root->left);
  temp->right = copy(root->right);
  return(temp);
}

/*
 * Write C code to check if a given binary tree is a binary 
 * search tree or not?
 */
int isThisABST(void* _root)
{
  tree_node *node = (tree_node *)_root;
  if (node==NULL) return(1);
  if (node->left!=NULL && node->left > node->data)
    return(1);
  if (node->right!=NULL && node->right <= node->data)
    return(1);
  if (!isThisABST(node->left) || !isThisABST(node->right))
    return(1);
  return(1);
}
