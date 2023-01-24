#include <cstdlib>    
#include <fstream>    
#include <iostream>
#include <sstream>   
#include <vector>
#include <string>
#include <cmath>
#include <iomanip>
#include <cassert>
#include <Eigen/Dense>

#include "portfolio.hpp"

portfolio::portfolio() {}

double portfolio::legalNum(std::string s) {
    try {
        return std::stod(s);
    }
    catch (std::invalid_argument & e) {
        std::cerr << "encounter non-numeric input!" << std::endl;
        exit(EXIT_FAILURE);
    }
}

std::vector<std::string> portfolio::parseLine(std::string line, std::string delim) {//code provided by Dr. Slankas in Dec 9th, 22:00
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

void portfolio::process_ror_std(char * fileName) {
    std::ifstream ifa;
    std::vector<std::string> all_ror_prot;
    std::vector<std::string> all_std_prot;
    ifa.open(fileName, std::ifstream::in);
    if (!ifa.is_open()) {
        std::cerr << "universe file open fails!" << std::endl;
        exit(EXIT_FAILURE);
    }
    if (ifa.peek() == std::ifstream::traits_type::eof()) {
        std::cerr << "universe file is empty!" << std::endl;
        exit(EXIT_FAILURE);
    }    
    std::string line;
    std::string delim = ",";
    std::vector<std::string> line_vec;
    while(getline(ifa, line)) {
        line_vec = parseLine(line, delim);
        if (line_vec.size() != 3) {
            std::cerr << "missing name/ror/std in universe file!" << std::endl;
            exit(EXIT_FAILURE);
        }    
        all_name.push_back(line_vec[0]);  
        all_ror_prot.push_back(line_vec[1]);
        all_std_prot.push_back(line_vec[2]);
    }   

    if (all_name.size() != all_ror_prot.size() || all_name.size() != all_std_prot.size()) {
        std::cerr << "a name field does not have its required value in universe file!" << std::endl;
        exit(EXIT_FAILURE);
    }

    double delement_ror;
    for(size_t i = 0; i < all_ror_prot.size(); ++i) {
        delement_ror = legalNum(all_ror_prot[i]);
        all_ror.push_back(delement_ror);
    }
    // for(size_t i = 0; i < all_ror.size(); ++i) {
    //     std::cout << all_ror[i] << std::endl;
    // }
    double delement_std;
    for(size_t i = 0; i < all_std_prot.size(); ++i) {
        delement_std = legalNum(all_std_prot[i]);
        all_std.push_back(delement_std);
    }
    ifa.close();       
}

void portfolio::process_all_cov(char * fileName) {
    std::ifstream ifb;
    ifb.open(fileName, std::ifstream::in);
    if (!ifb.is_open()) {
        std::cerr << "correlation file open fails!" << std::endl;
        exit(EXIT_FAILURE);
    }
    if (ifb.peek() == std::ifstream::traits_type::eof()) {
        std::cerr << "correlation file is empty!" << std::endl;
        exit(EXIT_FAILURE);
    }
    std::string line;
    std::vector<std::vector<double> > all_corr;
    while(getline(ifb, line)) {// 建议使用parseLine()，这里没换只是当时没出问题
        for (size_t a = 0; a < line.size(); ++a) {
            if (line[a] == ',') {
                line[a] = '\n';
            }  
        }
        std::string element;
        double delement;
        std::stringstream line_stream(line);
        std::vector<double> dline_corr;
        while(getline(line_stream, element)) {
            delement = legalNum(element);
            dline_corr.push_back(delement);
        }
        if (dline_corr.size() != all_name.size()) {
            std::cerr << "unmatched number for asset names and number for correlations(numColumn)" << std::endl;
            exit(EXIT_FAILURE);
        }
        all_corr.push_back(dline_corr);       
    }
    if (all_corr.size() != all_name.size()) {
        std::cerr << "unmatched number for asset names and number for correlations(numRow)" << std::endl;
        exit(EXIT_FAILURE);        
    }

    size_t numRow = all_corr.size();
    size_t numCol = all_corr[0].size();
    all_cov.resize(numRow);//initialize all_cov
    for (size_t x = 0; x < numRow; ++x) {
        all_cov[x].resize(numCol);
    }

    for (size_t i = 0; i < numRow; ++i) {
        for (size_t j = 0; j < numCol; ++j) {
            if (i == j) {
                if (all_corr[i][j] != 1) {
                    std::cerr << "data value incorrect in correlation matrix!" << std::endl;
                    exit(EXIT_FAILURE);
                }
            }
            all_cov[i][j] = all_corr[i][j] * (all_std[i] * all_std[j]);
        }
    }    
    // for (size_t i = 0; i < all_cov.size(); ++i) {
    //     for (size_t j = 0; j < all_cov[i].size(); ++j) {
    //         std::cout << all_cov[i][j] << " ";
    //     }
    //     std::cout << "\n";
    // }    
    ifb.close();    
}

void portfolio::prepare_matrix_l() {
    Matrix_l.resize(0,0);//prevent memory collision during loops
    size_t num = all_name.size();
    A = Eigen::MatrixXd(2, num);
    for (size_t i = 0; i < num; ++i) {
        A(0, i) = 1;
        A(1, i) = all_ror[i];
    }
    A_trans = A.transpose();
    // std::cout << "A_trans: " << std::endl << A_trans << std::endl;
    Sigma = Eigen::MatrixXd(num, num);
    for (size_t i = 0; i < num; ++i) {
        for (size_t j = 0; j < num; ++j) {
            Sigma(i, j) = all_cov[i][j];
        }
    }
    Matrix_l = Eigen::MatrixXd::Zero(num + 2, num + 2);
    Matrix_l.block(0, 0, num, num) = Sigma;
    Matrix_l.block(0, num, num, 2) = A_trans;
    Matrix_l.block(num, 0, 2, num) = A;
    // std::cout << "Matrix_l: " << std::endl << Matrix_l << std::endl; 
    
}

void portfolio::cal_vola(double rp) {
    size_t num = all_name.size();
    Eigen::VectorXd Matrix_r = Eigen::VectorXd::Zero(num + 2);
    Matrix_r(num) = 1;
    Matrix_r(num + 1) = rp;
    // std::cout << "Matrix_r: " << std::endl << Matrix_r << std::endl;
    Eigen::VectorXd Matrix_ans;
    Matrix_ans = Matrix_l.colPivHouseholderQr().solve(Matrix_r);
    // std::cout << "Matrix_ans: " << std::endl << Matrix_ans << std::endl;     
    std::vector<double> ans_vec;
    ans_vec.resize(num);
    for (size_t i = 0; i < num; ++i) {
        ans_vec[i] = Matrix_ans(i);
    } 
    // std::cout << "ans_vec: " << std::endl;
    // for (size_t i = 0; i < num; ++i) {
    //     std::cout << ans_vec[i] << std::endl;
    // }
    all_ans_vec.push_back(ans_vec);

    double sum = 0;
    double temp = 0;
    for (size_t i = 0; i < num; ++i) {
        for (size_t j = 0; j < num; ++j) {
            temp = ans_vec[i] * ans_vec[j] * all_cov[i][j];
            sum += temp;
        }
    }
    double vola = std::sqrt(sum);
    // std::cout << "volatility for " << rp << ": " << vola << std::endl;
    all_vola.push_back(vola);
}


int portfolio::negNum(std::vector<double> v) {
    for (size_t i = 0; i < v.size(); ++i) {
        if (v[i] < 0.00) {
            // std::cout << "there is negative in ans_vec_temp" <<std::endl;
            return 0; 
        }
    }
    // std::cout << "no negative in ans_vec_temp" <<std::endl;
    return 1;
}

void portfolio::cal_vola_res(double rp) {
    size_t num = all_name.size();
    size_t ind = (rp - 0.01) / 0.01;   
    std::vector<double> ans_vec_temp = all_ans_vec[ind];
    std::vector<int> index_neg;
    int M_size = num + 2;
    Eigen::MatrixXd Matrix_l_res_pre = Matrix_l;

    while (negNum(ans_vec_temp) != 1) {
        index_neg.clear();
        int neg_num = 0;
        for (size_t i = 0; i < ans_vec_temp.size(); ++i) {
            if (ans_vec_temp[i] < 0) {
                index_neg.push_back(i);
                neg_num += 1;
            }    
        }
        // std::cout << "neg_num: " << neg_num << std::endl;
        M_size += neg_num;
        // std::cout << "M_size for this loop: " << M_size << std::endl;
        Eigen::MatrixXd Matrix_l_res = Eigen::MatrixXd::Zero(M_size, M_size);
        Matrix_l_res.block(0, 0, M_size - neg_num, M_size - neg_num) = Matrix_l_res_pre;
        for (size_t i = 0; i < neg_num; ++i) {
            Matrix_l_res(index_neg[i], M_size - neg_num + i) = 1;
            Matrix_l_res(M_size - neg_num + i, index_neg[i]) = 1;
        }
        Matrix_l_res_pre = Matrix_l_res;
        // std::cout << "Matrix_l_res: " << std::endl << Matrix_l_res <<std::endl;//!!!

        Eigen::VectorXd Matrix_r_res = Eigen::VectorXd::Zero(M_size);
        Matrix_r_res(num) = 1;
        Matrix_r_res(num + 1) = rp;  
        // std::cout << "Matrix_r_res: " << std::endl << Matrix_r_res <<std::endl;//!!!

        Eigen::VectorXd Matrix_ans_res;
        Matrix_ans_res = Matrix_l_res.colPivHouseholderQr().solve(Matrix_r_res);
        // std::cout << "Matrix_ans_res: " << std::endl << Matrix_ans_res << std::endl;

        for (size_t i = 0; i < num; ++i) {
            ans_vec_temp[i] = Matrix_ans_res(i);
        }

        // std::cout << "ans_vec_temp: "; 
        // for (size_t i = 0; i < num; ++i) {
        //    std::cout << ans_vec_temp[i] << " ";
        // }
        // std::cout << std::endl;
    }

    double sum = 0;
    double temp = 0;
    for (size_t i = 0; i < num; ++i) {
        for (size_t j = 0; j < num; ++j) {
            temp = ans_vec_temp[i] * ans_vec_temp[j] * all_cov[i][j];
            sum += temp;
        }
    }    
    double vola_res = std::sqrt(sum);
    // std::cout << "restricted volatility for " << rp << ": " << vola_res << std::endl;
    all_vola_res.push_back(vola_res);
}

void portfolio::print_vola() {
    std::cout << "ROR,volatility" << std::endl;
    for (size_t i = 0; i < 26; ++i) {
        double rp = 0.01 + i * 0.01;
        double volatility = all_vola[i];
        std::cout << std::fixed << std::setprecision(1) << rp * 100.0 << "%,";
        std::cout << std::fixed << std::setprecision(2) << volatility * 100.0 << "%" << std::endl;
    }
}

void portfolio::print_vola_res() {
    std::cout << "ROR,volatility" << std::endl;
    for (size_t i = 0; i < 26; ++i) {
        double rp = 0.01 + i * 0.01;
        double volatility_res = all_vola_res[i];
        std::cout << std::fixed << std::setprecision(1) << rp * 100.0 << "%,";
        std::cout << std::fixed << std::setprecision(2) << volatility_res * 100.0 << "%" << std::endl;
    }    
}





