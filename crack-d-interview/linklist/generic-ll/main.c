/*
* Aim  : WAP to implement Generic Linked list.
* Date : Monday, April 16 2012 06:45 PM
       : Saturday, January 5th 6th 2013 12:00 PM
* By   : Atul R. Raut, Hyderabad
* File : main.c contents UI to linked list.
*
***/

#include <stdio.h>
#include <stdlib.h>
#include "list.h"

#define MAXLINE 6
#define MAXLINES 1000 /* lines to be sorted */

char *lineptr [MAXLINES]; /*pointers to next line*/

/* Forward declaration */
int readlines ( char *lineptr[], int nlines, FILE *fr);
int getLine (char line[], int max, FILE *fr);
void add_to_list ();

int main() {
    int  ch, val, _data, pos;
    fr = fopen ("rf.txt", "r");
    fw = fopen ("wt.txt", "w");
    if (fr == NULL || fw == NULL) {
        printf ("\n File can't open !\n");
        exit (0);
    }
    printf ("\nlist size = %d, list_node size = %d\n", sizeof(list), sizeof(list_node));

//    list_node *atclib_list = NULL;   // create empty list, can create no. of such list
    atclib_list = list_init (atclib_list);
    printf ("\nNext to list_init\n");
    fr = fopen ("rf.txt", "r");
    if (fr == NULL) {
       printf ("\n File can't open !");
       exit (0);
    }
    printf ("---------------------------------------------------");
    printf("\nEnter to the world of Atul Raut's 'C' Programing:\n");
    printf ("---------------------------------------------------");
    while(1) {
                printf("\n 0>Exit         \n 1>Add First      \n 2>Add Last     \n 3>Insert     \
                \n 4>Delete First \n 5>Delete Node    \n 6>Delete Last                  \
                \n 7>Display      \n 9>Print Reversly \n 10>Free list                   \
                \n");
                printf ("------------------------------------------------");
                printf ("\n\t\t Welcome to World of LinkList :: \n");
                printf ("\t\t <====> :: ");
                scanf("%d", &ch);
    if (ch < 0 || ch > 10)
        return EXIT_SUCCESS ;
    switch(ch) {
              case 0:
                 exit(0);
              case 1:
                 add_to_list ();
                 break;
              case 2:
                 printf("\nEnter the number : ");
                 scanf("%d", &val);
                 //m_Addlast(val);
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
                 list_print(atclib_list);
                 break;
              case 9:
                 //m_Printrev();
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
 // close file
  fclose (fr);
  fclose (fw);
  return 0;
}

int readlines ( char *lineptr[], int maxlines, FILE *fr) {
   int iLine, nLines;
   char line[maxlines];
   char *cPtr = NULL;
   nLines = 0;
   while (iLine = getLine (line, maxlines, fr) > 0) {
       if (iLine >= maxlines || (cPtr = (char *) malloc (strlen(line+1))) == NULL) {
            printf ("\n returing\n");
            return -1;
       } else {
                if (cPtr == NULL)
                    return;
                strcpy (cPtr, line);
                lineptr[nLines++] = cPtr;
                 //printf ("\n ATUL: lineptr = %s, cPtr=%s, line=%s\n", lineptr[nLines-1], cPtr, line);
       }
   } // while  ends
  return nLines;
}

/*
* getLine : get 1 line from file into s, return length
***/
int getLine (char s[], int maxline, FILE *fr) {
    char c;
    int i;
    i = 0;
    while (--maxline > 0 &&  (c = getc(fr)) != EOF && c!= '\n') {
          s[i] = c;
          i++;
    }
    if (c == '\n') {
       s[i] = '\0';
       i++;
    }
    return i;
}

void add_to_list () {
    int len, maxline, i;
    char c;
    char str[100];
    len = 0; i = 0;
    // get input from file, add to link list.
    maxline = readlines (lineptr, MAXLINES, fr);
    printf ("\nmaxlines = %d\n", maxline);
    for(i=0; i<maxline; i++) {
      list_add (atclib_list, lineptr[i], strlen(lineptr[i]));
    }
}
