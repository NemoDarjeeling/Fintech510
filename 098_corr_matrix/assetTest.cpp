#include <cstdlib>    
#include <fstream>    
#include <iostream>
#include <sstream>   
#include <vector>
#include <string>
#include <cmath>
#include <iomanip>
#include <cassert>

#include "assetTest.hpp"

asset::asset(std::string temp) {//get the filename, nothing special
    fileName = temp;
}

bool asset::IsDoubleString(const std::string & s) {
    char * e = 0;
    double val = strtod(s.c_str(), &e);
    return e != s.c_str() && *e == '\0' && val != HUGE_VAL;
}

void asset::init() {
    std::ifstream infile(fileName);//open the file
    if (!infile) {//open failure
        std::cerr << "No such file!" << std::endl;
        exit(EXIT_FAILURE);
    }
    std::string temp;
    std::string t;
    getline(infile, temp);
    std::stringstream str(temp);//get the first line and turn it into stringstream
    int flag = 0;
    int check = 0;
    while (getline(str, t, ',')) {
        if (flag == 0) {
            ++flag;
            continue;
        }
        ++check;
        assetName.push_back(t);//store the names in the first line
    }

    int row = 0;
    int col = 0;
    while (getline(infile, temp)) {//starting with the second line
        col = 0;
        std::vector<double> tmp; 
        std::stringstream data(temp);
        t.clear();
        flag = 0;
        while (getline(data, t, ',')) {
            if (flag == 0) {
                ++flag;
                continue; 
            }

            if (IsDoubleString(t)) {//decide if the price is double type
                double a;
                std::stringstream num(t);
                num >> a;
                tmp.push_back(a);//store the price data into tmp
            }
            else {//if the price is not double type
                if (row == 0) {//if it is the first line, error
                    std::cerr << "error" << std::endl;
                    exit(EXIT_FAILURE);
                }
                else {//if it is not, use the previous price data
                    tmp.push_back(arr[row - 1][col]);
                }   
            }
            ++col;
        }
        if (check != col) {//if numColumns in asset name not numColumns in price
            std::cerr << "error" << std::endl;
            exit(EXIT_FAILURE);
        }
        arr.push_back(tmp);//我们并不转置数据，只要把他们变成vector使得里面每一个数据都能被index access就行
        ++row;
    }
    assert(row > 1);
}

void asset::calROI() {
    int row = arr.size();
    int col = arr[0].size();//get the size of rows and columns
    if (row == 1) {//if there is only one row, useless
        std::vector<double> temp;
        for (int j = 0; j < col; ++j) {
            temp.push_back(0);
        }
        ROI.push_back(temp);
    }
    else {//if there is more than one row of price data
        for (int i = 1, i < row; ++i) {
            std::vector<double> temp;
            for (int j = 0; j < col; ++j) {
                if (arr[i - 1][j] < 1e-15) {
                    std::cerr << "error" << endl;
                    exit(EXIT_FAILURE);
                }
                double num = 0;
                num = (arr[i][j] - arr[i - 1][j]) / arr[i - 1][j];
                temp.push_back(num);
            }
            ROI.push_back(temp);
        }
    }
}

void asset::calAvg_ROI() {
    int col = ROI[0].size(); 
    int row = ROI.size();
    for (int i = 0; i < col; ++i) {
        double sum = 0;//不转置数据的弊端
        for (int j = 0; j < row; ++j) {
            sum += ROI[j][i];
        }
        avg_ROI.push_back(sum / row);
    }
}

void asset::calSD() {
    int col = ROI[0].size();
    int row = ROI.size();
    for (int i = 0; i < col; ++i) {
        double sum = 0;
        for (int j = 0; j < row; ++j) {
            sum += (ROI[j][i] - avg_ROI[i]) * (ROI[j][i] - avg_ROI[i]);
        }
        if (row != 1) {
            sum /= (row - 1)
        } 
        SD.push_back(sqrt(sum));
    }
}

void asset::calCOV() {
    int row = ROI.size();
    int col = ROI[0].size();
    COV.resize(col);
    for (int i = 0; i < col; ++i) {
        COV[i].resize(col);
    }
    for (int i = 0; i < col; ++i) {
        for (int j = i; j < col; ++j) {
            double sum = 0;
            for (int k = 0; k < row; ++k) {
                sum += (ROI[k][i] - avg_ROI[i]) * (ROI[k][j] - avg_ROI[j]);
            }
            sum /= row;
            COV[i][j] = sum;
            COV[j][i] = sum;//对角线对折，一模一样的，直接复制
        }
    }
}

void asset::calCORR() {
    int col = ROI[0].size();
    CORR.resize(col);
    for (int i = 0; i < col; ++i) {
        CORR[i].resize(col);
    }
    for (int i = 0; i < col; ++i) {
        for (int j = i; j < col; ++j) {
            if (i == j) {//corr(a,a)
                CORR[i][j] = 1;
                continue;
            }
            if (SD[i] * SD[j] != 0) {//test non-volatile asset, possible? seem not in test case...
                CORR[i][j] = COV[i][j] / (SD[i] * SD[j]);
            }
            else {
                CORR[i][j] = 0;
            }
            CORR[j][i] = CORR[i][j];
        }
    }
}

void asset::outCORR() {
    int len = assetName.size();
    for (int i = 0; i < len; ++i) {
        cout << assetName[i] << endl;
    }

    cout << '[';
    int row = CORR.size();
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < row; ++j) {
            if (j == 0) {
                if (i == 0) {
                    cout << std::setw(7) << std::fixed << std::setprecision(4) << CORR[i][j];
                }
                else {
                    cout << std::setw(8) << std::fixed << std::setprecision(4) << CORR[i][j];
                }
            }
            else {
                cout << "," << std::setw(7) << std::fixed << std::setprecision(4) << CORR[i][j];
            }
        }
        if (i != row - 1) {
            cout << endl;
        }
        else {
            cout << ']' << endl;
        }
    }
}




