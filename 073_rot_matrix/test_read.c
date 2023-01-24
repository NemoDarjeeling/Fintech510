#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main() {//this function is meant to test if the code can read from a file and store the elements in the corresponding array
    //printf("%d\n", __LINE__);    
    FILE * f = fopen("sample.txt", "r");
    if (f == NULL) {
        perror("Could not open file");
        return EXIT_FAILURE;
    }
    //printf("%d\n", __LINE__);

    char prematri[10][10] = {0}; //do we still need to initialize it to 0?
    //printf("%d\n", __LINE__);
    char element = 0;
    //printf("%d\n", __LINE__);
    
    //while ((element = fgetc(f)) != EOF) {
        element = fgetc(f);
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                if (element != '\n' || element != EOF) {
                    prematri[i][j] = element;
                    //printf("%d\n", __LINE__);
                    element = fgetc(f);
                    //printf("%d\n", __LINE__);
                    //printf("%d\n", __LINE__);
                }
                else {
                 perror("line too short");
                 return EXIT_FAILURE;
                }
            }
            //element = fgetc(f);
            if (element != '\n') {
                perror("this is a line too long");
                return EXIT_FAILURE;
            }
            else {
                element = fgetc(f);
            }
        }
    //}
    if (element != EOF) {
        perror("too much data");
        return EXIT_FAILURE;
    }

    for (int m = 0; m < 10; m++) {//just to print the array to see the result
        for (int n = 0; n < 10; n++) {
            //printf("%d\n", __LINE__);
            printf("%c", prematri[m][n]);
            //printf("%d\n", __LINE__);
        }
        printf("\n");
    }  

    return 0;
}
