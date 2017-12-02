#include <stdio.h>

typedef struct node {
  int value;
  struct node *right;
  struct node *left;
} mynode;

mynode *root;
add_node(int value);
void levelOrderTraversal(mynode *root);

int main(int argc, char* argv[]) {
  root = NULL;
  add_node(5);
  add_node(1);
  add_node(-20);
  add_node(100);
  add_node(23);
  add_node(67);
  add_node(13);
  printf("\n\n\nLEVEL ORDER TRAVERSAL\n\n");
  levelOrderTraversal(root);
}

// Function to add a new node...
add_node(int value) {
  mynode *prev, *cur, *temp;
  temp = (mynode *) malloc(sizeof(mynode));
  temp->value = value;
  temp->right = NULL;
  temp->left  = NULL;
  if(root==NULL) {
      printf("\nCreating the root..\n");
      root = temp;
      return;
    }
  prev=NULL;
  cur=root;
  while(cur!=NULL) {
      prev=cur;
      cur=(value<cur->value)?cur->left:cur->right;
  }
  if(value < prev->value)
    prev->left=temp;
  else
    prev->right=temp;
}
// Level order traversal..
void levelOrderTraversal(mynode *root) {
  mynode *queue[100] = {(mynode *)0}; // Important to initialize!
  int size = 0;
  int queue_pointer = 0;
  while(root) {
    printf("[%d] ", root->value);
    if(root->left) {
      queue[size++] = root->left;
    }
    if(root->right) {
      queue[size++] = root->right;
    }
     root = queue[queue_pointer++];
 }
}
