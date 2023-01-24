#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/*int find_e(int * array) {//go through the array, find and record the most frequent character(index) and number
    int is_e_num = 0;
    int is_e_chr = 0;
    for (int m = 0; m < 26; m++) {
        if (array[i] > is_e_num) {
            is_e_num = array[m];
            is_e_chr = m;
        }
    }
    return is_e_chr;
}*/

//???not possible to build extra function, or bus error

int find_key(FILE * f) {
    /*int * array1;
    for (int i = 0; i <26; i++) {
        array1[i] = 0;//create an array with 26 "slots" for 26 characters to store their number of appearance
    }*/
    //sometimes unable to use my own code to construct array with 26 slots.
    int array1[26]={0};

    int chr;
    while((chr = fgetc(f)) != EOF) { //trying to go through the whole file and store the number of 26 char. each in an array, 0th stores number for a, 26th stores number for z, like a implicit dictionary
        if (isalpha(chr)) {
            chr = tolower(chr);
            chr = chr - 'a';//??why only 'a', "a" does not work?
            array1[chr] = array1[chr] + 1;
        }
    }

    int is_e_num = 0;
    int is_e_chr = 0;
    for (int m = 0; m < 26; m++) {
        if (array1[m] > is_e_num) {
            is_e_num = array1[m];
            is_e_chr = m;
        }
    }

    //int is_e = find_e(array1);
   
    /*int key1 = is_e_chr - ("e" - "a");//e+key is within the round of 26 
    int key2 = 26 + is_e_chr - ("e" - "a");//e+key is exceeding this round of 26 and going to the next round
    if (key1 < 0 || key1 >= 26) {
        return key2;
    }
    else {
        return key1;
    }*/
    //???not possible to use my own code to calcalute, or bus error.

    int k =  0;
    if (is_e_chr >= ('e' - 'a')) {
        k = is_e_chr - ('e' - 'a');
    }
    else {
        k = (26 - ('e' - 'a')) + is_e_chr;
    } 
    return k;
}

int main(int argc, char ** argv){
     if (argc != 2) {//check if the number of command line is correct
       fprintf(stderr,"incorrect arguments numbers\n");//standard expression to print for command line problem
       return EXIT_FAILURE;
     }


    FILE * f= fopen(argv[1], "r");//open the file, readable only

    if (f == NULL) {//check if the file exists
       perror("unable to open file");//standard expression to print for open-file problem
       return EXIT_FAILURE;      
    }
    
    int key = find_key(f);
    printf("%d\n", key);

    if (fclose(f) != 0) {
    perror("unable to close the input file");//standard expression to print for close-file problem
    return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;  
 }

