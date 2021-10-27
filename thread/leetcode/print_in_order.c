/***
    https://leetcode.com/problems/print-in-order/
    Print in Order
    Suppose we have a class:

    public class Foo {
    public void first() { print("first"); }
    public void second() { print("second"); }
    public void third() { print("third"); }
    }
    The same instance of Foo will be passed to three different
    threads. Thread A will call first(), thread B will call
    second(), and thread C will call third(). Design a mechanism
    and modify the program to ensure that second() is executed
    after first(), and third() is executed after second().

    Note:
    We do not know how the threads will be scheduled in the
    operating system, even though the numbers in the input
    seem to imply the ordering. The input format you see is
    mainly to ensure our tests' comprehensiveness.

    Input: nums = [1,2,3]
    Output: "firstsecondthird"
    Explanation: There are three threads being fired asynchronously.
    The input [1,2,3] means thread A calls first(), thread B
    calls second(), and thread C calls third(). "firstsecondthird"
    is the correct output.

    Input: nums = [1,3,2]
    Output: "firstsecondthird"
    Explanation: The input [1,3,2] means thread A calls first(),
    thread B calls third(), and thread C calls second().
    "firstsecondthird" is the correct output.

    Constraints:
    nums is a permutation of [1, 2, 3].

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: 27 Oct 2021
    Fair Oaks, CA.
*/

/*----------------------------------- Header --------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>
#include <string.h>  /* malloc */
#include <stdbool.h>
#include <math.h>
#include <assert.h>
#include <stdint.h> /* uint32_t */
#include <unistd.h> /* sleep */
#include<pthread.h>
/*----------------------------------- Micro --------------------------------------*/
#define debug(str,args...) printf("[%s] L=%d :"str"\n", __func__, __LINE__, ##args)
#define atsizeof(object) (char *)(&object+1) - (char*)(&object)
#define arrsz(x)  (sizeof(x) / sizeof((x)[0]))
#define max(a,b)		\
  ({ typeof (a) _a = (a);	\
    typeof (b) _b = (b);	\
    _a > _b ? _a : _b; })
#define min(a,b)		\
  ({ typeof (a) _a = (a);	\
    typeof (b) _b = (b);	\
    _a < _b ? _a : _b; })
/*----------------------------------- Micro --------------------------------------*/

struct user {
  // User defined data may be declared here.
  pthread_cond_t cond_t1;
  pthread_cond_t cond_t2;
  pthread_cond_t cond_t3;
  pthread_mutex_t mtx;
  int i;

} user;

void first(struct user* obj);
void second(struct user* obj);
void third(struct user* obj);

struct user* fooCreate() {
  struct user* obj = (struct user*) malloc(sizeof(struct user));

  if(obj != NULL)
    {
      pthread_mutex_init(&obj->mtx, NULL);
      pthread_cond_init(&obj->cond_t1, NULL);
      pthread_cond_init(&obj->cond_t2, NULL);
      pthread_cond_init(&obj->cond_t3, NULL);
      obj->i =1;
    }

  return obj;
}

void first(struct user* obj) {
  pthread_mutex_lock(&obj->mtx);
  // printFirst() outputs "first". Do not change or remove this line.
  debug("printFirst()");
  obj->i = 2;
  pthread_cond_signal(&obj->cond_t2);
  pthread_mutex_unlock(&obj->mtx);
}

void second(struct user* obj) {
  pthread_mutex_lock(&obj->mtx);
  while(obj->i < 2)
    pthread_cond_wait(&obj->cond_t2,&obj->mtx);
  // printFirst() outputs "first". Do not change or remove this line.
  // printSecond() outputs "second". Do not change or remove this line.
  debug ("printSecond()");
  obj->i = 3;
  pthread_cond_signal(&obj->cond_t3);
  pthread_mutex_unlock(&obj->mtx);
}


void third(struct user* obj) {
  pthread_mutex_lock(&obj->mtx);
  while(obj->i < 3)
    pthread_cond_wait(&obj->cond_t3,&obj->mtx);

  // printThird() outputs "third". Do not change or remove this line.
  debug("printThird()");
  pthread_mutex_unlock(&obj->mtx);
}

void fooFree(struct user* obj) {
  // User defined data may be cleaned up here.
  pthread_mutex_destroy(&obj->mtx);
  pthread_cond_destroy(&obj->cond_t1);
  pthread_cond_destroy(&obj->cond_t2);
  pthread_cond_destroy(&obj->cond_t3);
  free(obj);

}
/*
  typedef struct
  {
  sem_t first_;
  sem_t second_;
  sem_t third_

  } struct user;

  struct user* fooCreate()
  {
  struct user* obj = (struct user*) malloc(sizeof(struct user));

  //initialize semaphores
  sem_init(&obj->first_, 0, 1);
  sem_init(&obj->second_, 0, 0);
  sem_init(&obj->third_, 0, 0);

  return obj;
  }

  void first(struct user* obj)
  {
  //lock
  sem_wait(&obj->first_);

  // printFirst() outputs "first". Do not change or remove this line.
  printFirst();

  //unlock
  sem_post(&obj->second_);
  }

  void second(struct user* obj) {

  //lock
  sem_wait(&obj->second_);

  // printSecond() outputs "second". Do not change or remove this line.
  printSecond();

  //unlock
  sem_post(&obj->third_);
  }

  void third(struct user* obj)
  {

  //lock
  sem_wait(&obj->third_);

  // printThird() outputs "third". Do not change or remove this line.
  printThird();

  //unlock
  sem_post(&obj->first_);
  }

  void fooFree(struct user* obj)
  {
  //destroy semaphores
  sem_destroy(&obj->first_);
  sem_destroy(&obj->second_);
  sem_destroy(&obj->third_);

  //free allocated memory
  free(obj);
  obj = NULL;

  }
*/

int main (int argc, char **argv) {
  int ret = 0;
  struct user* this_obj = fooCreate();

  second(this_obj);
  first(this_obj);
  third(this_obj);
  fooFree(this_obj);

  debug("Output = %d", ret);
  return 0;
}

/**

 **/
