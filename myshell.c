#include "systemcalls.c"
#include "rinseInput.c"


void displayWelcome();
void printCurrentLoc();


int main(int argc, char const *argv[]) {  
  /* Clears the console on load
   * and displays an instructional welcome message.
   */
  system("clear");
  displayWelcome();
    
  while(1){
    /* Shows prompt, takes input, 
       splits input into cmd and arg and reads commands
    */
    char* userInput = malloc(sizeof(char)*1024);
    char*** commandsAndArgs = malloc(sizeof(char)*1024*30);
    printCurrentLoc();
    fgets(userInput,1024,stdin);
    sortInput(userInput, commandsAndArgs);
    for(int i=0; commandsAndArgs[i]!=NULL;i++){
    printf("%s\n",commandsAndArgs[i]);
    }
    //execute_command(commandsAndArgs);
  }
return 0;
}


// Displays an instructional welcome message to the user
void displayWelcome(){
  printf("%s\n","##########################################################");
  printf("%s\n","##         Welcome to s172483's Simple Shell            ##");
  printf("%s\n","##         For a list of commands type: 'commands'      ##");
  printf("%s\n","##         To exit: Ctrl+Z or type exit/Exit            ##");
  printf("%s\n","##########################################################");
}
void printCurrentLoc(){
  char path[256];
  getcwd(path,256);
  printf("%s >> ",path);
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
