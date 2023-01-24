#include <cstdlib>    
#include <fstream>    
#include <iostream>
#include <sstream>   
#include <vector>
#include <string>
#include <cmath>
#include <iomanip>
#include <cassert>

class asset {
private:
    std::string fileName;
    std::vector<bool> check;
    std::vector<std::string> assetName;
    std::vector<std::vector<double> > arr;
    std::vector<double> avg_ROI;
    std::vector<std::vector<double> > ROI;
    std::vector<double> SD;
    std::vector<std::vector<double> > COV;
    std::vector<std::vector<double> > CORR;

public:
    asset(std::string filename);
    bool IsDoubleString(const std::string & s);
    void init();
    void calROI();
    void calAvg_ROI();
    void calSD();
    void calCOV();
    void calCOV();
    void calCORR();
    void outCORR();
    ~asset() {}
};