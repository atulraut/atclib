#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define STR "now is the time for all good men to come to the aid of their party"
#define MAXWORD 100

struct tnode *addtree (struct tnode *, char *);
void treeprint (struct tnode *);
int getword (char *, int);
struct tnode talloc (void);
char *my_strdup (chat *s);
void my_free (char *strdup);

typedef struct tnode_t {        /* the tree node:   */ 
	char *word;             /* points to the text*/
	int count;              /* number of occurences */
	struct tnode_t *left;   /* left child */
	struct tnode_t *right;  /* right child */
} tnode;

int main() {
    struct tnode *root = NULL;
    char word[MAXWORD];

    printf("\nHello World %s\n", STR);
    while (getword(word, MAXWORD) != EOF) 
      if (isalpha(word[0]))
	root = addtree(root, word);
    
    treeprint (root);
    return 0;
}

struct tnode *addtree (struct tnode *root, char *word) {

}

void treeprint (struct tnode *root) {

}

/* getword: get next word or character from input */
int getword (char *word, int lim) {
  FILE *fr = NULL;
  FILE *fw = NULL;
  fr = fopen ("at.txt", "r");
  fw = fopen ("wt.txt", "w");
  if (fr == NULL || fw == NULL) {
    printf ("\n File can't open !");
    exit (0);
  }

  if ( (nlines = readlines (lineptr, MAXLINES, fr)) >= 0) {
    qsort_n (lineptr, 0, nlines-1);
    writelines (lineptr, nlines);
    return 0;
  } else {
    printf ("\nerror: input line too big to handled.\n");
    return 1;
  }

}

/* talloc: make a tnode */
struct tnode talloc (void) {
  return (struct tnode *) malloc (sizeof(struct tnode));
}

char *my_strdup (chat *s) { /* make a duplicate of s */
  char *p = NULL;
  p = (char *) malloc (strlen (s)+1);  /* +1 for '\0'*/
  if (p != NULL) 
    strcpy (p, s);
  return p;
}

void my_free (char *strdup) {
  free (strdup);
}


