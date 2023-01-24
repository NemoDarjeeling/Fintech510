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
    std::vector<std::string> assetRaw;
    std::vector<std::string> assetName;
    std::vector<std::vector<std::string> > assetPrice;
    std::vector<std::vector<double> > assetPriceTps;
    std::vector<std::vector<double> > assetRor;
    std::vector<double> assetRorAvg;
    std::vector<double> assetStd;
    std::vector<std::vector<double> > assetCov;
    std::vector<std::vector<double> > assetCorr;

public:
    asset();
    void process_assetRaw(int argc, char ** argv);//读取文件，获取每个元素是原文件一行的vector
    void process_assetName();//处理assetRaw，获取每个元素是一个资产名的vector
    void process_assetPrice();//处理assetRaw，获取每个元素是资产具体价格的vector的vector,每个资产都有初始价，但后续数据没有处理
    double legalPrice(std::string s, double pre);//合法化每个数据
    void process_assetPriceTps();//转置assetPrice，获取这样一个vector的vector：有若干行资产，每行是一个资产的随时间变化的、不为空的价格
    void process_assetRor();//处理assetPrice，获取这样一个vector的vector：有若干行资产，每行是一个资产的随时间变化的收益率（比assetPriceTps少一列）
    void process_assetRorAvg();//处理assetRor，获取每个元素是一种资产的平均收益率的vector
    void process_assetStd();//处理assetPrice和assetRor，获取每个元素是一种资产的收益率标准差的vector
    void process_assetCov();//处理assetRor和assetStd，获取这样一个vector：covariance matrix
    void process_assetCorr();//处理assetCov和assetStd，获取这样一个vector：correlation matrix
    void print_assetCorr();//打印correlation matrix
};
