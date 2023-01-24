#ifndef __CATARRAY_H__
#define __CATARRAY_H__
#include <stdlib.h>

struct category_tag {
  char * category;
  char ** wordlist;
  size_t n_words;
};
typedef struct category_tag category_t;

struct catarray_tag {
  category_t ** catlist;
  size_t n_cats;
};
typedef struct catarray_tag catarray_t;

#endif
