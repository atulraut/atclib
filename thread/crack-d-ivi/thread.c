#include <stdio.h>
#include<pthread.h>
/* g++ thread.c  -o main.out -pthread -std=c++11
*/
pthread_t tid[2];
unsigned int shared_data = 0;
pthread_mutex_t mutex;
unsigned int rc;

void* PrintEvenNos(void *ptr) {
  rc = pthread_mutex_lock(&mutex);
       do {
	   if(shared_data%2 == 0) {
	       printf("Even : %d\n",shared_data);
	       shared_data++;
	     } else {
	       rc=pthread_mutex_unlock(&mutex);//if number is odd, do not print, release mutex
	     }
	 } while (shared_data <= 5);
}

void* PrintOddNos(void* ptr1) {
  rc = pthread_mutex_lock(&mutex);
      do {
	  if(shared_data%2 != 0) {
	      printf("Odd  : %d\n",shared_data);
	      shared_data++;
	    } else {
	       rc = pthread_mutex_unlock(&mutex);//if number is even, do not print, release mutex
	    }
	} while (shared_data <= 5);
}

int main(void) {
  pthread_create(&tid[0],0,&PrintEvenNos,0);
  pthread_create(&tid[1],0,&PrintOddNos,0);
  //  sleep(3);
  pthread_join(tid[0],NULL);
  pthread_join(tid[1],NULL);
}

/**
   => ./main.out
   Even : 0
   Odd  : 1
   Even : 2
   Odd  : 3
   Even : 4
   Odd  : 5
**/
