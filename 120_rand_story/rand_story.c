#include "rand_story.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void freeWords(catarray_t * words) {
    if (words == NULL) {
        return;
    } 
    for (size_t i = 0; i < words->n_cats; ++i) {
        category_t * curCategory = words->catlist + i;
        for (size_t j = 0; j < curCategory->n_words; ++j) {
            free(curCategory->wordlist[j]);            
        }
        free(curCategory->wordlist);
        free(curCategory->category);
    }
    free(words->catlist);
    free(words);
}

