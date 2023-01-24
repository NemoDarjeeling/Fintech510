#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "outname.h"

char * computeOutputFileName(const char * inputName) {
  char * outputName = malloc((strlen(inputName) + 1) * sizeof(*outputName));//though outputName just copies what it is in inputName, strlen() does not count for /0 or /n, so we want to add 1 for /0
  strcpy(outputName, inputName);//copy the latter to the former
  outputName = realloc(outputName, (strlen(inputName) + 8) * sizeof(*outputName));
  strcat(outputName,".counts");//combine two strings together
  return outputName; 
}
