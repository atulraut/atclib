/*
* Aim  : WAP to implement Generic Linked list.
* Date : Monday, April 16 2012 06:45 PM
* By   : Atul R. Raut
* File : main.c contents UI to linked list.
*
***/

#include <stdio.h>
#include <stdlib.h>
#include "list.h"

#define MAXLINE 6
int main() {
    int  ch, val,_data,pos, i, s[100];
    char c;
    FILE *fr = NULL;
    char *linePtr[MAXLINE]; /*pointer to next line*/

    printf ("\nlist size = %d\n", sizeof(list));    
    list_node *atclib_list = NULL;   // create empty list, can create no. of such list
    atclib_list = list_init (atclib_list);
    printf ("\nNext to list_init\n");
    i = 0;
    fr = fopen ("rf.txt", "r");
    if (fr == NULL) {
    	printf ("\n File can't open !");
   	exit (0);
    }
    while ((c=getc(fr)) != EOF) {
	if (c == '\n') 
	      continue;
	else {
		s[i] = c;
		i++;	
	}
//	printf ("\n c >>>>> %c\n", c);
   }
    printf ("---------------------------------------------------");    
    printf("\nEnter to the world of Atul Raut's 'C' Programing:\n");
    printf ("---------------------------------------------------");
    while(1) {
//		system("clear");
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
		switch(ch)
		{
			case 0:
				exit(0);
			case 1:
///				printf("\nEnter the number : ");
///				scanf("%d", &_data);
				list_add (atclib_list, 10, 2);
				break;
			case 2:
				printf("\nEnter the number : ");
				scanf("%d", &val);
//				m_Addlast(val);
				break;
			case 3:
				printf("\nEnter the number and position :");
				scanf("%d%d", &val,&pos);
				printf ("\n ---------------- ");
//				m_Insert (val, pos);
				printf ("\n ---------------- ");
				break;
			case 4:
//				m_Delfirst();
				break;
			case 5:
				printf("\nEnter the position :");
				scanf("%d",&pos);
//				m_Deletenode(pos);
				break;
			case 6:
//				m_Dellast();
				break;
			case 7:
				list_print(atclib_list);
				break;
			case 9:
//				m_Printrev();
				break;
			case 10:
//				m_Freelist();
				break;
		        default : {
				printf("\nEnter the correct choice ");
				exit(0);
			}
		}
	}
	return 0;
}


