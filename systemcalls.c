#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h> // Used by waitpid()

char* getArguments(char** strings){
  int i = 1; /* Setting index to 1 to avoid getting the command in the mix */
  int count = 0;
  char* result = NULL;
  int totalLength = 0;

  // Close program if input is empty
  if (strings == NULL){
    printf("%s","Input strings are NULL");
    return NULL;
  }

  // Iterate through the array to find out the size
  while(strings[i]!=NULL){
    totalLength = strlen(strings[i]);
    i++;
  }
  count = i;
  totalLength++;

  // Allocate memory for the result string
  result = malloc(sizeof(char)*totalLength);
  if(result==NULL){
    printf("%s", "Memory allocation failed somehow\n");
    return NULL;
  }

  // Concatenate input strings into result
  for(i=1; i<count; i++){
    strcat(result,strings[i]);
  }
  return result;

}
void pipeFunc(char ***commandsAndArgs, int index, int *pipefd_outer){

}
//Reads command from userInput in prompt and takes action based on command and parameters
void execute_command(char* commandsAndArgs[])
{
    int pid = fork();
    if (pid>0)
    {
      wait(0);
    }
    else if (pid == 0) {
        /* Check if there are more than one command in the arrays (user input '|')*/
        if (commandsAndArgs[1] != NULL) {
            int i = 0;
            while (commandsAndArgs[i] != NULL) i++;
            pipeFunc(commandsAndArgs, --i, NULL);
        } else {
            /* If no commands match then the shell uses exec to search for files (programs) to run that match the userinput.
            e.g. "ls" or "cd" */
            char **arguments = getArguments(commandsAndArgs);
            execvp(commandsAndArgs[0], arguments);
            printf("ExecVP failed @ single command launch");

                {

                }

            }
        }
    }
    else if(!strcmp(commandsAndArgs[0],"commands") | !strcmp(commandsAndArgs[0],"Commands")){
        printf("%s\n","1. Type 'cd <path>' or 'CD <path>' to change current directory");
        printf("%s\n","2. Type 'pwd' for current working directory");
        printf("%s\n","3. Type 'ls' for listing files in current working directory");
        printf("%s\n","4. Type 'pipe <program>' for nothing - not implemented yet");
        printf("%s\n","5. Type 'dup2 <filename.txt>' or 'DUP2 <filename.txt>' to redirect stdOut to filename.txt");
        printf("%s\n","6. Type 'exit/Exit' to exit the shell");
    }

        /* Closes all current running processes and terminates the Shell */
    else if(strcmp(commandsAndArgs[0],"exit")==0 | strcmp(commandsAndArgs[0], "Exit")==0)
    {
        printf("%s\n","Goodbye!" );
        exit(0);
    }
    else
    {
        exit(1);
    }



  /*else if(strcmp(commandsAndArgs[0],"dup2")==0 | strcmp(commandsAndArgs[0], "DUP2")==0){
    // Creates a pointer to the filedescriptor of fileName.txt which is entered by the user.
    // This is found using concatenateString(arguments[])
    char* fdName = getArguments(commandsAndArgs);
    int fdPointer = open(fdName,O_CREAT| O_APPEND|O_RDWR|O_TRUNC,0644);
    int stdOut = 1;
    printf("%s%s\n", "Now redirecting standard output to :",fdName);
    dup2(fdPointer,stdOut);
    
  }
*/


  

  

}


