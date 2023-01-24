#include <cstdlib>    
#include <fstream>    
#include <iostream>
#include <sstream>   
#include <vector>
#include <string>
#include <cmath>
#include <iomanip>
#include <cassert>



vector<string> parseLine(const std::string line, const std::string delim) {
    std::vector<std::string> result;
    auto start = 0U;
    auto end = line.find(delim);
    while (end != std::string::npos) {
        result.push_back(line.substr(start, end - start));
        start = end + delim.length();
        end = line.find(delim, start);
    }
    result.push_back(line.substr(start, end));
    return result;
}

int main() {
    const string line = "Inv Grade credit,0.079072,0.059322";
    const string delim = ",";
    parseLine(line, delim);
    return 0;
}