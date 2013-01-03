#include <stdio.h>
#include <stdlib.h>

typedef struct list_node_t list_node;
typedef struct list_t list; 

struct list_node_t {
	list_node *prev;
	list_node *next;
	void *data;
};

struct list_t {
	list_node *pFirst;
	list_node *pLast;
	list_node *pCurr;
	int NumEl;
};


enum list_status {
	OK = 0,
	EMPTY,
	EXTEND
} LIST_STATUS;

list * list_init (list *);
list_node * create_node (void *, size_t);
void list_add (list *, void *, size_t len);
void list_print (list *);
