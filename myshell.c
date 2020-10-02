#include "myshell.h"
#include "stdio.h"
#include "string.h"

int main(int argc, char const *argv[]) {

int shellLoaded = 1;
int status=1;
char* promptInput;



// Clears the console if the program has just started and displays an instructional welcome message
  if(shellLoaded){
    clearScreen();
    shellLoaded=0;
    displayWelcome();
  }


  while(1){
    // Shows the prompt and takes input from user
    promptInput = show_prompt("$ ");
    // Reads input from user then decides where to go from there.
    read_command(promptInput);
  }
return 0;
}



































/* Create new childproce
   If succesful, execute command with parameters  in the child.
   If unsuccesfull - wait for child to terminate.
if (fork() !=0){
    waitpid(-1, &status, 0);
    } else {
          execve(command, parameters, 0);
          show_prompt();
    }
}
*/

/*
while(TRUE){

    if (fork() !=0){                    // fork off child process

      // Parent code
      waitpid(-1, &status, 0);          // Wait for child to exit
      } else {
              // Child code
              execve(command, parameters, 0); // Child executes the user input command
        }
 }
 */
