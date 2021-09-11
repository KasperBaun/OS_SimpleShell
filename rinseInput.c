#include <string.h>
#include <stdlib.h>

void sortStrings();


// Splits the input into an array of strings where command and arguments are
void sortStrings(char* input, char* destination){
    int i=0;
    char* tokenString = strtok(input, " \n");
    
    while (tokenString != NULL)
    {         
      destination[i] = tokenString;
      i++;    
      tokenString = strtok(NULL, " \n");
    } tokenString = strtok(NULL, " \n");
}