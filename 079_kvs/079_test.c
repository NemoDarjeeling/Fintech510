#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"

/*kvpair_t * splitPairs(char * str) {
  char * value1 = strchr(str,'=');
  *value1 = '\0';
  value1 ++;//get value1 "red" in "apple=red", and make array str stop before "=" ("apple")

  char * n = strchr(value1,'\n');//check the last element of each line, \n
  if(n != NULL) {//make it no longer \n, but just \0, we don't need it to go to next line.
    *n ='\0';
  }
  
  kvpair_t * pair = malloc(sizeof(*pair));
  pair->key = str;//assign str to key in pair
  pair->value = value1;//assign value1 to value in pair
  return pair;  
}

void printKVs(kvarray_t * pairs) {
   kvpair_t* curr_pair;
   for(int i=0;i<pairs->size;i++){
    curr_pair=pairs->arr[i];
    printf("key = '%s' value = '%s'\n" ,curr_pair->key, curr_pair->value);
  }
  //WRITE ME
}

int main () {
   //const char str[] = "apple=red";
   //char * value1 = strchr(str,'=');//create value1 to store the "=apple", and point at the first element of this array "="
   //*value1 = '\0';//replace the first element of "=" to "\0", which is NULL, the string ends here!
   //value1 ++;//move the pointer one element forward, so now value1 is "red" and points at "r" 

   //printf("%s is key, %s is value", str, value1);
   
   //return(0);

  FILE * f = fopen("test.txt", "r");
  if (f == NULL) {
    perror("Could not open file");
    return -1;
  }

  //read the lines
  char * line = NULL;
  size_t sz = 0;//initialise sz
  kvpair_t * curr_pair = NULL;//initialise curr_pair to NULL
 
  kvarray_t * kv_array = malloc(sizeof(*kv_array));
  kv_array->size = 0;//initialise with 0, for size in kv_array, which is the length of the array
  kv_array->arr = NULL;//initialise with NULL, for arr in kv_array, which is key=value pairs
  
  while (getline(&line, &sz, f) != EOF) {//if the line get is not EOF (int -1), keep getting lines; note: alrealy getting the first line
    curr_pair=splitPairs(line);//split the line and store "key" "value" into curr_pair
    kv_array->arr=realloc(kv_array->arr, (kv_array->size + 1) * sizeof(*kv_array->arr));//add one more slot in memory for next pair
    kv_array->arr[kv_array->size]=curr_pair;//assign curr_pair to (size)th element(which is a also pair with "key" and "value") 
    kv_array->size ++;//prepare to move to the next, which is (size+1)th element
    line = NULL;//？？？why do we have to do this, line with be automatically rewritten by getline
  }
  
  free(line);

  int result=fclose(f);
  if (result != 0) {
    return -1;
  }

  printKVs(kv_array);

  return 0;
}*/

kvpair_t * splitPairs(char * str) {
  
  char * value1 = strchr(str,'=');
  *value1 = '\0';
  value1 ++;
  char * n = strchr(value1,'\n');
  if(n != NULL) {
    *n ='\0';
  }
  kvpair_t * pair = malloc(sizeof(*pair));
  pair->key = str;
  pair->value = value1;
  return pair;  
}

int main () {
    char str[] = "apple=red";
    kvpair_t * pairs = splitPairs(str);
    printf("%s is key, %s is value", pairs->key, pairs->value);
    free(pairs->key);
    free(pairs->value);
    return 0;
}