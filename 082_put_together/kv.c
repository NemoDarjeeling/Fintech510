#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"

kvpair_t * splitPairs(char * str) {
  char * value1 = strchr(str,'=');
  *value1 = '\0';
  value1 ++;//get value1 "red" in "apple=red", and make array str stop before "=" ("apple")

  char * n = strchr(value1,'\n');//check the last element of each line, \n
  if(n != NULL) {//make it no longer \n, but just \0, we don't need it to go to next line; and also we want to indicate the end of string- value1
    *n ='\0';
  }
  
  kvpair_t * pair = malloc(sizeof(*pair));
  pair->key = str;//assign str to key in pair
  pair->value = value1;//assign value1 to value in pair
  return pair;  
}

kvarray_t * readKVs(const char * fname) {
  FILE * f = fopen(fname, "r");
  if (f == NULL) {
    perror("Could not open file");
    return NULL;
  }

  //read the lines
  char * line = NULL;
  size_t sz = 0;//initialise sz
  kvpair_t * curr_pair = NULL;//initialise curr_pair to NULL
 
  kvarray_t * kv_array = malloc(sizeof(*kv_array));
  kv_array->size = 0;//initialise with 0, for size in kv_array, which is the length of the array
  kv_array->arr = NULL;//initialise with NULL, for arr in kv_array, which is key=value pairs
  
  while (getline(&line, &sz, f) != EOF) {//if the line get is not EOF (int -1), keep getting lines; note: alrealy getting the first line
    curr_pair = splitPairs(line);//split the line and store "key" "value" into curr_pair
    kv_array->arr = realloc(kv_array->arr, (kv_array->size + 1) * sizeof(*kv_array->arr));//add one more slot in memory for next pair
    kv_array->arr[kv_array->size] = curr_pair;//assign curr_pair to (size)th element(which is a also pair with "key" and "value") 
    kv_array->size ++;//prepare to move to the next, which is (size+1)th element
    line = NULL;//？？？why do we have to do this, line with be automatically rewritten by getline
  }
  free(line);//getline is in heap, need to be freed

  int result=fclose(f);
  if (result != 0) {
    return NULL;
  }
  return kv_array;
}

void freeKVs(kvarray_t * pairs) {
  for(int i = 0 ;i < pairs->size; i++) {
    free(pairs->arr[i]->key);
    //free(pairs->arr[i]->value);why, key is a pointer, value is a pointer, free key, but not free value? because that's what you do with the splitpair to create key and value, it is using the same address of one line repeatly, also concerns the problem of free(line) does not free all lines
    free(pairs->arr[i]);
  }
  free(pairs->arr);
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  kvpair_t * print_pair;//initialise a pair to store to-print pair
  for(int i = 0; i < pairs->size; i++){
    print_pair = pairs->arr[i];//assign value of to-print pair to print_pair
    printf("key = '%s' value = '%s'\n", print_pair->key, print_pair->value);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  kvpair_t * curr_pair;
  for(int i = 0; i < pairs->size; i++){
    curr_pair = pairs->arr[i];
    if (!strcmp(curr_pair->key, key)) {//if in this pair, its key == key we want, then strcmp == 0, then we return the pair's value 
      return curr_pair->value;
    }
  }
  return NULL;
}

