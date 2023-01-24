#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"
#include "counts.h"
#include "outname.h"

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  counts_t * ans = createCounts();//initialise ans with NULL and 0   
  FILE * f = fopen(filename, "r");//open file, read only
  if (f == NULL) {//if file does not exist, return NULL
    return NULL;
  }  
  char * line = NULL;
  size_t sz = 0;//initialise line and sz
  while (getline(&line, &sz, f) >= 0) {//get line until EOF
    char * n = strchr(line, '\n');//if the end of line is \n, make it to be \0, forcing the string end; if the end of the line is \0, strchr will return NULL, so n will be NULL naturally
    if(n != NULL) {
      *n = '\0';
    }
    char * x = lookupValue(kvPairs, line);//(execute to only one line)renturn the value of key if it is in key-value pair; renturn NULL if it is not in key-value pair
    //kvPairs read from file with "apple=red", line read from file with "apple", this code returns "red"
    addCount(ans, x);//(executed to only one line)get that "red", and store the correponding information in ans
  }
  free(line);
  if (fclose(f) != 0 ) {
    return NULL;
  }
  return ans;
}

int main(int argc, char ** argv) {
  //WRITE ME (plus add appropriate error checking!)
  if (argc < 2) {//command line less that 3 (./executable program, "apple=red" file, "banana" file)
    fprintf(stderr, "no enough arguments");
    return EXIT_FAILURE;
  }
  //read the key/value pairs from the file named by argv[1] (call the result kv)
  kvarray_t * kv = readKVs(argv[1]);//read from "apple=red" file and store key and value in struct

  //count from 2 to argc (call the number you count i)
  for (int i = 2; i < argc; i++) {
    //count the values that appear in the file named by argv[i], using kv as the key/value pair
    //   (call this result c)
    counts_t * c = countFile(argv[i], kv);//read from "banana" file and count how many times each key's value occurred
    if (c == NULL) {//c should be filled with value: number, if not, there is a problem
      return EXIT_FAILURE;
    }
    
    //compute the output file name from argv[i] (call this outName)
    char * outName = computeOutputFileName(argv[i]);//initialize output file name

    //open the file named by outName (call that f)
    FILE * f1 = fopen(outName, "w");

    //print the counts from c into the FILE f
    printCounts(c, f1);
    //close f
    if (fclose(f1) != 0) {
      return EXIT_FAILURE;
    }
    
    //free the memory for outName and c
    free(outName);
    freeCounts(c);
  }
  
  freeKVs(kv); //free the memory for kv

  return EXIT_SUCCESS;
}