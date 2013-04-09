/*
* Aim  : WAP to implement Generic Linked list.
* Date : Saturday, Feb 2nd & 3rd 2013 12:00 AM
* By   : Atul R. Raut
* File : main.c menu to generic linked list.
*
***/

#include <stdio.h>
#include <stdlib.h>

#include "list.h"

#define MAXLINE 1000
int *linePtr[MAXLINE];

void list_menu (list *);
void list_add  (list *_list_atclib);
int readLine (int, FILE*);
int getLine (char s[], int, FILE*);
void init_file ();
void close_file ();

int main () {

  /*< Fileile open >*/
  init_file ();

  /*< Initialise the link list>*/
  list_atclib = init_list (list_atclib);
  /*< Show link list menu >*/
  list_menu (list_atclib);

  /*< file close >*/
  close_file ();
  return 0;
}

/*< Show link list menu >*/
void list_menu (list *_list_atclib) {
  int ch, val, pos;
  char *str;
  list_action action;

  while(1) {
    printf("\n 0>Exit\n 1>Add\n 2>Add First\n 3>Add Last \
                \n 4>Delete First\n 5>Delete Last\n 6>Delete Node\
                \n 7>Display\n 8>Print Revere \n 9>Free list                   \
                \n");
    printf ("------------------------------------------------");
    printf ("\n\t\t Welcome to World of LinkList :: \n");
    printf ("------------------------------------------------\n");
    printf ("\t <====> :: ");
    scanf("%d", &ch);
    action = ch;
    if (ch < 0 || ch > 10)
      return EXIT_SUCCESS ;
    switch(action) {
    case LIST_EXIT:
      exit(0);
    case LIST_ADD:
      if (NULL != _list_atclib) 
	list_add  (_list_atclib);
      break;
    case LIST_ADD_FIRST:
      //m_Addfirst (head, val, sizeof(val));
      break;
    case 3:
      printf("\nEnter the number and position :");
      scanf("%d%d", &val,&pos);
      printf ("\n ---------------- ");
      //m_Insert (val, pos);
      printf ("\n ---------------- ");
      break;
    case 4:
      //m_Delfirst();
      break;
    case 5:
      printf("\nEnter the position :");
      scanf("%d",&pos);
      //m_Deletenode(pos);
      break;
    case 6:
      //m_Dellast();
      break;
    case 7:
	print_list(_list_atclib);
      break;
    case LIST_REVERSE:
      printf ("\nReversing link list.\n");
      reverse_list (_list_atclib);
    case 9:
      //print_list();
      break;
    case 10:
      //m_Freelist();
      break;
    default : {
      printf("\nEnter the correct choice ");
      exit(0);
    } // default end
    } // switch end
  } // while end
}

/*< Fileile open >*/
void init_file () {
  fr = fopen ("rf.txt", "r");
  fw = fopen ("wf.txt", "w");
  if (NULL == fr || NULL == fw)
    printf ("\nfailed to open file !\n");
}

/*< close file >*/
void close_file () {
  fclose (fr);
  fclose (fw);
}

void list_add  (list *_list_atclib) {
  int numline, i;
  numline = readLine (MAXLINE, fr);
  for (i=0; i<numline; i++)
    add_list (_list_atclib, linePtr[i], sizeof (linePtr[i]));
}

int readLine (int maxline, FILE *fr) {
  int nline, numline;
  char s[maxline];
  char *strPtr;
  numline = 0;
  while ((nline = getLine (s, maxline, fr)) > 0) {
    if ( (strPtr = (char *)malloc(sizeof(s))) != NULL) {
      /*< if array of string is there we have to copy it using strcpy >*/
      strcpy (strPtr,s);
      linePtr[numline++] = strPtr;
    } else
      return 0;

  }
  return numline;
}

int getLine (char s[], int maxline, FILE *fr) {
  char c;	
  int i, lineNum;
  i = 0;
  lineNum = 0;
  while(--maxline>0 && (c = getc (fr)) != EOF && c != '\n') {
    s[i] = c;
    i++;
  }
  if (c == '\n') {
    s[i] = '\0';
    i=0;
    lineNum++;
  }
  return lineNum;	
}
