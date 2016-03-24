/* lab7.c
 * January 2016
 * Griffin Scott
 * Purpose:  Provide an introduction to using mutexes.
 */
#include <stdio.h>
#include <stdlib.h>  /* to make ubuntu happy with exit() */
#include <pthread.h>
#include <time.h>
#include <sched.h> /* to allow the thread to yield the cpu with sched_yield */

#define DEBUG 0

/* function prototypes */
void *grab_stick(void*);

/* global variables */
pthread_mutex_t stick;

int main(void)
{  pthread_t player1;	/* the first player */
   pthread_t player2;	/* the second player */
   int status = 0;	/* status of thread creation */

   /* start each thread, checking for errors */
   if (DEBUG) printf("Parent is creating first player.\n");
   status = pthread_create(&player2, NULL, grab_stick, (void *)2);
   /* check for an error -- code from book */
   if (status != 0)
   {  printf("Oops. pthread create returned error code %d\n", status);
      exit(-1);
   }
   if (DEBUG) printf("Parent is creating second player.\n");
   status = pthread_create(&player1, NULL, grab_stick, (void *)1);
   /* check for an error -- code from book */
   if (status != 0)
   {  printf("Oops. pthread create returned error code %d\n", status);
      exit(-1);
   }

   /* wait for children to exit */
   if (DEBUG) printf("Parent is waiting on the first player to exit.\n");
   status = pthread_join(player1, NULL);
   if (DEBUG) printf("First player has exited, and been joined.\n");
   if (DEBUG) printf("Parent is waiting on the second player to exit.\n");
   status = pthread_join(player2, NULL);
   if (DEBUG) printf("Second player has exited, and been joined.\n");

   /* exit this process */
   exit(0);
}


/* GRAB_STICK
 * Purpose:	this is where each player thread will begin.  Each player
 *              immediately tries to grab the stick.
 * Arguments:   player_num = which player am I?
 * Returns:     nothing
 */
void *grab_stick(void *player_num)
{  int number1 = 0;		/* a random number 1 */
   int number2 = 0;    /* a random number 2 */
   printf("%d: Starting execution\n", player_num);

   /* see the seed */
   /*srandom(time(NULL)); */

   /* pick a random number, then determine if it is even or odd */
   number1 = random();
   number2 = random();
   printf("%d random number1 value", number1);
   printf("%d random number2 value", number2);
  /* Error Checking */
   if (number1 == number2) {
      printf("rerolling for political reasons"):
      number1 = random();
      number2 = random();
    }
   if (number1 > number2) { //Player2 gives us.

   }
   /* if I am player 0, sometimes give up the processor,
    * but only if I got an even number */
   /*if ( (player_num == 0 ) | (number % 2 == 0) )
   {
      printf("Test31\n");
      printf("Thread %d voluntarily yielding.\n", player_num);
      sched_yield();  // voluntarily yield the CPU
   //}
*/
   /* grab the stick! */
   pthread_mutex_lock(&stick);
   printf("Player %d got the stick!\n", player_num);

   /* exit this thread */
   pthread_exit(NULL);
}
