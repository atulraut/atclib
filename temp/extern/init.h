#include <stdio.h>
#include <stdlib.h>

typedef struct _init_config {
  int *isUpgraded;
  int flag;
} init_config;

init_config *head;

int init (int *isUp);
