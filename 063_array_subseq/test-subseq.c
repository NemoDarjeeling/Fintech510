#include<stdio.h>
#include<stdlib.h>

size_t maxSeq(int * array,size_t n);

int main()
{
  int arr1[] = {};
  size_t ans1 = maxSeq(arr1,0);
  if(ans1 != 0) {
    printf("incorrect answer for empty array");
    return EXIT_FAILURE;
  }
  
  int arr2[] = {1,2,1,3,5,6,2,4,6,9};
  size_t ans2 = maxSeq(arr2,10);
  if(ans2 != 4) {
    printf("incorrect answer for array with multiple increasing arrays");
    return EXIT_FAILURE;
  }
  
  int arr3[] = {1,2,3,4};
  size_t ans3 = maxSeq(arr3,4);
  if(ans3 != 4) {
    printf("incorrect answer for array with only one increasing array");
    return EXIT_FAILURE;
  }
  
  int arr4[] = {1,2,2,4};
  size_t ans4 = maxSeq(arr4,4);
  if(ans4 != 2) {
    printf("incorrect answer for array with multiple equal increasing arrays");
    return EXIT_FAILURE;
  }
  
  int arr5[] = {3,-4,5,6};
  size_t ans5 = maxSeq(arr5,4);
  if(ans5 != 3) {
    printf("incorrect answer for array with negative elements");
    return EXIT_FAILURE;
  }
  
  int arr6[] = {10,9,7,6};
  size_t ans6 = maxSeq(arr6,4);
  if(ans6 != 1) {
    printf("incorrect answer for with only decreasing array(s)");
    return EXIT_FAILURE;
  }

  int arr7[] = {1,2,3,4};
  size_t ans7 = maxSeq(arr7, 3);
  if (ans7 == 4) {
    printf("incorrect answer for wrong size of array");
    return EXIT_FAILURE;
  }
  
  return EXIT_SUCCESS;
}
