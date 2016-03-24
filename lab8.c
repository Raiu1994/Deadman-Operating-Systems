//Lab8

#include <stdio.h>
#include <pthread.h>

#define LOOP_LIMIT 1000
#define MAXIMUM 5

//Global variables
pthread_mutex_t mutex; //Mutex to protect condition variables
pthread_cond_t condvar; //Whose turn is it?
int shared = 0; //The object being produced to and consumed from

//Function prototypes
void *consumer_fun(void *);
void *producer_fun(void *);

int main(void){
  pthread_t consumer; //Read from the shared variable
  pthread_t producer; //Writes to the shared variable

  //init mutex and condition variable
  pthread_mutex_init(&mutex, 0);
  pthread_cond_init(&condvar, 0);

  //Makes two threads
  pthread_create(&consumer, 0, consumer_fun, 0);
  pthread_create(&producer, 0, producer_fun, 0);

  //Join with threads when they finish
  pthread_join(consumer, 0);
  pthread_join(producer, 0);

  //destroy mutex and condition variable
  pthread_cond_destroy(&condvar);
  pthread_mutex_destroy(&mutex);

  //exit
  return 0;
}

//producer_fun
//Gens a random number, write it to the shared variable
void *producer_fun(void *ptr){
  int number = 0; //RANDOM NUMBER
  int i = 0; //Do this a few times

  //Start thread
  printf("Producer thread starting.\n");

  //init the PRNG
  srandom((unsigned int)time(NULL));

  for (i=0; i<LOOP_LIMIT; i++){
    /*Picks a random number that is less than MAXIMUM.
    If you do not get +1, we can get 0, and will get out of sync on the loop.
    This causes a deadlock condition.
    */
    number = random() % MAXIMUM + 1;

    //CRITICAL REGION
    pthread_mutex_lock(&mutex); //Don't try to open the consumer action at the same time.

    //Is buffer empty? If no, wait for an empty buffer
    while(shared != 0){
      pthread_cond_wait(&condvar, &mutex); //It is not time to produce.
    }//End while

    //This thread's turn.
    shared = number; //Set shared to the number generated.
    printf("Producer storing the number %d, on loop %d. \n", shared, i);

    pthread_cond_signal(&condvar); //Is condvar awake?
    pthread_mutex_unlock(&mutex);//Now we can continue.
  }//End for and CRITICAL REGION

  pthread_exit(0);
} //End producer_fun

//consumer_fun
//Takes the number from shared and sets it to zero.
void *consumer_fun(void *ptr){
   int i = 0; //The increment variable

  printf("Consumer thread starting.\n");

  for (i=0; i<LOOP_LIMIT; i++){ //Loops the consumer action.
    //CRITICAL REGION
    pthread_mutex_lock(&mutex);

    //Is buffer nonempty. If not, wait.
    while (shared == 0){
      pthread_cond_wait(&condvar, &mutex); //It is not time to consume.
    }//end while

    printf("Consumer retrieving the number %d, on loop %d.\n", shared, i);
    shared = 0; //Clear out shared.
    //signal the other thread in case it is asleep
    pthread_cond_signal(&condvar);
    //aond now unlock the mutex.
    pthread_mutex_unlock(&mutex);
  }//End For

  pthread_exit(0); //exit
}//End consumer_fun
