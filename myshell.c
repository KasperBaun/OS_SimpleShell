#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h> // Used by waitpid()
#include <dirent.h>
#include <asm-generic/errno-base.h>
#include <errno.h>

#define MAXLENGTH 1024 /* Maximum length of input string */
#define MAXLIST 100 /* Maximum number or arguments */


/* Displays an instructional welcome message to the user*/
void displayWelcome(){
    printf("*\tHello %s and\n",getenv("USER"));
    printf("*\tWelcome to s172483's Simple Shell\n");
    printf("*\tFor a list of commands type: 'commands'\n");
    printf("*\tTo exit: Ctrl+Z or type exit/Exit/EXIT\n\n");
}
void printCurrentLoc(){
    char path[256];
    getcwd(path,256);
    printf("%s >> ",path);
}
void tokenizerLoop(char *input, char*delim, char* output[])
{
    /* Takes a pointer to a char array(string) as input
   and splits it up into tokens delimited by the
   defined delimiter.
   It requires a pointer to a string array to update
   values in that array */
    int i=0;
    char *token = strtok(input,delim);
    output[i] = token;

    while(output[i] != NULL)
    {
        output[++i] = strtok(NULL,delim);
    }
}
/* Splits the input into an array of strings where command and arguments are */
sortInput(char input[], char* destination[]){

    /* Search for chars matching '|' (pipe) first */
    if(strstr(input,"|"))
    {   /* Divide the commands separated by pipe by calling tokenizer with arguments: input, '|', output destination */
        tokenizerLoop(input,"|",destination);
    }
    else
    {
        /* This is only called if there is no '|' - so I can safely assume that only one command is entered by user
           therefore I use only destination[0] instead of creating a for-loop */
        tokenizerLoop(input," \n",destination);
    }
}

/* Changes the current directory to the specified directory if possible*/
int cd(char *pth){
    char path[1000];
    strcpy(path,pth);
    char cwd[256];
    getcwd(cwd,sizeof(cwd));

    if(pth==NULL){
        printf("Path is: %s\n",pth);
        chdir(cwd);
        return 0;
    }
    /* concatenate current working directory and user-specified path and check if it exists */
    strcat(cwd,"/");
    strcat(cwd,path);
    DIR* dir = opendir(cwd);
    if(dir)
    {   chdir(cwd);
        printf("%s%s\n","Current directory changed to: ", getcwd(cwd,sizeof (cwd)));
    }   else if(ENOENT == errno)
        {
        printf("Directory: %s does not exist!\n",cwd);
        }   else
            {
            printf("opendir() failed for some reason");
            }
    return 0;
}
void pipeMachine(char *command[], int i, int *pipefd_outer)
{
    printf("%i",i);
    int pipefd[2];
    pipe(pipefd);
    int pid = fork();
    if (pid > 0)
    {
        wait(0);
        if (pipefd_outer != NULL)
        {
            close(pipefd_outer[0]);
            dup2(pipefd_outer[1], 1);
        }
        close(pipefd[1]);
        dup2(pipefd[0], 0);
        execvp(command[0], &command[i]);
        puts("Command not found!");
        exit(127);
    }
    else if (pid == 0)
    {
        if (i > 1)
        {
            pipeMachine(command, --i, pipefd);
            exit(0);
        }
        else
        {
            close(pipefd[0]);
            dup2(pipefd[1], 1);
            execvp(command[i-1], &command[i-1]);
            puts("Command not found!");
            exit(127);
        }
    }
    else
    {
        exit(1);
    }
}
void execute_command(char* command[]){
    /* Closes all current running processes and terminates the Shell */
    if(strcmp(command[0],"exit")==0 | strcmp(command[0], "Exit")==0 | strcmp(command[0], "EXIT")==0)
    {
        printf("%s\n","Goodbye!" );
        exit(0);
    }
    /* Shows instructional commands */
    if(!strcmp(command[0],"commands") | !strcmp(command[0],"Commands")){
        printf("%s\n","1. Type 'cd <path>' or 'CD <path>' to change current directory");
        printf("%s\n","2. Type 'pwd' for current working directory");
        printf("%s\n","3. Type 'ls' for listing files in current working directory");
        printf("%s\n","4. Type 'pipe <program>' for nothing - not implemented yet");
        printf("%s\n","5. Type 'dup2 <filename.txt>' or 'DUP2 <filename.txt>' to redirect stdOut to filename.txt");
        printf("%s\n","6. Type 'exit/Exit' to exit the shell");
    }
        // Change path to the specified path
    else if(strcmp(command[0],"cd")==0 | strcmp(command[0], "CD")==0){
        if(command[1]!=NULL){
            char* path = command[1];
            cd(path);
        }
        return;
    }

    /* Forking a child process to run the command in */
    pid_t pid = fork();

    if (pid == -1) {
        printf("\nFailed forking child..");
        return;
    } else if (pid == 0) {
        if (command[1] != NULL)
        {
            int i = 0;
            while(command[i] != NULL) i++;
            pipeMachine(command, --i, NULL);
        }
        /* If no commands match then the shell uses exec to search for files (programs) to run that match the userinput.
            e.g. "ls" or "cd" */
        if (execvp(command[0], command) < 0) {
            printf("\nCould not execute command..");
        }
        exit(0);
    } else {
        /* wait for child to terminate */
        wait(NULL);
        return;
    }
}
/* Just used for understanding chars in C */
void * print_chars(char *process_string) {
    int i;
    int string_len;
    string_len = strlen(process_string);
    int newline = 10;

    printf("String is %s and its length is %d\n", process_string, string_len);

    for(i = 0; i < string_len+1; i++) {
        putchar(process_string[i]);
        putchar(newline);
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
    char userInput[MAXLENGTH], *parsedArguments[MAXLIST];
    printCurrentLoc();
    fgets(userInput,MAXLENGTH,stdin);
    //printf("User input before calling sortInput(): %s",userInput);
    sortInput(userInput, parsedArguments);
    execute_command(parsedArguments);
  }
}
