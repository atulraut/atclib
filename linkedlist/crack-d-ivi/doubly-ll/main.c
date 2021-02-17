/*
* Aim 	 : Doubly Circular Link List.
* Author : Atul Ramesh Raut
* Date   : Sunday August 21, 2016. 05:30PM
* File   : main.c
*
***/

#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int main() {
    int  ch, val;
    LIST *nw_list = NULL;
    nw_list = init_list (nw_list);
    if (NULL == nw_list)
      return 0;
    printf ("---------------------------------------------------");
    printf("\nEnter to the world of Atul Raut's Programing:\n");
    printf ("---------------------------------------------------");
    while(1) {
		printf("\n 0>Exit         \n 1>Add First      \n 2>Add Last     \n 3>Insert     \
                \n 4>Delete First \n 5>Delete Node    \n 6>Delete Last                  \
                \n 7>Display      \n 9>Print Reversly \n 10>Free list                   \
                \n 11>FindCir     \n \
                \n");
		printf ("------------------------------------------------");
		printf ("\n\t\t Welcome to World of LinkList :: \n");
		printf ("\t\t <====> :: ");
		scanf("%d", &ch);
		if (ch < 0 || ch > 11)
			return EXIT_SUCCESS ;
		switch(ch) {
			case 0:
				exit(0);
			case 1:
				printf("\nEnter the number : ");
				scanf("%d", &val);
				m_add (nw_list, val);
				break;

			case 2:
			m_insertionSort(nw_list);
				  //printf("\nEnter the number : ");
				  //scanf("%d", &val);
				  //m_Addlast(val);
				break;
/*				
			case 3:
				printf("\nEnter the number and position :");
				scanf("%d%d", &val,&pos);
				printf ("\n ---------------- ");
				m_Insert (val, pos);
				printf ("\n ---------------- ");
				break;
*/
			case 4:
			        m_free(nw_list);
				break;
/*
			case 5:
				printf("\nEnter the position :");
				scanf("%d",&pos);
				//m_Deletenode(pos);
				break;
			case 6:
				m_Dellast();
				break;
*/
			case 7:
				m_display(nw_list);
				break;

			case 9:
				m_Printrev(nw_list);
				break;
/*
			case 10:
				m_Freelist();
				break;
			case 11:
			        if(m_FindCircular())
			           printf ("Is is Cirular\n");
				else
				   printf ("Not circular\n");
				break;
*/
		        default : {
				printf("\nEnter the correct choice ");
				exit(0);
			}
		}
	}
	return 0;
}


