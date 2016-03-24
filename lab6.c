/* lab6.c
Griffin Scott
2016
Purpose: To demonstrate how to create a new thread using phthreads
*/

#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

#define DEBUG 1

// Function prototypes
void *div_by_number(void*);

int main(void){
  pthread_t thread_one;
  pthread_t thread_two;
  int status = 0; //This is the return value from the pthread functions.

  //Creating a child
  printf("Parent is creating first child.\n");
  status = pthread_create(&thread_one, NULL, *div_by_number, (void *)1);
  //Error checking
  if (status != 0){
    printf("Ooops, pthread create has returned error code %d\n", status);
    exit(-1);
  }//end if

  //Second child
  printf("Parent is creating second child.\n");
  status = pthread_create(&thread_two, NULL, *div_by_number, (void *)2);
  //Error checking
  if (status != 0){
    printf("Ooops, pthread create has returned error code %d\n", status);
    exit(-1);
  }//end if

  //Waiting for child to exit
  printf("Parent is waiting on the first child to exit. \n");
  printf("Test\n");
  status = pthread_join(thread_one, NULL);
  printf("Test2\n");
  printf("First child has exited, and has been joined.\n");
  printf("Parent is waiting on the second child to exit.\n");
  status = pthread_join(thread_two, NULL);
  printf("Second Child has exited, and has been joined.\n");

  exit(0);
}//End main

void *div_by_number(void *thread_num) {
  int dividend = 84; //This is divided
  int result = 0; //This is the result of the division
  int maximum_time = 0; //This is the max time to waiting
  int number = 0; //And a "random" number.

  //And initialize the random number generator, aka putting the SEED to the sod.
  srandom((unsigned int)time(NULL)+ *(int *)thread_num);
  //Pick a random number that is less than the maximum_time
  maximum_time = 4; //4 seconds max waiting
  number = random() % maximum_time;
  //Wait maximum_time amount of time
  printf("Thread %d sleeping %d seconds.\n", *(int *) thread_num, number);
  sleep(number);

  if (*(int *) thread_num == 1){
      result = dividend/2;
  } else {
    result = dividend/0;
  }//End else

  if (*(int *) thread_num == 2){
    printf("Problem! Second child should not be here. \n");
    printf("Second child exiting... \n");
  } else {
      printf("The first child gets a result of %d.\n", result);
      printf("First child exiting...\n");
  } //End else

  pthread_exit(NULL);
} //End div_by_number
