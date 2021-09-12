#include <string.h>
#include <stdlib.h>

void parseInput();
void tokenizerLoop();


/* Splits the input into an array of strings where command and arguments are */
void parseInput(char* input, char** destination[]){
        
    /* Rinse entire input for '\n' (not sure this is needed) */
    
    /* Search for chars matching '|' (pipe) first */
    if(strstr(input,"|"))
    {
        char* tokenString = strtok(input, "|");
        char* singleCommand[1024];
        
    } 
    else
    {
        tokenizerLoop(input," \n",destination);
    }

}


/* Takes a pointer to a char array(string) as input
   and splits it up into tokens delimited by the
   defined delimiter. 
   It requires a pointer to a string array to update
   values in that array 
*/
void tokenizerLoop(char *input, char*delim, char** output[])
{
    int i=0;
    char *tokenString;
    tokenString = strtok(input,delim);
    output[i] = tokenString;

    while(tokenString != NULL)
    {
        output[i] = tokenString;
        i++;
        tokenString= strtok(NULL, delim);
    }   tokenString = strtok(NULL, delim);
}