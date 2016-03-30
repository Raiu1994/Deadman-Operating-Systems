//Griffin Scott
//Project 1

#include <stdio.h>
#include <sdtlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

#define TRUE 1
#define FALSE 0

#define Max_Num_Args 256 //setting max
#define Max_Char 256 //Max amount of characters
#define Buffer_L 256 //Limit of buffer

int main(void)
{ char input_args = NULL;
   int pid = 0; // process id for fork
   int returnval = 0; //exec vp useage
   int errorval = 0; // inside wait pid
   int childstatus = 0;
   int input_args =0;
   int i =0;

      while(1) //loop with prompt until "exit"
   { //display prompt
      printf("Griffin Shell v 1.0.0\n");
if(Num_Arg == 0);
//check for user enter "exit" to quit shell
if (strcmp(input_args[0]exit)==0);
exit(0);

//space for space reasons

}

//execute the command using fork and execvp
//create child process

if(debug_fork) printf("Fork off!");
pid = fork ();

// error checking
if(pid<0)
{printf("Griffin says unable to fork, so new process!! Terminating.....\n");
  continue; //get new prompt, not exit

}
else if (pid ! = 0)
{//this is the parent
  if (debug_fork) printf("Parent waiting on child.\n");
  errorval = waitpid(-1, &childstatus, 0 );
  //check for errors
  if (errorval ==-1)
  {printf("Griffin Shell: error waiting on child exit.\n");


}

  if (debug_fork)printf("Child process exiting")
}
else
{ //this is the child
  if(debug_fork) printf("Child calling execvp.\n");
  returnval = execvp(input_args[0], input_args);
  //check errors
  if (returnval ==-1)
  {printf("Griffin Shell: command %s not found.\n, input_args[0]");
  continue;
}
exit(0);
}

     //if blank line,just continue



   }


}
