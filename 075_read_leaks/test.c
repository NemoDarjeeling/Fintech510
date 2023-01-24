#include <stdio.h>
#include <stdlib.h>

int f(int n) {
  int * p = malloc(2 * sizeof(*p));
  p[0] = n;
  p[1] = n+2;
  int ans = p[0] * p[1];
  free(p);
  return ans;//until this line, malloc p needs to be freed because the function is returning
}

int main(void) {
  int * p = malloc(4 * sizeof(*p));
  int * q = p;
  int ** r = &q;
  p[0] = f(1);
  *r = NULL;
  free(p);
  q = malloc(2 * sizeof(*q));
  p = q;//until this line, malloc p needs to be freed because p is assigned to other value
  free(q);
  q = NULL;
  return EXIT_SUCCESS;//until this line malloc q needs to be freed because the function is returning
}
