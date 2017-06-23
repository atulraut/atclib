#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _node {
  void *data;
  struct _node *next;
} NODE;

typedef struct _list {
  struct _node *head;
} LIST;

struct check {
   int i;
   char c; 
   double d; 
} chk[] = { { 1, 'a', 1.1 }, { 2, 'b', 2.2 }, { 3, 'c', 3.3 } };

LIST* m_init(void *);
void  m_insert(void *_ptr, void *data, int sz);
void m_print (void *_ptr, void(*)(void *));
void m_print_char(void *_ptr);
void m_print_str(void *_ptr);
void m_print_int(void *_ptr);
void m_printcomp(void *_ptr);

int main () {
  char ch[] = {'a', 'b', 'c'};
  char *str[] = {"Atul", "Raut"};
  int j[] = {10, 20, 30};

  LIST *list1, *list2, *list3, *list4;
  LIST lst, lst2, lst3, lst4; 
  list1 = m_init(&lst);
  list2 = m_init(&lst2);
  list3 = m_init(&lst3);
  list4 = m_init(&lst4);
  /* char */
  m_insert(list1, &ch[0], sizeof(ch[0]));
  m_insert(list1, &ch[1], sizeof(ch[1]));
  m_print (list1, m_print_char);
  /* string */
  m_insert(list2, str[0], (strlen(str[0])) );
  m_print (list2, m_print_str);
  /* int */
  printf("Printing INT:\n"); 
  m_insert(list3, &j[0], sizeof(int));
  m_print (list3, m_print_int);
  printf(" : done INT\n"); 
  /* composite */
  m_insert(list4, &chk[0], sizeof(chk[0]));
  //  m_insert(&list4, &chk[1], sizeof chk[1]);
  //m_insert(&list4, &chk[2], sizeof chk[2]); 
  printf("Printing composite:\n"); 
  m_print(list4, m_printcomp); 
  printf(" : done\n"); 
}

LIST* m_init(void *_ptr) {
    LIST *l1 = (LIST *)_ptr;
    l1 = (LIST *)malloc(sizeof(LIST));
    l1->head = NULL;
    return l1;
}

void  m_insert(void *_ptr, void *data, int sz) {
  LIST *l1 = (LIST *)_ptr;
  NODE *temp = NULL;
  int i = 0;
  temp = (NODE *)malloc(sizeof(NODE));
  temp->data = (void *)malloc(sizeof(sz)+1);
  for (i=0; i<sz; i++) {
    //    printf ("data = %c\n", *(char *)(data+i));
    *(char *)(temp->data+i) = *(char *)(data+i);
  }
  if (l1->head == NULL)
    l1->head = temp;
  else {
    NODE *trav =(NODE *)l1->head;
    while (trav->next != NULL)
      trav = trav->next;
    trav->next = temp;
    temp->next = NULL;
  }
}

void m_print (void *_ptr, void(*f)(void *diz_ptr)) {
  LIST *l1 = (LIST *)_ptr;
  NODE *trav = l1->head;
  //  printf ("data = %c\n", *(char *)(trav->data));
  while (trav) {
    (*f)(trav->data);
    trav = trav->next;
  }
}

void m_print_char(void *_ptr) {
    printf(" %c\n", *(char *)_ptr);
}

void m_print_str(void *_ptr) {
  printf("\"%s\"", (char *)_ptr); 
  printf ("\n");
}

void m_print_int(void *_ptr) {
  printf(" %d \n", *(int *)_ptr);
}

void m_printcomp(void *comp)
{
  printf("REACHED : %d, %s\n", __LINE__, __FILE__);
  struct check temp = *(struct check *)comp; 
  printf(" '%d:%c:%f", temp.i, temp.c, temp.d); 
}





