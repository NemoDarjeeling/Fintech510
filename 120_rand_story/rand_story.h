#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__
#include <stdlib.h>
#include "catarray.h"

catarray_t * readWords(FILE * f);
addWord();
catIndex();
addCat();
addWordToCat();

void readStory(FILE * f, catarray_t * words);
parseLine();
replaceBlank();

void freeWords(catarray_t * words);

#endif