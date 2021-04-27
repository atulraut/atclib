/***
    Easy: N-ary Tree Preorder Traversal

    Given the root of an n-ary tree, return the preorder traversal
    of its nodes' values.

    Nary-Tree input serialization is represented in their level order
    traversal.
    Each group of children is separated by the null value (See examples)

    Input: root = [1,null,3,2,4,null,5,6]
    Output: [1,3,5,6,2,4]

    https://leetcode.com/problems/n-ary-tree-preorder-traversal/
 */

/**
 * Definition for a Node.
 * struct Node {
 *     int val;
 *     int numChildren;
 *     struct Node** children;
 * };
 */

/**
 * Note: The returned array must be malloced, assume caller calls free().
 * 8ms
 */
int* preorder2(struct Node* root, int* returnSize)
{
  if(!root)
    {
      *returnSize = 0;
      int* ret = malloc(sizeof(int));
      return(ret);
    }

  else
    {
      int* ret = malloc(sizeof(int) * 10000);
      struct Node* stack[1000];
      int top = -1, i = 0, j;

      stack[++top] = root;

      while(top != -1)
        {
  struct Node* ptr = stack[top];
  ret[i++] = ptr->val;
  top--;

  for(j=(ptr->numChildren - 1); j>=0; j--)
            {
      stack[++top] = ptr->children[j];
            }
        }

      *returnSize = i;
      return(ret);
    }

  return(NULL);
}

void preorder_cnt(struct Node* root, int* returnSize) {
  int i;

  if (root == NULL)
    return;

  (*returnSize)++;

  for (i = 0; i < root->numChildren; i++)
    preorder_cnt(root->children[i], returnSize);
}

void preorder_traversal(struct Node* root, int* arr, int* idx) {

  int i;

  if (root == NULL)
    return;

  arr[(*idx)] = root->val;
  (*idx)++;

  for (i = 0; i < root->numChildren; i++)
    preorder_traversal(root->children[i], arr, idx);
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* preorder(struct Node* root, int* returnSize) {

  int* res = NULL;
  int idx = 0;

  *returnSize = 0;
  preorder_cnt(root, returnSize);

  res = (int*)malloc(sizeof(int) * (*returnSize));

  preorder_traversal(root, res, &idx);

  return res;
}

int main() {
  struct Node rt[4];
  // Fix Me.
  rt[0] = (struct Node) {.val=1, .left=NULL, .right=NULL};
  rt[1] = (struct Node) {.val=2, .left=NULL, .right=NULL};
  rt[2] = (struct Node) {.val=3, .left=NULL, .right=NULL};
  rt[3] = (struct Node) {.val=4, .left=NULL, .right=NULL};

  rt[0].left  = &rt[1];  // 1 <-- 0 [0's left]
  rt[0].right = &rt[2];  // 0 --> 3 [0's right]
  rt[1].left  = &rt[3];  // 1 <-- 2 [2's left]

}

