#include <cstdlib>    
#include <fstream>    
#include <iostream>
#include <sstream>   
#include <vector>
#include <string>
#include <cmath>
#include <iomanip>
#include <cassert>

int portfolio::negNum(std::vector<double> v) {
    for (size_t i = 0; i < v.size(); ++i) {
        if (v[i] < 0.00) {
            std::cout << "there is negative in ans_vec_temp" <<std::endl;
            return 0; 
        }
    }
    std::cout << "no negative in ans_vec_temp" <<std::endl;
    return 1;
}

int main() {
    std::vector<double> v1 = {1,2,3,4,5,6,7};
    negNum(v1);
    std::vector<double> v2 = {1,2,3,-4,5,6,7};
    negNum(v2);
    std::vector<double> v3 = {1,2,-3,4,-5,6,7};
    negNum(v3);
    return 0;
}