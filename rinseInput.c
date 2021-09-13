#include <string.h>
#include <malloc.h>



/* Takes a pointer to a char array(string) as input
   and splits it up into tokens delimited by the
   defined delimiter.
   It requires a pointer to a string array to update
   values in that array
*/
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
        for(int i=0; commands[i] != NULL;i++)
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




