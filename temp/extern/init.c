#include <stdio.h>
#include <stdlib.h>
#include "init.h"
#include "interrupt.h"

int init (int *m_isUp) {

    printf ("\n[init] init.c\n");

    head = (init_config *)malloc(sizeof(init_config));
    head->isUpgraded = m_isUp;// false;
    //head->flag = 0;
    upgrade(head->isUpgraded);
    if (*head->isUpgraded == 1)
      printf ("\n[init] true ");
    else
      printf ("\n[init] false ");
    return 0;
}

