#ifndef ADD_H_LIST
#define ADD_H_LIST

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

#define debug(str,args...) printf("[%s] L=%d :"str"\n", __func__, __LINE__, ##args)

struct list_node {
    int data;
    struct list_node *next;
} list_node;

struct list {
  struct list_node *head;
} list;

/* Creating Two Linked List */
struct list *list1;
struct list *list2;
struct list *l_base;

int counter;
struct list* m_Init (struct list *);
void m_Addfirst(void*);
void m_Addlast(void *);
void m_Delfirst(void *);
void m_Display(void *);
void m_Dellast(void *);
void middleNode(void *);
void m_Freelist(void *);
void m_quit(void *);
void m_isPalindrome(void *);

#define debug(str,args...) printf("[%s] L=%d :"str"\n", __func__, __LINE__, ##args)

#endif
