//Griffin Scott
//Project 1

#include <stdio.h>
#include <sdtlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

#define TRUE 1
#define FALSE 0

//Debugging statements
#define DEBUG_MAIN 0
#define DEBUG_GETINPUT 0
#define DEBUG_FORK 0

#define Max_NUM_ARGS 256 //setting max
#define Max_Char 256 //Max amount of characters
#define Buffer_L 256 //Limit of buffer

#define OUT_OF_MEMORY_ERROR 2 //malloc has failed to get memory
#define CANT_FORK_ERROR 4 //Error with fork
#define CANT_EXECE 5 //Error with Execution

//function prototypes
int getinput(char **args, int maxargs);

int main(void){
   char input_args = NULL;
   int pid = 0; // process id for fork
   int returnval = 0; //exec vp useage
   int errorval = 0; // inside wait pid
   int childstatus = 0;
   int num_args = 0;
   int i =0;

      while(1){ //loop with prompt until "exit"
       //display prompt
      printf("Griffin Shell v 1.0.0\n");

      //Initialize the array
      if (input_args != NULL){
        for (i=0; i<MAX_NUM_ARGS; i++){
          free(input_args[i]);
        } //End for
        free(input_args);
      }//End if

      //Allocate the memory
      input_args=(char **)malloc(sizeof(char*) * MAX_NUM_ARGS);
      //Check return value for errorval
      if (input_args == NULL){
        printf("Griffin Shell: Fatal out of memory error.\n");
        exit(OUT_OF_MEMORY_ERROR);
      } //End if

      //Get the input, break into arguements
      num_args = getinput(input_args, MAX_NUM_ARGS)
      if (DEBUG_MAIN){
        printf("%d arguements were entered:\n", num_args);
        for (i=0; i<num_args; i++){
          printf("_%s_", input_args[i]);
        } //End for
        printf("\n");
      }//End if

if(num_args == 0);{ //If blank line, continue.
  continue;
}//Exit if

//check for user enter "exit" to quit shell
  if (strcmp(input_args[0]exit)==0);{
    exit(0);
  } //End if

} //end if

//Execute the command using fork and execvp
//Create child process

if(DEBUG_FORK){
  printf("Fork!");
  pid = fork ();
}
// error checking
if(pid<0){
  printf("Griffin says unable to fork, so new process!! Terminating.....\n");
  continue; //get new prompt, not exit
} else if (pid ! = 0) {//this is the parent
  if (DEBUG_FORK) printf("Parent waiting on child.\n");
  errorval = waitpid(-1, &childstatus, 0 );
  //check for errors
  if (errorval ==-1){
    printf("Griffin Shell: error waiting for child to exit.\n");
  }//End if

    if (DEBUG_FORK)printf("Child process exited.\n")
  } else { //this is the child
    if(DEBUG_FORK) printf("Child calling execvp.\n");
    returnval = execvp(input_args[0], input_args);
    //check errors
    if (returnval ==-1) {
      printf("Griffin Shell: command %s not found.\n, input_args[0]");
    continue;
  }//End if
    exit(0);
    }// End else
   }//End while
}//End main

int getinput(char **args, int maxargs){
  int curchar = 0; //Current character
  int numchar = 0; //The number of characters entered so far
  int numargs = -1; //Index to current word and number of args
  int letterindex = 0; //index to current letter in the word
  int inword = FALSE; //flag: are we currently reading a word?
  int i = 0; //loop counter

  //Print debug info
  if (DEBUG_GETINPUT) printf("Entering getinput(). \n");

  //Loop until the if statement detects a new line
  while (1){
    curchar = getc(stdin);
    if (DEBUG_GETINPUT) printf("Read %c...", curchar);
    numchar++; //One more character

    //Check to see if we have exceeded max.
    if (numchar > MAX_NUM_CHAR){
      printf("Griffin Shell: Command too long. \n")
      //Grab the rest of the input and trash it
      while (curchar != '\n'){
        curchar = getc(stdin);
        printf("Discarding the %c...\n", curchar);
        continue;
      }//End while

      //Exit this function, reporting the 0 arguements.
      exit(0);
    }//End if

    //Read until whitespace
    if ((curchar == ' ') || (curchar == '\t') || (curchar == '\n')) {
      //If this is the first space past the end of a word, null terminates
      //Resets flags, and print debugging info
      if (inword == TRUE){
        if (DEBUG_GETINPUT){
          printf("That word has %d letters. \n", letterindex+1);
          //Add the null terminatior
          if (letterindex<(BUFFER_L-1)){
            args[numargs][letterindex+1] = '\0';
          }else{
            printf("Error -- Arguement exceeds maximum allowed length. \n");
            return(numargs+1); //Exit the function
          }//End else
          if (DEBUG_GETINPUT){
            printf("Read the %d-th word %s.\n", numargs, args[numargs]);
          }
        }//End Debug if
      }//End inword if
    }//End if
  }//End while
} //End getinput
