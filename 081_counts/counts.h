#ifndef __COUNTS_H__
#define __COUNTS_H__
struct _one_count_t {
  char * str;//a particular string
  size_t cnt;//count times that particular string has occurred !!!initialize everything!!!
};
typedef struct _one_count_t one_count_t;

struct _counts_t {
  one_count_t ** cntArr;//an array of one_count_t, of which each has a string and its count
  size_t cntSize;//size of the array
  size_t unkown;//a field to count unknown names
};
typedef struct _counts_t counts_t;

counts_t * createCounts(void);
void addCount(counts_t * c, const char * name);
void printCounts(counts_t * c, FILE * outFile);

void freeCounts(counts_t * c);

#endif
