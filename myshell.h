#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "string.h"



// TODO: Make prompt take more than a string input (parameters)


// show_prompt() - Shows the prompt with blinking cursor ready to take input
char* show_prompt() {
  char *command = malloc(sizeof(char)*1024);
  printf("%s", ">>> ");
  scanf("%s", command);
  return command;
}

void clearScreen() {
  system("clear");
}
void read_command(char* command, char*const* parameters) {

  if(strcmp(command,"exit")==0 | strcmp(command, "Exit")==0){
    // Closes all current running processes. Child processes are sent SIGCHLD signal to terminate.
    printf("%s\n","Goodbye!" );
    exit(0);
  }

  if(strcmp(command,"commands")==0 | strcmp(command,"Commands")==0){
    printf("%s\n","1. Type 'pipe' for blablabla");
    printf("%s\n","1. Type 'pipe' for blablabla");
    printf("%s\n","1. Type 'pipe' for blablabla");
    printf("%s\n","1. Type 'pipe' for blablabla");
    printf("%s\n","1. Type 'pipe' for blablabla");
    printf("%s\n","1. Type 'pipe' for blablabla");
    printf("%s\n","1. Type 'pipe' for blablabla");
    printf("%s\n","1. Type 'pipe' for blablabla");
    printf("%s\n","1. Type 'exit/Exit' to exit the shell");
  }

}
void displayWelcome(){
  printf("%s\n","##########################################################");
  printf("%s\n","##         Welcome to s172483's Simple Shell            ##");
  printf("%s\n","##         For a list of commands type: 'commands'      ##");
  printf("%s\n","##         To exit: Ctrl+Z or type exit/Exit            ##");
  printf("%s\n","##########################################################");
}
