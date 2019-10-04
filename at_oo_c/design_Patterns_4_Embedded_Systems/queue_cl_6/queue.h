#ifndef QUEUE_H_

#define QUEUE_H_

#define QUEUE_SIZE 10
/* class Queue */
struct Queue {
  int buffer[QUEUE_SIZE];
  /* where the data things are */
  int head;
  int size;
  int tail;
  int (*isFull)(struct Queue* const me);
  int (*isEmpty)(struct Queue* const me);
  int (*getSize)(struct Queue* const me);
  void (*insert)(struct Queue* const me, int k);
  int (*remove)(struct Queue* const me);
};

/* Constructors and destructors:*/
void Queue_Init(struct Queue* const me,int (*isFullfunction)(struct Queue* const me),
		int (*isEmptyfunction)(struct Queue* const me),
		int (*getSizefunction)(struct Queue* const me),
		void (*insertfunction)(struct Queue* const me, int k),
		int (*removefunction)(struct Queue* const me) );
void Queue_Cleanup(struct Queue* const me);

/* Operations */
int Queue_isFull(struct Queue* const me);
int Queue_isEmpty(struct Queue* const me);
int Queue_getSize(struct Queue* const me);
void Queue_insert(struct Queue* const me, int k);
int Queue_remove(struct Queue* const me);
struct Queue * Queue_Create(void);
void Queue_Destroy(struct Queue* const me);

#endif /*QUEUE_H_*/
