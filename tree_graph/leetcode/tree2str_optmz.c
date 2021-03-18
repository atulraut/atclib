/***
    606. Construct String from Binary Tree
    Ref : https://leetcode.com/problems/construct-string-from-binary-tree/

    You need to construct a string consists of parenthesis and integers
    from a binary tree with the preorder traversing way.

    The null node needs to be represented by empty parenthesis pair "()".
    And you need to omit all the empty parenthesis pairs that don't affect
    the one-to-one mapping relationship between the string and the original
    binary tree.
    Example 1:
    Input: Binary tree: [1,2,3,4]
      1
    /   \
   2     3
  /
 4

    Output: "1(2(4))(3)"
    Explanation: Originallay it needs to be "1(2(4)())(3()())",
    but you need to omit all the unnecessary empty parenthesis pairs.
    And it will be "1(2(4))(3)".

    Example 2:
    Input: Binary tree: [1,2,3,null,4]
      1
    /   \
    2     3
     \
      4

    Output: "1(2()(4))(3)"
    Explanation: Almost the same as the first example,
    except we can't omit the first parenthesis pair to break the one-to-one mapping
    relationship between the input and the output.

    Date : 16 March 2021.
    San Diego, CA
*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>
#include <string.h>  /* malloc */
#include <stdbool.h>
#include <math.h>
#include <assert.h>
#include <stdint.h> /* uint32_t */
#include <unistd.h> /* sleep */

/***
    In case File Debug Option needs to Enabled.
*/
//#define debug(str,args...) printf("[%s] [%s()] L=%d :"str"\n",__FILE__, __func__, __LINE__, ##args)

#define debug(str,args...) printf("[%s] L=%d :"str"\n", __func__, __LINE__, ##args)

struct tree_node {
  int val;
  struct tree_node *left;
  struct tree_node *right;
};

//preorder = root left right

void tree_to_string(struct tree_node* root, char* ret) {
  int idx = 0;
  if(root == NULL)
    return;

  idx +=sprintf(ret+idx, "%d", root->val);

  if(root->left == NULL && root->right == NULL)
    return ;
  else {

    idx +=sprintf(ret+idx, "(");
    tree_to_string(root->left,  ret+idx);
    idx +=sprintf(ret+strlen(ret), ")");

    if(root->right) {
      idx +=sprintf(ret+strlen(ret), "(");
      tree_to_string(root->right,  ret+strlen(ret));
      idx +=sprintf(ret+strlen(ret), ")");

    }
    return;
  }
}

char * tree2str(struct tree_node* root) {
  if(root == NULL)
    return "";
  char* ret = (char*)calloc(1024*1024, sizeof(char));

  if(ret == NULL)
    return NULL;
  tree_to_string(root, ret);

  return ret;
}

/* Old Code */
char result[100000]={0};
int j;
struct tree_node* tGlobal;
void preorder(struct tree_node* rt,int flag) {
  if(rt == NULL) {
    //if(flag== 0 && tGlobal->right != NULL) { // NOT BST Tree
    if(flag== 0  && tGlobal->right != NULL && tGlobal->left != NULL) {                             // For BST Tree
      result[j] = '(';
      j++;
      result[j] = ')';
      j++;
    }
    return;
  }

  result[j]='(';
  j++;
  j= j+sprintf(result+j, "%d", rt->val);
  tGlobal = (struct tree_node*)malloc(sizeof(struct tree_node));
  tGlobal = rt;
  preorder(rt->left,0);
  preorder(rt->right,1);
  result[j]=')';
  j++;
}

int main () {
  struct tree_node rt[4];

  /* Initialize the Tree as per Example 1 above */
  rt[0] = (struct tree_node) {.val=1, .left=NULL, .right=NULL};
  rt[1] = (struct tree_node) {.val=2, .left=NULL, .right=NULL};
  rt[2] = (struct tree_node) {.val=3, .left=NULL, .right=NULL};
  rt[3] = (struct tree_node) {.val=4, .left=NULL, .right=NULL};

  rt[0].left  = &rt[1];  // 1 <-- 0 [0's left]
  rt[0].right = &rt[2];  // 0 --> 3 [0's right]
  rt[1].left  = &rt[3];  // 1 <-- 2 [2's left]

  //preorder (rt, 0);
  char *ret = tree2str(rt);

  for (int i=0; i<strlen(ret); i++) {
    printf ("%c ", ret[i]);
    //debug ("--> %c", ret[i]);
  }
  printf ("\n");
  return 0;
}

/**
   => ./a.out
   1 ( 2 ( 4 ) ) ( 3 ) - Default
**/

