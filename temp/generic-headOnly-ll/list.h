#include <stdio.h>
#include <stdlib.h>

FILE *fr, *fw;
typedef struct node_t node;

typedef struct node_t {
	node *next;
	node *prev;
	void *data;
} node;

node *atclib_list;
int numEl;

node * list_init (node *);
node * createnode (void *, int len);
void addfirst (node *, void *, int);
void list_print (node *);
