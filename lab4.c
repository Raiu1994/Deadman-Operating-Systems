//lab4.c
//Griffin Scott

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#define CHILD 0
#define DEBUG 1
#define LIMIT 256 //This is the limit for each input.

int main(void){
	int pid = 0; //Process id for Child 1
  char inputCommand;


    printf("Please type in a command, as well as any arguements that you want to use.\n");
    inputCommand = getc(stdin);
    if (inputCommand < LIMIT){
      printf("Error. The maximum number of characters is 256. Please reduce the number of characters in your command.\n");
      exit();
    }
  //Let's make a Child
	pid = fork();
	printf ("Parent has created the First Child.\n");


}
