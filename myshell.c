#include "stdio.h"
#include "myshell.h"


int int main(int argc, char const *argv[]) {
  #define TRUE1

  while(TRUE){
      type_prompt(); /* This displays the prompt */
      read_command(command, parameters); /* Reads the user input from terminal */

      if (fork() !=0){ /* fork off child process */

        /* Parent code */
        waitpid(-1, &status, 0); /* Wait for child to exit*/
        } else {
          /* Child code */
          execve(command, parameters, 0); /* Child executes the user input command */
          }
   }
  return 0;
}
