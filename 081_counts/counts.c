#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "counts.h"
counts_t * createCounts(void) {
  counts_t * ans = malloc(sizeof(*ans));//allocate one space for ans
  ans->cntArr = NULL;//initialise cntArr 

  
  ans->cntSize = 0;//initialise cntSize
  ans->unkown = 0;//initialise unkown
  return ans;
}

void addCount(counts_t * c, const char * name) {//addCount(ans,x)
  if (name == NULL) {//if name you want to find is not in the list, which is made to be NULL by lookupValue(), at this time add 1 to unkown
    c->unkown++;
  }
  else {//if name entered is in the list
    one_count_t * x = NULL;//initialise x, in which is one string and its count
    
    int h = 0;//a signal for whether a string is a new string first appeared so far, or it is a string we have already stored in c

    for(size_t i = 0; i < c->cntSize; i++) {//starting with cntSize=0, so won't enter the loop in the first place
      x = c->cntArr[i];//this line we not only assign the value of c->cntArr[i] to x, but also make x points to &c->cntArr[i], so what happens under is done to c, not some x outside c
      if (strcmp(x->str, name) == 0) {
        x->cnt++;
        //c->cntArr[i] = x;//!!!update this slot in c with information in x
        h = 1;//indicate this string has been stored in c, so no need to assign new value and create new slots
      }
    }

    if (h == 0) {//new string
      one_count_t * x1 = NULL;
      x1 = malloc(sizeof(*x1));
      x1->str = malloc(strlen(name) + 1);//\0 stuff
      strcpy(x1->str, name);//copy the name for the new string
      x1->cnt = 1;//record the count for this new string to be 0
      c->cntArr = realloc(c->cntArr, (c->cntSize + 1) * sizeof(*c->cntArr));//allocate next slot for str-cnt 
      c->cntArr[c->cntSize] = x1;//assign x1 to this slot
      c->cntSize++;//record the increase in number of slots
      //free(x1->str);//no need to do this, because x1 is actually malloced to also become the space in c->cntArr, so when you have already freed c->cntArr[i], you have already freed x1 and x1->str
      //free(x1);
    }
  }
}

void printCounts(counts_t * c, FILE * outFile) {
  one_count_t * x = NULL;
  for (size_t i = 0; i < c->cntSize; i++) {
    x = c->cntArr[i];
    fprintf(outFile,"%s: %zd\n", x->str, x->cnt);
  }
  if (c->unkown != 0) {
    fprintf(outFile,"<unknown> : %zd\n",c->unkown);
  }
}

void freeCounts(counts_t * c) {
  for (size_t i = 0; i < c->cntSize; i++){
    free(c->cntArr[i]->str);//str is a pointer, cnt is not, so free str not free cnt
    free(c->cntArr[i]);
  }
  free(c->cntArr);
  free(c);
}
