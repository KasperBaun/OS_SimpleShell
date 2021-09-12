Welcome to MyShell.

1.
## COMPILE THE PROGRAM ##
To compile the program use 'gcc myshell.c -o myshell' or make myshell. Your current working directory has to be where the myshell.c and myshell.h files are located.
If neither of these 2 options work, you may not have GCC or make installed on your platform.
Using any linux distribution - type 'gcc --version' or 'make --version' in terminal to see if you have GCC or make installed.
If you are not presented with details on the version of GCC or make, please install either of the two.

2.
## RUN THE PROGRAM ##
To run the program type ./myshell. Your current working directory has to be where the myshell file is located.

3.
## MANUAL ##
The program comes with a built in manual. Upon load, instructions will print on screen to let you know the commands available.
Type 'commands' or 'Commands' to be presented with the full list of available commands.
The commands are:
 1. Type 'cd <path>' or 'CD <path>' to change current directory");
 2. Type 'pwd' for current working directory");
 3. Type 'ls' for listing files in current working directory");
 4. Type 'pipe <program>' for nothing - not implemented yet");
 5. Type 'exit/Exit' to exit the shell");



## SYSTEM CALLS ## 
The Shell makes use of system calls. 
These calls are code that is executed from the kernel of the operating system, thus having priviledged acces to hardware resources and structure.
When using a system call, the operating system switches from user-mode/space to kernel mode, executes the system call and then switches back to user-mode.

EXEC
The Shell makes use of Exec system calls that looks for a program to execute with the specified filename or path.It "takes over" the current running process with another process. It exchanges the process image.
This is implemented in the end of the read_command program.
This is because, if none of the manually implemented commands are executed, the exec system call will take command and arguments and look for file of that name or path to execute.
This effectively "extends" the shell with programs such as "pwd", "ls" and more that are allready  on the computer and requiring very little programming effort from my part.

DUP2
Copies the filedescriptor for the stdout to a path or file specified by the user.
In the simple shell you call DUP2 by typing dup2 <path/filename.txt> or DUP2 <path/filename.txt>
This redirects the output over to the path/filename.txt

## I/O REDIRECTION ##
Using the pipe function we can make the output of one process become the input for another. This is also reffered to as InputOutput Redirection.
Examples of InputOutput Redirection are:
strings myshell.c | grep poggers <- the first function "strings myshell.c" takes all the strings from myshell.c and then we pipe them to another program which uses grep to search the strings for the string "poggers". So the output from the first program becomes the input for the next program.


echo howdy > hello.txt <- this takes the output "howdy" and puts it in a hello.txt file.
cat hello.txt > howdy.txt <- this takes the hello.txt and copies it to a howdy.txt

Bibliography #2 - Gary Explains Linux Terminal Commands: Pipes and Redirection.

## PROGRAM ENVIRONMENT ##
The program environment for this shell is that the code is run on a UNIX platform seeing as system calls are not so easily done in e.g. Windows operating system.
The Shell is written in C language which has built-in system-call functions in the header <unistd.h>.


## BACKGROUND PROGRAM EXECUTION ##
A few places in the shell it makes use of fork(). This spawns a child process that can run the command or program and do it in the "background".
