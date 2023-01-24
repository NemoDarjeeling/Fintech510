#include <cstdlib>       
#include <iostream>
#include <sstream>   
#include <string>
#include <cmath>

int main() {
    int num_fintech = 0;
    for (int i = 1; i < 101; ++i) {
        int flag_5 = 0;
        int flag_7 = 0;
        if (i % 5 == 0) {
            flag_5 = 1;
        }
        if (i % 7 == 0) {
            flag_7 = 1;
        }

        if (flag_5 == 1 && flag_7 == 0) {
            std::cout << "Fin" << std::endl;
        }
        if (flag_5 == 0 && flag_7 == 1) {
            std::cout << "Tech" << std::endl;
        }
        if (flag_5 == 1 && flag_7 == 1) {
            std::cout << "Fintech" << std::endl;
            num_fintech += 1;
        }
        if (flag_5 == 0 && flag_7 == 0) {
            std::cout << i << std::endl;
        }
    }
    std::cout << "num_fintech: " << num_fintech << std::endl;
    return 0;
}