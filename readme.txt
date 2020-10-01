Welcome to MyShell.

1.
## COMPILE THE PROGRAM ##
To compile the program use 'gcc myshell.c -o myshell' or make myshell. Your current working directory has to be where the myshell.c and myshel.h files are located.
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
    "1. Type 'pipe' for blablabla"
    "1. Type 'pipe' for blablabla"
    "1. Type 'pipe' for blablabla"
    "1. Type 'pipe' for blablabla"
    "1. Type 'pipe' for blablabla"
    "1. Type 'pipe' for blablabla"
    "1. Type 'pipe' for blablabla"
    "1. Type 'pipe' for blablabla"
    "1. Type 'exit/Exit' to exit the shell"



## SYSTEM CALLS ## 
The Shell makes use of system calls. 
These calls are code that is executed from the kernel of the operating system, thus having priviledged acces to hardware resources and structure.
When using a system call, the operating system switches from user-mode/space to kernel mode, executes the system call and then switches back to user-mode.



## I/O REDIRECTION ##


## PROGRAM ENVIRONMENT ##
The program environment for this shell is that the code is run on a UNIX platform seeing as system calls are not so easily done in e.g. Windows operating system.
The Shell is written in C language which has built-in system-call functions in the header <unistd.h>.


## BACKGROUND PROGRAM EXECUTION ##

