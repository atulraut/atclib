/*
* Aim :  Create Singly Link List
* Date : July-29-2016
*
***/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "list.h"

int main()
{
    int ch;
    int  val;
    LIST *l;
    l = m_Init();
    printf ("---------------------------------------------------");
    printf("\nEnter to the world of Atul Raut's Programing:\n");
    printf ("---------------------------------------------------");
    while(1) {
		printf("\n 0>Exit         \n 1>Add First      \n 2>Add Last     \n 3>Insert     \
                \n 4>Delete First \n 5>Delete Node    \n 6>Delete Last                  \
                \n 7>Display      \n 9>Print Reversly/m_ReturnNthNode_From_End \n 10>Free list                   \
                \n 11>Reverse ll \n 12>Reverse kth ll  \n 13>Sort List      \
                \n");
		printf ("------------------------------------------------");
		printf ("\n\t\t Welcome to World of LinkList :: \n");
		printf ("\t\t <====> :: ");
		scanf("%d", &ch);
		if(isalpha(ch) != 0) {
		  printf("%d is not a digit.",ch);
		  return EXIT_SUCCESS ;
		} else
		    printf("%d is a digit.",ch);
		switch(ch) {
			case 0:
			  printf("Exiting \n");
				exit(0);
			case 1:
				printf("\nEnter the number : ");
				scanf("%d", &val);
				m_Addfirst (val, l);
				break;
/*			case 2:
				printf("\nEnter the number : ");
				scanf("%d", &val);
				m_Addlast(val);
				break;
			case 3:
				printf("\nEnter the number and position :");
				scanf("%d%d", &val,&pos);
				printf ("\n ---------------- ");
				m_Insert (val, pos);
				printf ("\n ---------------- ");
				break;
*/
			case 4:
				m_Delfirst(l);
				break;
/*
			case 5:
				printf("\nEnter the position :");
				scanf("%d",&pos);
				m_Deletenode(pos);
				break;
			case 6:
				m_Dellast();
				break;
*/			case 7:
				m_Display(l);
				break;

			case 9:
//				m_Printrev();
				m_ReturnNthNode_From_End(l, 3);
				break;

			case 10:
				m_Freelist(l);
				break;
			case 11:
			        m_Revlist(l);
				break;
			case 12:
				printf("\nEnter the kth node to reverse \n");
				scanf("%d", &val);
				m_RevlistKthNode(l, val);
					break;
			case 13:
				m_Sortlist(l);
				break;
		        default : {
				printf("\nEnter the correct choice \n\n");
				exit(0);
			}
		}
	}
	return 0;
}


