char* filterArguments(char** arguments,int howManyArg){
  int i = 1; /* Setting index to 1 to avoid getting the command in the mix */
  int amountOfArgsToReturn = howManyArg;
  int count = 0;
  char* result = NULL;
  int totalLength = 0;

  // Close program if input is empty
  if (arguments == NULL){
    printf("%s","Argument input strings are NULL");
    return NULL;
  }

  // Iterate through the array to find out the size
  while(arguments[i]!=NULL){
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
    strcat(result,arguments[i]);
  }
  return result;

}







char* filterArguments(char** arguments,int howManyArg){
  int i = 1; /* Setting index to 1 to avoid getting the command in the mix */
  int amountOfArgsToReturn = howManyArg+1;
  int count = 0;
  char* result = NULL;
  int totalLength = 0;

  // Close program if input is empty
  if (arguments[i] == NULL){
    printf("%s","Argument input strings are NULL");
    return NULL;
  }

  // Iterate through the array to find out the size
  while(arguments[i]!=NULL){
    totalLength = strlen(arguments[i]);
    i++;
  }
  count = i; 
  totalLength++; // Incrementing totalLength once more than needed to make sure we dont have a memory fault

  // Allocate memory for the result string
  result = malloc(sizeof(char)*totalLength);
  if(result==NULL){
    printf("%s", "Memory allocation failed somehow\n");
    return NULL;
  }

    // Concatenate input strings into result
  for(i=1; i<amountOfArgsToReturn; i++){
    strcat(result,arguments[i]);
  }
  return result;

}








    // Change path to the specified path
  else if(strcmp(arguments[0],"cd")==0 | strcmp(arguments[0], "CD")==0){
    char* path = filterArguments(arguments,1);
    cd(path);
  }