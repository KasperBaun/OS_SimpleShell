#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "string.h"
#include "fcntl.h"
#include "sys/wait.h" // Used by waitpid()



// show_prompt() - Shows the prompt with blinking cursor ready to take input will max support a size of 1024 chars
char* show_prompt(char *promptmsg){
  char *promptInput = malloc(sizeof(char)*1024);
  printf("%s", promptmsg);
  fgets(promptInput,1024,stdin);
  return promptInput;
}

// Removes all code from the console screen
void clearScreen() {
  system("clear");
}

char* concatenateStrings(char** strings){
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

// Changes the current directory to the specified directory if possible
int cd(char *pth){
   char path[1000];
   strcpy(path,pth);
   char cwd[256]; 
   getcwd(cwd,sizeof(cwd));

  if(pth==NULL){
    printf("%s%s\n","Path is:",pth);
  }

   strcat(cwd,"/"); 
   strcat(cwd,path);
   chdir(cwd);    

   printf("%s%s\n","Current directory changed to: ",cwd);
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

//Reads command from userInput in prompt and takes action based on command and parameters
void read_command(char* arguments[]) {
  
  // pipe
  if(strcmp(arguments[0],"pipe")==0 | strcmp(arguments[0], "Pipe")==0){
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

  else if(strcmp(arguments[0],"dup2")==0 | strcmp(arguments[0], "DUP2")==0){
    // Creates a pointer to the filedescriptor of fileName.txt which is entered by the user.
    // This is found using concatenateString(arguments[])
    char* fdName = concatenateStrings(arguments);
    int fdPointer = open(fdName,O_CREAT| O_APPEND|O_RDWR|O_TRUNC,0644);
    int stdOut = 1;
    printf("%s%s\n", "Now redirecting standard output to :",fdName);
    dup2(fdPointer,stdOut);
    
  }



  // Change path to the specified path
  else if(strcmp(arguments[0],"cd")==0 | strcmp(arguments[0], "CD")==0){
    char* path = concatenateStrings(arguments);
    cd(path);
  }


	
  else if(!strcmp(arguments[0],"commands") | !strcmp(arguments[0],"Commands")){
    printf("%s\n","1. Type 'cd <path>' or 'CD <path>' to change current directory");
    printf("%s\n","2. Type 'pwd' for current working directory");
    printf("%s\n","3. Type 'ls' for listing files in current working directory");
    printf("%s\n","4. Type 'pipe <program>' for nothing - not implemented yet");
    printf("%s\n","5. Type 'dup2 <filename.txt>' or 'DUP2 <filename.txt>' to redirect stdOut to filename.txt");
    printf("%s\n","6. Type 'exit/Exit' to exit the shell");
  }
  
  
    // Closes all current running processes and terminates the Shell.d
  else if(strcmp(arguments[0],"exit")==0 | strcmp(arguments[0], "Exit")==0){
    printf("%s\n","Goodbye!" );
    exit(0);
  }
  
  // If no commands match then the shell uses exec to search for files (programs) to run that match the userinput.
  // e.g. "ls" or "cd"
  else {
    if (fork()!=0){
      wait(NULL);
    } else
    {
      execvp(arguments[0],arguments);
      exit(0);
    }
    
}
}


