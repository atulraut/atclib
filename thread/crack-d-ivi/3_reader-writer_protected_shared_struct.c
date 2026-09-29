/**
   Implement reader/writer protected shared structure

   gcc -Wall -Wextra -pthread rwlock.c -o rwlock
   ./rwlock

   Date: Mon Sep 28 20:34:07 PDT 2026
   Folsom, CA, USA
**/

#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

/**
                 Shared Structure
              +--------------------+
              | value              |
              | name               |
              +--------------------+
                       ^
                       |
                 pthread_rwlock
                       |
             +---------+---------+
             |                   |
          Readers              Writer
       R1  R2  R3 ...            W
             |                   |
             v                   v
        Can execute          Exclusive
        concurrently          access
**/

typedef struct {
  int value;
  char name[64];

  pthread_rwlock_t lock;
} shared_data_t;

shared_data_t shared;

/* Initialize shared structure */
int shared_init(shared_data_t *data) {
  if (data == NULL)
    return -1;

  data->value = 0;
  data->name[0] = '\0';

  if (pthread_rwlock_init(&data->lock, NULL) != 0)
    return -1;

  return 0;
}

/*
 * READER
 *
 * Multiple readers can execute this
 * function simultaneously.
 */
int shared_read(shared_data_t *data,
                int *value,
                char *name,
                size_t name_size)
{
  if (data == NULL || value == NULL ||
      name == NULL || name_size == 0)
    return -1;

  /*
   * Acquire READ lock.
   *
   * Other readers are allowed.
   * Writers are blocked.
   */
  pthread_rwlock_rdlock(&data->lock);

  *value = data->value;
  snprintf(name, name_size, "%s", data->name);

  pthread_rwlock_unlock(&data->lock);

  return 0;
}

/*
 * WRITER
 *
 * Writer gets exclusive access.
 */
int shared_write(shared_data_t *data,
                 int value,
                 const char *name)
{
  if (data == NULL || name == NULL)
    return -1;

  /*
   * Acquire WRITE lock.
   *
   * Blocks:
   *   - all readers
   *   - all other writers
   */
  pthread_rwlock_wrlock(&data->lock);

  data->value = value;
  snprintf(data->name,
	   sizeof(data->name),
	   "%s",
	   name);

  pthread_rwlock_unlock(&data->lock);
  return 0;
}

void shared_destroy(shared_data_t *data) {
  if (data == NULL)
    return;
  pthread_rwlock_destroy(&data->lock);
}

void *reader_thread(void *arg) {
  int id = *(int *)arg;

  for (int i = 0; i < 5; i++) {

    int value;
    char name[64];

    shared_read(&shared,
		&value,
		name,
		sizeof(name));
    printf("Reader %d: value=%d name=%s\n",
	   id, value, name);
    usleep(100000);
  }
  return NULL;
}

void *writer_thread(void *arg) {
  int id = *(int *)arg;

  for (int i = 0; i < 5; i++) {

    char name[64];

    snprintf(name,
	     sizeof(name),
	     "writer-%d",
	     id);

    shared_write(&shared,
		 i,
		 name);

    printf("Writer %d updated data\n", id);
    usleep(200000);
  }
  return NULL;
}

int main(void) {
  pthread_t r1, r2, r3;
  pthread_t w1;

  int id1 = 1;
  int id2 = 2;
  int id3 = 3;
  int wid = 1;

  shared_init(&shared);

  pthread_create(&r1, NULL, reader_thread, &id1);
  pthread_create(&r2, NULL, reader_thread, &id2);
  pthread_create(&r3, NULL, reader_thread, &id3);
  pthread_create(&w1, NULL, writer_thread, &wid);

  pthread_join(r1, NULL);
  pthread_join(r2, NULL);
  pthread_join(r3, NULL);
  pthread_join(w1, NULL);

  shared_destroy(&shared);

  return 0;
}

/**
   -> ./rwlock
   Reader 1: value=0 name=
   Reader 2: value=0 name=
   Reader 3: value=0 name=
   Writer 1 updated data
   Reader 1: value=0 name=writer-1
   Reader 3: value=0 name=writer-1
   Reader 2: value=0 name=writer-1
   Writer 1 updated data
   Reader 1: value=1 name=writer-1
   Reader 2: value=1 name=writer-1
   Reader 3: value=1 name=writer-1
   Reader 1: value=1 name=writer-1
   Reader 2: value=1 name=writer-1
   Reader 3: value=1 name=writer-1
   Writer 1 updated data
   Reader 1: value=2 name=writer-1
   Reader 2: value=2 name=writer-1
   Reader 3: value=2 name=writer-1
   Writer 1 updated data
   Writer 1 updated data
**/
