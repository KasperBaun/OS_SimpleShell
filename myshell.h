#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "string.h"
#include "sys/wait.h" // Used by waitpid()



// show_prompt() - Shows the prompt with blinking cursor ready to take input will max support a size of 1024 chars
char* show_prompt(char *promptmsg){
  char *promptInput = malloc(sizeof(char)*1024);
  printf("%s", promptmsg);
  scanf("%s", promptInput);
  return promptInput;
}

// Removes all code from the console screen
void clearScreen() {
  system("clear");
}

// Displays an instructional welcome message to the user
void displayWelcome(){
  printf("%s\n","##########################################################");
  printf("%s\n","##         Welcome to s172483's Simple Shell            ##");
  printf("%s\n","##         For a list of commands type: 'commands'      ##");
  printf("%s\n","##         To exit: Ctrl+Z or type exit/Exit            ##");
  printf("%s\n","##         Maximum input is command + 29 arguments      ##");
  printf("%s\n","##########################################################");
}


//Reads command from userInput in prompt and takes action based on command and parameters
void read_command(char *promptInput) {

    // First part of read_command splits the string promptInput into command and arguments.
    char *commandArgs[30];
    int i = 0;
    int sizeOfCommandArgs=1;
    char *delim = " ";
    char *ptr = strtok(promptInput, delim);
    
    while (ptr!=NULL)
    {   
        commandArgs[i] = ptr;
        sizeOfCommandArgs++;
        ptr = strtok(NULL, delim);
        printf("%s", commandArgs[i]);
    }
    char* command = commandArgs[0];
    
  
  

  // pipe
  if(strcmp(command,"pipe")==0 | strcmp(command, "Pipe")==0){
    // Create a child process
    printf("%s\n","Drilling the hole and preparing the pipe!" ); 
    int pid=fork();
    int status;
    if (pid !=0){
        waitpid(-1, &status, 0);
        } else {
              // Ask for input to send through Pipe
              //char* input = show_prompt("What input would you like to be sent through pipe? (Type a command or some manual data input)\n");
              //execve(input, parameters, 0);
              //show_prompt();
              printf("%s", "Hello from child\n");
              exit(0);
        }
        // What command should the receiving process perform on the datainput received through the pipe? */
    }

  if(strcmp(command,"echopipe")==0 | strcmp(command, "Echopipe")==0){
   
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


