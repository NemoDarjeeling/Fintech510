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

class portfolio {
private:
    std::vector<std::string> all_name;
    std::vector<double> all_ror;
    std::vector<double> all_std;
    std::vector<std::vector<double> > all_cov;
    Eigen::MatrixXd A;
    Eigen::MatrixXd A_trans;
    Eigen::MatrixXd Sigma;
    Eigen::MatrixXd Matrix_l;
    std::vector<std::vector<double> > all_ans_vec;
    std::vector<double> all_vola;
    std::vector<double> all_vola_res;
public:
    portfolio();
    double legalNum(std::string s);
    std::vector<std::string> parseLine(std::string line, std::string delim);
    void process_ror_std(char * fileName);
    void process_all_cov(char * fileName);
    void prepare_matrix_l();
    void cal_vola(double rp);
    int negNum(std::vector<double> v);
    void cal_vola_res(double rp);
    void print_vola();
    void print_vola_res(); 
};