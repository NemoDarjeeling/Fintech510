#include <stdio.h>
#include <stdlib.h>

size_t  maxSeq(int * array, size_t n) {
    if (n == 0) {
        size_t l_max = 0;
        return l_max;
    }

    if (n == 1) {
        size_t l_max = 1;
        return l_max;
    }

    size_t l_max = 0;
    int value = array[0];
    size_t m = 0;
    for (size_t i = 1; i < n; i++) {
        int next_value = array[i];
        m++;

        if (i == (n - 1)) {
            if (value < next_value) {
                m++;
                if (m > l_max) {
                    l_max = m;
                }            
            }
            else {
                return l_max;
            }
        }

        else {
            if (value < next_value) {
                value = next_value; 
            }
            else {
                value = next_value;
                if (m > l_max) {
                    l_max = m;
                }
		m = 0;
            }
        }
    }
    return l_max;
}
