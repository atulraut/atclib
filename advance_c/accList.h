#ifndef ACCLIST_H
#define ACCLIST_H

#include <stdio.h>
#include <stdlib.h>

struct accListNode                 //the nodes of a linked-list for any data type
{
  void *data;                     //generic pointer to any data type
  struct accListNode *next;       //the next node in the list
};

struct accList                    //a linked-list consisting of accListNodes
{
  struct accListNode *head;
  struct accListNode *tail;
  int size;
};

//allocate the accList and set to NULL
void accList_allocate(struct accList *theList); 
//append data to the end of the accList
void appendToEnd(void *data, struct accList *theList);    
//removes data from accList
void removeData(void *data, struct accList *theList);         

#endif
