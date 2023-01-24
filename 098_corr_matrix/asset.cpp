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

asset::asset() {}//just used to initialize asset

void asset::process_assetRaw(int argc, char ** argv) {
    std::ifstream ifs;
    ifs.open(argv[1], std::ifstream::in);
    if (!ifs.is_open()) {//test case 3
        std::cerr << "file open fails" << std::endl;
        exit(EXIT_FAILURE);
    }
    std::string line_f;
    while(getline(ifs, line_f)) {
        assetRaw.push_back(line_f);
    }
    // for(std::vector<std::string>::iterator it = assetRaw.begin(); it != assetRaw.end(); ++it) {
    //     std::cout << *it << " p.a.row success" << std::endl;
    // }
    ifs.close();
}

void asset::process_assetName() {
    std::string header = assetRaw[0];
    std::stringstream header_stream(header);
    std::string asset_name;
    while (getline(header_stream, asset_name, ',')) {
        assetName.push_back(asset_name);
    }
    std::vector<std::string>::iterator i = assetName.begin();
    assetName.erase(i); // 去掉“Time”一栏
    // for (std::vector<std::string>::iterator it = assetName.begin(); it != assetName.end(); ++it) {
    //     std::cout << *it << " p.a.name success" << std::endl;
    // }
    // std::cout << "numColumn in assetName is " << assetName.size() << std::endl;
}

void asset::process_assetPrice() {
    for (size_t i = 1; i < assetRaw.size(); ++i) { // 跳过第一行的表头
        std::string price_line = assetRaw[i];
        for (size_t a = 0; a < price_line.size(); ++a) { // 建议直接用delim，参见efficient frontier，直接修改原数据容易出问题
            if (price_line[a] == ',') {
                price_line[a] = '\n';
            }
        }

        std::string price;
        std::stringstream price_line_stream(price_line);
        std::vector<std::string> tempPriceLine;
        getline(price_line_stream, price); // 跳过第一格的时间
        while (getline(price_line_stream, price)) {
            if (i == 1 && price == "null") { // 仅处理第一行数据的问题，保证所有资产都有合法的初始价；直接自己写legalNum()，这个限制性太强，不好
                std::cerr << "null price in one column of the first row" << std::endl;
                exit(EXIT_FAILURE);                
            } 
            if (i == 1 && price == " ") {
                std::cerr << "blank price in one column of the first row" << std::endl;
                exit(EXIT_FAILURE);                
            }
            if (i == 1) {
                double numPrice;
                try {
                    numPrice = std::stod(price);
                } 
                catch (std::invalid_argument & e) {
                    std::cerr << "other non-empty invalid price in one column of the first row" << std::endl;
                    exit(EXIT_FAILURE); 
                }
            }
            // std::cout << "test for price: "<< price << std::endl;
            tempPriceLine.push_back(price);
        }


// std::cout << "store this line successfully" << std::endl;


        // std::vector<std::string>::iterator it = tempPriceLine.begin();
        // tempPriceLine.erase(it);


// std::cout << "Col PriceLine: " << tempPriceLine.size() << std::endl;
// std::cout << "Col assetName: " << assetName.size() << std::endl;

        if (tempPriceLine.size() != assetName.size()) {//test case 4, 有名字没数据，有数据没名字
            std::cerr << "missing (one) asset name or (a column of) asset prices" << std::endl;
            exit(EXIT_FAILURE);
        }
        assetPrice.push_back(tempPriceLine);     
    }
    // for (int m = 0; m < 254; ++m) {
    //     for (int n = 0; n < 7; ++n) {
    //         std::cout << assetPrice[m][n] << ' ';
    //     }
    //      std::cout << '\n';
    //  }
}

double asset::legalPrice(std::string s, double pre) {
    try {
        return std::stod(s);
    }
    catch (std::invalid_argument & e) {
        return pre;
    }
}

void asset::process_assetPriceTps() {
    std::vector<std::vector<std::string> > assetPriceTps_temp;
    std::vector<std::string> assetPriceTps_line_temp;

    for (size_t n = 0; n < assetPrice[0].size(); ++n) {

        for (size_t m = 0; m < assetPrice.size(); ++m) {
            assetPriceTps_line_temp.push_back(assetPrice[m][n]);
        }
        assetPriceTps_temp.push_back(assetPriceTps_line_temp);
        assetPriceTps_line_temp.erase(assetPriceTps_line_temp.begin(), assetPriceTps_line_temp.end());
    }
    //   for (int x = 0; x < 7; ++x) {
    //       for (int y = 0; y < 254; ++y) {
    //           std::cout << assetPriceTps_temp[x][y] << ' ';
    //       }
    //       std::cout << '\n';
    //   }

    size_t numRow = assetPriceTps_temp.size();
    size_t numCol = assetPriceTps_temp[0].size();
    
    assetPriceTps.resize(numRow);//initialize assetPriceTps
    for (size_t x = 0; x < numRow; ++x) {
        assetPriceTps[x].resize(numCol);
    }

    for (size_t i = 0; i < numRow; ++i) { // prevent the intimidating "invalid read of size 8"，因为直接调用legalPrice的时候，对于初始值i = 0,j = 0, assetPriceTps[i][j - 1]是传不进去的
        assetPriceTps[i][0] = std::stod(assetPriceTps_temp[i][0]);
    }

    for (size_t i = 0; i < numRow; ++i) {
        for (size_t j = 1; j < numCol; ++j) {
                assetPriceTps[i][j] = legalPrice(assetPriceTps_temp[i][j], assetPriceTps[i][j - 1]);
        }
    } 
    //   for (int x = 0; x < numRow; ++x) {
    //        for (int y = 0; y < numCol; ++y) {
    //           std::cout << assetPriceTps[x][y] << ' ';
    //      }
    //       std::cout << '\n';
    //   }
}

void asset::process_assetRor() {
    size_t numRow = assetPriceTps.size();
    size_t numCol = assetPriceTps[0].size() - 1;
    
    assetRor.resize(numRow);//initialize assetRor
    for (size_t x = 0; x < numRow; ++x) {
        assetRor[x].resize(numCol);
    }

    for (size_t i = 0; i < numRow; ++i) {
        for (size_t j = 0; j < numCol; ++j) {
            assetRor[i][j] = assetPriceTps[i][j + 1] / assetPriceTps[i][j] - 1; // 恰好assetPriceTps比assetRor多一列，所以正好不会超界（也不是正好，这是数学
        }
    }
//   for (int x = 0; x < numRow; ++x) {
//       for (int y = 0; y < numCol; ++y) {
//          std::cout << assetRor[x][y] << ' ';
//       }
//          std::cout << '\n';
//      }
}

void asset::process_assetRorAvg() {
    size_t numRow = assetRor.size();
    size_t numCol = assetRor[0].size();
    double sum = 0;
    for (size_t i = 0; i < numRow; ++i) {
        for (size_t j = 0; j < numCol; ++j) {
            sum += assetRor[i][j];
        }
        assetRorAvg.push_back(sum / numCol);
        sum = 0;//很关键，不在每行加完之后清零，就会一直加
    } 
    // for (int x = 0; x < numRow; ++x) {
    //     std::cout << assetRorAvg[x] << ' ';
    // }
}

void asset::process_assetStd() {
    size_t numRow = assetRor.size();
    size_t numCol = assetRor[0].size();
    double sum = 0;
    for (size_t i = 0; i < numRow; ++i) {
        for (size_t j = 0; j < numCol; ++j) {
            sum += (assetRor[i][j] - assetRorAvg[i]) * (assetRor[i][j] - assetRorAvg[i]);
        }
        sum = sum / (numCol - 1);
        assetStd.push_back(sqrt(sum));
        sum = 0;
    }    
    //  std::cout << '\n';
    //  for (int x = 0; x < numRow; ++x) {
    //  std::cout << assetStd[x] << ' ';
    //  }        
}

void asset::process_assetCov() {
    size_t numRow = assetRor.size();
    size_t numCol = assetRor[0].size();

    assetCov.resize(numRow);
    for (size_t x = 0; x < numRow; ++x) {
        assetCov[x].resize(numRow);
    }

    for (size_t i = 0; i < numRow; ++i) {
        for (size_t j = 0; j < numRow; ++j) {
            double sum_cov = 0;
            for(size_t k = 0; k < numCol; ++k) {
                sum_cov += (assetRor[i][k] - assetRorAvg[i]) * (assetRor[j][k] - assetRorAvg[j]);
            }
            sum_cov = sum_cov / numCol;
            assetCov[i][j] = sum_cov;
        }
    }

    //  for (int x = 0; x < numRow; ++x) {
    //      for (int y = 0; y < numRow; ++y) {
    //          std::cout << assetCov[x][y] << ' ';
    //      }
    //      std::cout << '\n';
    //  }    
}

void asset::process_assetCorr() {
    size_t numRow = assetRor.size();

    assetCorr.resize(numRow);
    for (size_t x = 0; x < numRow; ++x) {
        assetCorr[x].resize(numRow);
    }

    for (size_t i = 0; i < numRow; ++i) {
        for (size_t j = 0; j < numRow; ++j) {
            if (i == j) {
                assetCorr[i][j] = 1;
            }
            else {
                assetCorr[i][j] = assetCov[i][j] / (assetStd[i] * assetStd[j]);
            }
        }
    }
    // for (int x = 0; x < numRow; ++x) {
    //     for (int y = 0; y < numRow; ++y) {
    //         std::cout << assetCorr[x][y] << ' ';
    //     }
    //     std::cout << '\n';
    // }    
}

void asset::print_assetCorr() {
    for (size_t i = 0; i < assetName.size(); ++i) {
        std::cout << assetName[i] << std::endl;
    }

    size_t numRow = assetRor.size(); // 你也妹用到啊
    size_t numCol = assetRor[0].size(); // 你也妹用到啊

	for (int i = 0; i < assetCorr.size(); ++i) {
		if (i == 0) { // 第一行的起头
            std::cout << "[";
        }
		else { // 不是第一行的起头
            std::cout << " ";
        }

		for (int j = 0; j < assetCorr.size(); ++j) { // 打印这一行
			if (j != assetCorr.size() - 1) {
				std::cout << std::setw(7) << std::fixed << std::setprecision(4) << assetCorr[i][j]<<',';
			}
			else std::cout << std::setw(7) << std::fixed << std::setprecision(4) << assetCorr[i][j];
		}

		if (i != assetCorr.size() - 1) { // 不是最后一行的结尾
            std::cout << std::endl;
        }
		else { // 最后一行的结尾
            std::cout << "]";
        }
	}   
}
