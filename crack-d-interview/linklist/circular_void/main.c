/*
* Aim 	 : Singaly Circular Link List.
* Author : Atul Ramesh Raut
* Date   : Struday April 20, 2016. 10:30PM
* File   : main.c
*
***/

#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "../lib/lib.h"

int main() {
    LIST *nw_list = NULL;

    nw_list = init_list (nw_list);
    if (NULL == nw_list)
      return 0;

    start_ll(nw_list);

    return 0;
}
