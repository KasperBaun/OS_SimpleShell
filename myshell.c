#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h> // Used by waitpid()
#include <dirent.h>
#include <asm-generic/errno-base.h>
#include <errno.h>

#define MAXLENGTH 1024 /* Maximum length of input string */
#define MAXCMD 10 /* Maximum amount of cmd+args */

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
        printf("%s\n","4. Most linux commands works since the shell makes use of \nexecvp() system call and searchs the $PATH variable for binaries matching");
        printf("%s\n","5. Type 'exit/Exit' to exit the shell");
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
void printArrayContent(char*array[]){
    if(array[0]==NULL) return;
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
        } return 1;
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
         /* Implement pipe functionality here */
   /* More than one command so we need to redirect some output to another process */            
        char recv[MAXLENGTH];
        int pipefd[2];
        pipe(pipefd);
        pid_t pid;
        pid=fork();
            
            
            if(pid==-1) {
                 perror("fork in execute_command pipe section");
                exit(1);
            }   
            else if (pid==0)
            {
                /* We are in child process */
                close(pipefd[0]); /* Close read-end of pipe */
                FILE *out = fdopen(pipefd[1],"w"); /* Open pipe as stream for writing */
                dup2(pipefd[1], 1);  // send stdout to the pipe
                //dup2(pipefd[1], 2);  // send stderr to the pipe
                close(pipefd[1]);    // this descriptor is no longer needed
                execvp(command[0][0],command[0]);
                exit(0);
            } 
            else if(pid>0)
            {   
                wait(0); /* Wait for child to die */
                /* We are in parent process */
                close(pipefd[1]); /* Close writing end of pipe */
                FILE *in = fdopen(pipefd[0],"r"); /* Open pipe as stream for reading */
                FILE *fp;
                fp = fopen("receiveFile.txt","w");
                fread(recv, 1,MAXLENGTH,in); /* Write to stream from pipe */
                int i = 0;
                while(recv[i] != NULL) {
                    /* write to file using fputc() function */
                    fputc(recv[i], fp);
                    i++;
                }
                char cwdfile[256];
                getcwd(cwdfile,sizeof(cwdfile));
                strcat(cwdfile,"/");
                strcat(cwdfile,"receiveFile.txt");
                command[1][2] = cwdfile;
                fclose(fp);
                close(pipefd[0]);          /* Close unused read end */
             }
                    
            pid_t pid2 = fork();
                if(pid2==-1) {
                    perror("fork in execute_command pipe section");
                    exit(1);
                } else if(pid2==0){
                    execvp(command[1][0],command[1]);
                    exit(0);
                } else if(pid2>0)
                {
                    wait(0);
                    return;                
                } 
            }  

    

    /* Forking a child process to run the command in */
    if(pipeStatus == 0){
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
            wait(0);
            return;
        }
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
    char **commandArray[MAXCMD] = {NULL};
    int pipeStatus=0;
    printCurrentLoc();
    fgets(userInput,MAXLENGTH,stdin);
    pipeStatus = sortInput(userInput,commandArray);
    execute_command(commandArray,pipeStatus);
  }
}
