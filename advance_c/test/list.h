#include <stdio.h>
#include <stdlib.h>


typedef struct _head {
	FILE *fr;
	int kill;
}head;

head *head_ptr;

void test_one ();
void test_two ();
