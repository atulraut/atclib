/*
* Aim 	 : Simple tree implementation
* Author : Atul Ramesh Raut
* Date   : Thursday August 3, 2013. 12:31PM
* File   : main.c
*
***/

#include <stdio.h>
#include <stdlib.h>
#include "list.h"

tree_node *root = NULL;

int main() {
    int ch, val;
    root = create_node(45);
    printf ("---------------------------------------------------");    
    printf("\nEnter to the world of Atul Raut's Programing:\n");
    printf ("---------------------------------------------------");
    while(1) {
		printf("\n 0>Exit         \n 1>Add First      \n 2>Add Last     \n 3>Insert     \
                \n 4>Delete First \n 5>Delete Node    \n 6>Delete Last                  \
                \n 7>Display      \n 9>Print Reversly \n 10>Free list                   \
                \n 11>Search     \n \
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
				printf("\nJust Press Enter KEY : \n");
				//scanf("%d", &val);
//				m_add (nw_list, val);
				m_insert(root, 39);
				m_insert(root, 56);
/*				m_insert(root, 12);
				m_insert(root, 10);
				m_insert(root, 34);
				m_insert(root, 54);
*/				printf ("root       =%p \n", root);
				printf ("root->left =%p \n", root->left);
				printf ("root->right=%p \n", root->right);
				break;
/*
			case 2:
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
			case 4:
			        m_free(nw_list);
				break;

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
//				m_display(nw_list);
				m_preorder(root);
				break;
/*
			case 9:
				m_Printrev(nw_list);
				break;
*/
			case 10:
				m_delete_tree(root);
 				break;
			case 11:
				printf("\nEnter element to Search : \n");
				scanf("%d", &val);		
				m_search(root, val);
				break;

		        default : {
				printf("\nEnter the correct choice ");
				exit(0);
			}
		}
	}
	return 0;
}


