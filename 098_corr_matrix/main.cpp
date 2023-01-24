#include <cstdlib>    
#include <fstream>    
#include <iostream>
#include <sstream>   
#include <vector>
#include <string>
#include <cmath>
#include <iomanip>
#include <cassert>

#include "asset.hpp"

int main(int argc, char ** argv) {
    if (argc != 2) {//test case 1; test case 2
        if (argc == 1) {
            std::cerr << "please input filename" << std::endl;
        }
        else {
            std::cerr << "incorrect command line length" << std::endl;
        }
        exit(EXIT_FAILURE);
    }
    else {
        asset assetClass;
        assetClass.process_assetRaw(argc, argv);
        assetClass.process_assetName();
        assetClass.process_assetPrice();
        assetClass.process_assetPriceTps();
        assetClass.process_assetRor();
        assetClass.process_assetRorAvg();
        assetClass.process_assetStd();
        assetClass.process_assetCov();
        assetClass.process_assetCorr();
        assetClass.print_assetCorr();
    }
    return 0;
}