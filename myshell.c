#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h> // Used by waitpid()
#include <dirent.h>
#include <asm-generic/errno-base.h>
#include <errno.h>

#define MAXLENGTH 1024 /* Maximum length of input string */
#define MAXCMD 100 /* Maximum amount of args */

void pipeMachine();


/* Displays an instructional welcome message to the user*/
void displayWelcome(){
    printf("*\tHello %s and\n",getenv("USER"));
    printf("*\tWelcome to group 2's Simple Shell\n");
    printf("*\tFor a list of commands type: 'commands'\n");
    printf("*\tTo exit: Ctrl+Z or type exit/Exit/EXIT\n\n");
}


void printCurrentLoc(){
    char path[256];
    getcwd(path,256);
    printf("%s >> ",path);
}


void printCommands(){
        printf("%s\n","1. Type 'cd <path>' or 'CD <path>' to change current directory");
        printf("%s\n","2. Type 'pwd' for current working directory");
        printf("%s\n","3. Type 'ls' for listing files in current working directory");
        printf("%s\n","4. Type 'pipe <program>' for nothing - not implemented yet");
        printf("%s\n","5. Most linux commands works since the shell makes use of \nexecvp() system call and searchs the $PATH variable for binaries matching");
        printf("%s\n","6. Type 'exit/Exit' to exit the shell");
}


void tokenizerLoop(char *input, char*delim, char* output[])
{
    /* Takes a pointer to a char array(string) as input
   and splits it up into tokens delimited by the
   defined delimiter.
   It requires a pointer to a string array to update
   values in that array 
   returns int that counts how many elements is in the array*/
    int i=0;
    char *token = strtok(input,delim);

    while(token != NULL)
    {
        output[i++] = token;
        token = strtok(NULL,delim);
    }
}


void printArrayContent(char* array[]){
    if(array[0]!=NULL)
    {
    for(int i=0; array[i]!=NULL;i++){
        printf("Element[%d] is: %s \n",i,array[i]);
    }
    } else printf("printArrayContent() - Nothing to print im afraid");    
}


/* Allocates memory on the heap for the string (cmd+args) size and returns a pointer to the adress of the first element in the array */
char ** commandFactory(char* input){
    char **command = malloc(MAXCMD*sizeof(char*));
    tokenizerLoop(input," \n",command);
    return command;
}


/* Splits the input into an array of strings where command and arguments are */
int sortInput(char input[], char** commandArray[]){
    /* Clean string for \n */ 
    input[strcspn(input, "\n")] = 0;

    /* Search for chars matching '|' (pipe) first */
    if(strstr(input,"|"))
    {   /* Divide the commands separated by pipe by calling tokenizer with arguments: input, '|', output destination */
        char *temp[MAXLENGTH];
        tokenizerLoop(input,"|",temp);
        //printArrayContent(temp);
        for(int i=0; temp[i]!=NULL;i++){
            commandArray[i] = commandFactory(temp[i]);
            //printArrayContent(commandArray[i]);
        }
        return 1;
    }
    else
    {
        /* This is only called if there is no '|' - so I can safely assume that only one command is entered by user
           therefore I use only commandArray[0] instead of creating a for-loop */
        commandArray[0] = commandFactory(input);
        //printArrayContent(commandArray[0]); 
        return 0;       
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


void freeMemory(char ***commandArray){
    for(int i=0; i<MAXLENGTH; i++){
        int j = 0;
        while(commandArray[i][j]!=NULL){
            free(commandArray[i][j]);
            j++;
        }
        free(commandArray[i]);
    }
}


void execute_command(char** command[], int pipeStatus){

    for (int i = 0; i < 10; ++i) {
        printArrayContent(command[i]);
    }


    /* Closes all current running processes and terminates the Shell */
    if(strcmp(command[0][0],"exit")==0 | strcmp(command[0][0], "Exit")==0 | strcmp(command[0][0], "EXIT")==0)
    {
        printf("%s\n","Goodbye!" );
        exit(0);
    }
    /* Shows instructional commands */
    else if(!strcmp(command[0][0],"commands") | !strcmp(command[0][0],"Commands")){
        printCommands();
    }
        // Change path to the specified path
    else if(strcmp(command[0][0],"cd")==0 | strcmp(command[0][0], "CD")==0){
        if(command[0][1]!=NULL){
            char* path = command[0][1];
            cd(path);
        }
        return;
    }

    /* Check for pipe */  
    if (pipeStatus){ 
        /*todo Implement pipe functionality here */
    /* More than one command so we need to redirect some output to another process */
        int pipefd[2];
        int pid;
        char recv[MAXLENGTH];
        pipe(pipefd);

        switch (pid=fork())
        {
        case -1: perror("fork in execute_command pipe section");
            exit(1);
        case 0:
            /* We are in child process */
            close(pipefd[0]); /* Close read-end of pipe */
            FILE *out = fdopen(pipefd[1],"w"); /* Open pipe as stream for writing */
            dup2(pipefd[1], 1);  // send stdout to the pipe
            dup2(pipefd[1], 2);  // send stderr to the pipe
            close(pipefd[1]);    // this descriptor is no longer needed
            execvp(command[0][0],command[0]);
            break;
        default:
            /* We are in parent process */
            close(pipefd[1]); /* Close writing end of pipe */
            FILE *in = fdopen(pipefd[0],"r"); /* Open pipe as stream for reading */
            fread(recv, MAXLENGTH,1,in); /* Write to stream from pipe */
            printf("%s\n", recv);
            break;
        }

//    Tried to get pipe to work. Used sources:
//      https://www.youtube.com/watch?v=6xbLgZpOBi8
// and  https://stackoverflow.com/questions/2659590/pipe-implementation?noredirect=1&lq=1
//    doesn't work correctly
//        int pipe_fd[2]; //pipe_fd[1] is write end of pipe, and pipe_fd[0] is read end.
//
//        if(pipe(pipe_fd) == -1) {
//            printf("Error in pipe - ret 1");
//            exit(1);
//        }
//
//        int pid1 = fork();
//        if (pid1 < 0) {
//            printf("Error in fork - ret 2");
//            exit(1);
//        }
//
//        if (pid1 == 0) {    //we are in child process
//            dup2(pipe_fd[1], STDOUT_FILENO);
//            close(pipe_fd[0]);
//            close(pipe_fd[1]);          //as it was duplicated, we can close the fd1 ends as well so we have 1 left
//            execlp("ping","ping", "-c", "1", "google.com", NULL);         //test case
//        }
//
//        int pid2 = fork();
//        if (pid2 < 0) {
//            printf("Error in fork - ret 3");
//            exit(1);
//        }
//
//        //child process 2
//        if (pid2 == 0) {
//            dup2(pipe_fd[0], STDIN_FILENO);
//            close(pipe_fd[0]);
//            close(pipe_fd[1]);
//            execlp("grep", "grep", "rtt", NULL);          //test case
//        }
//
//        close(pipe_fd[0]);
//        close(pipe_fd[1]);
//
//        waitpid(pid1, NULL, 0);
//        waitpid(pid2, NULL, 0);
//    }

    /* Forking a child process to run the command in */
    pid_t processid = fork();

    if (processid == -1) {
        printf("\nFailed forking child..");
        return;
    } else if (processid == 0) {
        /* If no commands match then the shell uses exec to search for files (programs) to run that match the userinput.
            e.g. "ls" or "cd" */
        execvp(command[0][0], command[0]);
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
    char userInput[MAXLENGTH] = "";
    char **commandArray[MAXLENGTH] = {NULL};
    int pipeStatus=0;
    printCurrentLoc();
    fgets(userInput,MAXLENGTH,stdin);
    pipeStatus = sortInput(userInput,commandArray);
    execute_command(commandArray,pipeStatus);
    pipeStatus=0;
  }
}
