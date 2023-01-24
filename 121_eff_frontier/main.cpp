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
#define OPTION "-r"

int main(int argc, char ** argv) {
  if (argc != 3 && argc != 4) {
    std::cerr << "incorrect number of command lines!" << std::endl;
    exit(EXIT_FAILURE);
  }
  if (argc == 3) {
    portfolio portfolioClass;
    portfolioClass.process_ror_std(argv[1]);
    portfolioClass.process_all_cov(argv[2]);
    portfolioClass.prepare_matrix_l();
    for (size_t i = 0; i < 26; ++i) {
        double rp = 0.01 + i * 0.01;
        portfolioClass.cal_vola(rp);
    }    
    portfolioClass.print_vola();
    return EXIT_SUCCESS;
  }
  if (argc == 4) {
    if (strcmp(OPTION, argv[1]) != 0) {
      std::cerr << "Only accept filenames and '-r' option!" << std::endl;
      exit(EXIT_FAILURE);
    }
    portfolio portfolioClass;
    portfolioClass.process_ror_std(argv[2]);
    portfolioClass.process_all_cov(argv[3]);
    portfolioClass.prepare_matrix_l();
    for (size_t i = 0; i < 26; ++i) {
        double rp = 0.01 + i * 0.01;
        portfolioClass.cal_vola(rp);
    }
    for (size_t i = 0; i < 26; ++i) {
        double rp = 0.01 + i * 0.01;
        portfolioClass.cal_vola_res(rp);
    }
    portfolioClass.print_vola_res();
    return EXIT_SUCCESS;
  }
}