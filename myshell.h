#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "string.h"



// TODO: Make prompt take more than a string input (parameters)


// show_prompt() - Shows the prompt with blinking cursor ready to take input will max support a size of 1024 chars
char* show_prompt(char* promptmsg) {
  char *command = malloc(sizeof(char)*1024);
  printf("%s", promptmsg);
  scanf("%s", command);
  return command;
}

void clearScreen() {
  system("clear");
}
void read_command(char* command, char*const* parameters) {

  // pipe
  if(strcmp(command,"pipe")==0 | strcmp(command, "Pipe")==0){
    // Create a child process
    printf("%s\n","Drilling the hole and preparing the pipe!" );
    // Ask for input to send through Pipe
    char* input = show_prompt("What input would you like to be sent through pipe? (Type a command or some manual data input)\n");
    // What command should the receiving process perform on the datainput received through the pipe?

  }


  if(strcmp(command,"exit")==0 | strcmp(command, "Exit")==0){
    // Closes all current running processes. Child processes are sent SIGCHLD signal to terminate.
    printf("%s\n","Goodbye!" );
    exit(0);
  }

  if(strcmp(command,"commands")==0 | strcmp(command,"Commands")==0){
    printf("%s\n","1. Type 'pipe' or '|' for initializing a pipe between 2 processes");
    printf("%s\n","2. Type 'pipe' for blablabla");
    printf("%s\n","3. Type 'pipe' for blablabla");
    printf("%s\n","4. Type 'pipe' for blablabla");
    printf("%s\n","5. Type 'pipe' for blablabla");
    printf("%s\n","6. Type 'pipe' for blablabla");
    printf("%s\n","7. Type 'pipe' for blablabla");
    printf("%s\n","8. Type 'pipe' for blablabla");
    printf("%s\n","9. Type 'exit/Exit' to exit the shell");
  }

}
void displayWelcome(){
  printf("%s\n","##########################################################");
  printf("%s\n","##         Welcome to s172483's Simple Shell            ##");
  printf("%s\n","##         For a list of commands type: 'commands'      ##");
  printf("%s\n","##         To exit: Ctrl+Z or type exit/Exit            ##");
  printf("%s\n","##########################################################");
}
