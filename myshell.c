#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h> // Used by waitpid()


// Displays an instructional welcome message to the user
void displayWelcome(){
    printf("*\tHello %s and\n",getenv("USER"));
    printf("*\tWelcome to s172483's Simple Shell\n");
    printf("*\tFor a list of commands type: 'commands'\n");
    printf("*\tTo exit: Ctrl+Z or type exit/Exit\n\n");
}
void printCurrentLoc(){
    char path[256];
    getcwd(path,256);
    printf("%s >> ",path);
}
/* Takes a pointer to a char array(string) as input
   and splits it up into tokens delimited by the
   defined delimiter.
   It requires a pointer to a string array to update
   values in that array */
void tokenizerLoop(char *input, char*delim, char* output[])
{
    int i=0;
    char *token = strtok(input,delim);
    output[i] = token;

    while(output[i] != NULL)
    {
        output[++i] = strtok(NULL,delim);
    }
}
/* Removes whitespace and \n from an array of strings */
char** arrayTokenizerLoop(char* command)
{
    char** result = malloc(sizeof(char)*1024);
    for (int i=0; i<1024; ++i)
    {
        result[i] = malloc(sizeof(char)*1024);
        tokenizerLoop(command," \n",result);
    }
    return result;
}
/* Splits the input into an array of strings where command and arguments are */
void sortInput(char* input, char*** destination){

    /* Search for chars matching '|' (pipe) first */
    if(strstr(input,"|"))
    {
        /* First, we divide the commands separated by pipe by calling tokenizer with arguments: input, '|', output destination */
        char *commands[1024];
        tokenizerLoop(input,"|",commands);
        /* Now, we have to rinse for whitespace and \n - do this by calling a tokenizer function that supports array's  */
        for(int i=0; commands[i]!=NULL; i++)
        {
            destination[i] = arrayTokenizerLoop(commands[i]);
        }
    }
    else
    {
        /* This is only called if there is no '|' - so I can safely assume that only one command is entered by user
           therefore I only use destination[0] instead of creating a for loop */
        destination[0] = arrayTokenizerLoop(input);
    }
}
void execute_single_command(char* commandsAndArgs[])
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
            //pipeFunc(commandsAndArgs, --i, NULL);
        } else {
            char* firstCmd = &commandsAndArgs[0][0];
            /* Closes all current running processes and terminates the Shell */
            if(strcmp(firstCmd,"exit")==0 | strcmp(firstCmd, "Exit")==0)
            {
                printf("%s\n","Goodbye!" );
                exit(0);
            }
            /* Shows instructional commands */
            if(!strcmp(firstCmd,"commands") | !strcmp(firstCmd,"Commands")){
                printf("%s\n","1. Type 'cd <path>' or 'CD <path>' to change current directory");
                printf("%s\n","2. Type 'pwd' for current working directory");
                printf("%s\n","3. Type 'ls' for listing files in current working directory");
                printf("%s\n","4. Type 'pipe <program>' for nothing - not implemented yet");
                printf("%s\n","5. Type 'dup2 <filename.txt>' or 'DUP2 <filename.txt>' to redirect stdOut to filename.txt");
                printf("%s\n","6. Type 'exit/Exit' to exit the shell");
            }
            /* If no commands match then the shell uses exec to search for files (programs) to run that match the userinput.
            e.g. "ls" or "cd" */

            execvp(&commandsAndArgs[0][0], &commandsAndArgs[0]);
            printf("ExecVP failed @ single command launch");

            {

            }

        }
    }
    else
    {
        exit(1);
    }
}
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
        for(int j=0; commandsAndArgs[i][j] != NULL; j++)
        {
            printf("%s\n",commandsAndArgs[i][j]);
        }
    }
    //execute_command(commandsAndArgs);
  }
}
