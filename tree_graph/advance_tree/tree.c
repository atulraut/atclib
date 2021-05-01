#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
	int data;
	struct node *left;
	struct node *right;
};

struct node* m_Init (struct node *ll){
  memset((void *)ll, 0, sizeof(struct node));
  ll = malloc (sizeof (struct node));
  ll->right = NULL;
  ll->left = NULL;
  ll->data = -1;
  return ll;
}

//Function to find minimum in a tree.
struct node* m_FindMin(void *ptr) {
  struct node* root = (struct node*)ptr;

  while(root->left != NULL) root = root->left;
  return root;
}

// Function to search a delete a value from tree.
struct node* m_Delete(void *ptr, int data) {
  struct node* root = (struct node*)ptr;

  if(root == NULL) return root;
  else if(data < root->data) root->left = m_Delete(root->left,data);
  else if (data > root->data) root->right = m_Delete(root->right,data);
  // Wohoo... I found you, Get ready to be deleted
  else {
    // Case 1:  No child
    if(root->left == NULL && root->right == NULL) {
      free(root);
      root = NULL;
    }
    //Case 2: One child
    else if(root->left == NULL) {
      struct node *temp = root;
      root = root->right;
      free(temp);
    }
    else if(root->right == NULL) {
      struct node *temp = root;
      root = root->left;
      free(temp);
    }
    // case 3: 2 children
    else {
      struct node *temp = m_FindMin(root->right);
      root->data = temp->data;
      root->right = m_Delete(root->right,temp->data);
    }
  }
  return root;
}

//Function to visit nodes in Inorder
void m_Inorder(void *ptr) {
  struct node* root = (struct node*)ptr;

  if(root == NULL) return;

  if(NULL != root->left) {
    m_Inorder(root->left);       //Visit left subtree
  }
  printf("[%s]    -->[%d]\n",__func__, root->data);  //Print data
  if(NULL != root->right) {
    m_Inorder(root->right);      // Visit right subtree
  }
}

void m_Preorder(void *ptr) {
  struct node *nn = (struct node *)ptr;

  printf("[%s]  ->[%d]\n",__func__, nn->data);

  if(nn == NULL)
    return;
  if(NULL != nn->left)
    m_Preorder(nn->left);
  if(NULL != nn->right)
    m_Preorder(nn->right);
}

void m_Postorder(void *ptr) {
  struct node *nn = (struct node *)ptr;

  if(nn == NULL)
    return;
  if(NULL != nn->left)
    m_Postorder(nn->left);
  if(NULL != nn->right)
    m_Postorder(nn->right);
  printf("[%s] ->[%d]\n", __func__, nn->data);
}

// Function to Insert Node in a Binary Search Tree
struct node* m_Insert(void *ptr, int data) {
  struct node* root = (struct node*)ptr;
re
  if(root == NULL) {
    root = (struct node *)malloc(sizeof(struct node));
    root->data = data;
    root->left = root->right = NULL;
    printf("[%s] ->[%d]\n", __func__, root->data);
  }
  else if(data <= root->data)
    root->left = m_Insert(root->left,data);
  else
    root->right = m_Insert(root->right,data);
  return root;
}

int main() {
  /*Code To Test the logic
    Creating an example tree
    5
    / \
    3   10
    / \  / \
    1   4 9  11
  */
  struct node* root = NULL;

  root = m_Insert(root,5); root = m_Insert(root,10);
  root = m_Insert(root,3); root = m_Insert(root,4);
  root = m_Insert(root,1); root = m_Insert(root,9);
  root = m_Insert(root,11);

  /*
    root = m_Insert(root,1); root = m_Insert(root,3);
    root = m_Insert(root,2); root = m_Insert(root,5);
    root = m_Insert(root,4); root = m_Insert(root,6); root = Insert(root,7);
  */
  // Deleting node with value 5, change this value to test other cases
  //	root = Delete(root,5);

  //Print Nodes in Inorder
  printf ("Inorder: \n");
  //m_Inorder(root);
  m_Preorder(root);
  //m_Postorder(root);
  printf ("\n");
  root = m_Delete(root,10);
  m_Preorder(root);
}
