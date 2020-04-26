/*
* Copyright (c) 2013-2020, The ReRam Foundation. All rights reserved.
* GPL-2.0-only
* Aim 	 : Simple tree implementation
* Author : Atul Raut
* Date   : Thursday August 3, 2013. 12:31PM
* File   : main.c
*
***/

#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int main() {
    int ch, val;
    tree_node *root = NULL;
    root = create_node(1);
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
			  //printf("\nJust Press Enter KEY : \n");
				//scanf("%d", &val);
//				m_add (nw_list, val);
				m_insert(root, 2);
				m_insert(root, 3);
				m_insert(root, 4);
				m_insert(root, 5);
				m_insert(root, 6);
				m_insert(root, 7);
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
				//			printf("\nTree_height--> %dn",tree_height(root));
				//			printf("\nminValue--> %dn", minValue(root));
		tree_node *root_new = NULL;
/*
			root_new = create_node(5);
			root_new = mirror_copy(root);
			printf ("\n mirror_copy --> \n");
			m_preorder(root_new);
			tree_node *newCopy = NULL;
			newCopy = copy (root);
			printf ("\nNew Copy Tree -->");
			m_preorder(root_new);
			printf ("\n isThisABST = %d\n", isThisABST(root_new));
*/
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
