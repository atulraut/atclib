#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/*
  Example BST:
       17
      /  \
     /    \
    4      23
   / \     / \
  2   11  21  30
     /  \     /
    7    12  25
   / \
  6   9
*/

// 30, 25, 23, 21, 17, 12, 11, 9, 7, 6, 4, 2

struct node {
  int value;
  struct node* left;
  struct node* right;
  struct node* parent;
};

struct node* createNode(int value, struct node * parent, int isLeftChild) {
  struct node* n = (struct node*)malloc(sizeof(struct node));
  n->value = value;
  n->left = 0;
  n->right = 0;
  n->parent = parent;
  if (parent != 0) {
    if (isLeftChild==1){
      parent->left = n;
    } else {
      parent->right = n;
    }
  }
  return n;
}

void freeNodes(struct node* node) {
  if (node->right!=0) freeNodes(node->right);
  if (node->left!=0) freeNodes(node->left);
  free(node);
}

// maxNode returns the maximum node of the BST rooted at n.
// Assume that n will never be NULL
struct node* findMax(struct node* n) {
  // Your code here
  struct node* trav = n;
  while (trav->right != NULL)
    trav = trav->right;

  return (trav);
}

// findPrev returns the node with the next value less
// than the given node in the entire BST
// For example, the next lower value of 30 is 25
// If the given node is the smallest, return NULL.
struct node* findPrev(struct node* n) {
    // Your code here
    if(n->left)  {
       n = n->left;
    while (n->right)
      n = n->right;
    return   n;
    }
      int temp = n->value;
     while (n->parent && temp < n->parent->value)
      n = n->parent;
    return (n->parent);
    }

// printReverse prints the values of the BST in descending order.
// The root is passed in.
// 30, 25, 23, 21, 17, 12, 11, 9, 7, 6, 4, 2
void printReverse(struct node* r) {
  // Your code here
  printf ("\n");
  if (!r)
    return;
  // findMax => 30 ->print,
  // while findPrev:
  //    print more
  struct node* curr =  findMax(r);
  //printf ("%d", curr->value);
  while(curr) {
    printf ("->%d", curr->value);
    curr = findPrev(curr);
  }
  printf ("\n");
}

void test() {
  struct node* n1 = createNode(17, 0, 0);
  struct node* n2 = createNode(4, n1, 1);
  struct node* n3 = createNode(11, n2, 0);
  createNode(2, n2, 1);
  struct node* n5 = createNode(7, n3, 1);
  createNode(12, n3, 0);
  struct node* n7 = createNode(23, n1, 0);
  createNode(9, n5, 0);
  struct node* n9 = createNode(30, n7, 0);
  createNode(25, n9, 1);
  createNode(21, n7, 1);

  printReverse(n1);

  freeNodes(n1);
}

int main() {

  test();

  return 0;
}


