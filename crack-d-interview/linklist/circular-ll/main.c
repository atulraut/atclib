/*
* Aim :  Create Singly Circular Link List
* Date : 25-03-2010
*
***/

#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int main()
{
    printf("Hello world!\n");
    int  ch, val,pos;
	printf("\nEnter to the world of AR Raut:");
	getch();
	while(1)
	{
		system("cls");
		printf("\n 0>Exit         \n 1>Add First      \n 2>Add Last     \n 3>Insert     \
                \n 4>Delete First \n 5>Delete Node    \n 6>Delete Last                  \
                \n 7>Display      \n 9>Print Reversly \n 10>Free list                   \
                \n");
		scanf("%d", &ch);
		switch(ch)
		{
			case 0:
					exit(0);
			case 1:
					printf("\nEnter the number : ");
					scanf("%d", &val);
					m_Addfirst (val);
					break;
			case 2:
                    printf("\nEnter the number : ");
					scanf("%d", &val);
					m_Addlast(val);
					break;
			case 3:
					printf("\nEnter the number and position :");
					scanf("%d%d", &val,&pos);
                    printf ("\n>>>>>>>>> ");
					m_Insert (val, pos);
					printf ("\n>>>>>>>>> ");
					break;
			case 4:
			//		delfirst();
					break;
			case 5:
					printf("\nEnter the position :");
					scanf("%d",&pos);
			//		deletenode(pos);
					break;
			case 6:
			//		dellast();
					break;
			case 7:
					m_Display();
					break;
			case 9:
			//		printrev(head);
					break;
			case 10:
			//		freelist();
					break;
			default :
					printf("\nEnter the correct choice ");
		}
		getch();
	}
	return 0;
}

