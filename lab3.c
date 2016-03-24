/*lab3.c
 * Griffin Scott
 * 1/27/16
 * This program will create a new process using fork, waitpid, exit and will also catch a signal: SIGFPE.
 */

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

#define CHILD 0
#define DEBUG 1

int main(void){
	int pid = 0; //Process id for Child 1
	int pid2 = 0; //Process id for Child 2
	int retpid = 0; //Child that just exited
	int childValue = 0; //sets the child return value
	int dividend = 42; //The top half of the fraction
	int divisor = 0; //The bottom half of the fraction
	int result = 0; //Result of division

	//Let's make a Child
	pid = fork();
	printf ("Parent has created the First Child.\n");
	//No, the First Child isn't Shinji. He still hasn't gottn in the robot.
	
	//If I am the parent, create the Second Child.
	if (pid != CHILD){
		printf ("I am the parent. Ready to create the next child.\n");
		pid2 = fork();
	}//End Child Creation Process

	//If parent, I have 2 non-zero pids for the Children. Let's check to see if they are not zombies. To continue the joke, "Are they in the robot?"
	if((pid != CHILD) && (pid2 != CHILD)){
		printf("Parent is waiting on one of the children to exit.\n");
		retpid = waitpid(-1, &childValue, 0);
		printf("Child %d returned a value of %x in hex. \n", retpid, childValue);
		//And now we do it again, because we had multiple bottles on that night.
		printf("Parent is waiting on the other child to exit. \n");
		retpid = waitpid(-1, &childValue, 0);
		printf("Child %d returned a value of %x in hex. \n", retpid, childValue);
		//Edit this process
		exit(0);
	}

	//First child, that has a zero for the first pid
		else if (pid == CHILD){
			if (DEBUG){
				printf("I am the first child with pid %d and pid2 %d. \n", pid, pid2);
				//Preform the division... SIGFPE is not caught in the process.
				result = dividend/divisor;

				printf("The first child gets a result of %d.\n", result);
				//This part should never execute.
				printf("First child exiting...\n");
				exit(0);
			}
			else{ //Second Child has a non-zero first pid (The same as the parent)
			if (DEBUG){
			printf("I am the second child with a pid %d and a pid2 %d. \n", pid, pid2);
			//Preform validation
			result = dividend/(divisor+1);

			//Print results
			printf("The second child gets a result of %d. \n", result);
			exit (0);
			}
		}
	}
}
