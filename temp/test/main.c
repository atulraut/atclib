#include <stdio.h>
#include "list.h"

int main () {
        head_ptr = (head *)malloc(sizeof(head));
	test_one ();
	test_two ();
	return 0;
} 

void test_one () {
  char c;
  (head_ptr->fr) = fopen ("rf.txt", "w");
	printf ("\n address here. =%p\n", head_ptr->fr);
	if (head_ptr->fr == NULL) {
		printf ("\n File can't open !\n");
		exit (0);
	}
	//	fputs ("ATUL", head_ptr->fr);
	fputc ('B', head_ptr->fr);
        //fputc ('\n', head_ptr->fr);
	c = getc (head_ptr->fr);
       printf ("\n Atul = %c\n", c);
     
       while((c = getc (head_ptr->fr)) != EOF) {
	       printf ("\n Atul = %c\n", c);
       }
	//fclose (head_ptr->fr);
}

void test_two () {
       char c = 'R';
	printf ("\n address 2 here. =%p\n", head_ptr->fr);
          //head_ptr->fr = fopen ("rf.txt", "r");
       if (head_ptr->fr == NULL) {
		printf ("\n File can't open !\n");
		exit (0);
       }
       while((c = getc (head_ptr->fr)) != EOF) {
	       printf ("\n Atul = %c\n", c);
       }
       printf ("\n Inside two post while");
       fclose (head_ptr->fr);
       printf ("\n Inside two post file close \n");
}
