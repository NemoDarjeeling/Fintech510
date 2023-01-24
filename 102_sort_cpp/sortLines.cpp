#include <algorithm>  //std::sort
#include <cstdlib>    //EXIT_SUCCESS
#include <fstream>    //std::ifstream
#include <iostream>   //std::cin std::cout std::cerr
#include <vector>     //std::vector
#include <string>

void sort(std::vector<std::string> lines){
    std::sort(lines.begin(), lines.end());
    for(std::vector<std::string>::iterator it = lines.begin(); it != lines.end(); ++it) {
        std::cout << *it << std::endl;
    }
}

void sort_lines() {
    std::string str_l;
    std::vector<std::string> lines_l;
    while (!std::cin.eof()) {
        getline(std::cin, str_l);//getline虽然是帮你把前者里面的东西存到后者里，但是本身是有值的
        lines_l.push_back(str_l);
    }
    // if ((is.eof() != 1) && (is.good() != 1)) {
    //     std::cerr << "line read fails" << std::endl;
    //     exit(EXIT_FAILURE);
    // }
    sort(lines_l);
    //no need to delete str for getline, as vector has done it for you，但是捏vector只会在超出定义范围才会帮你自动释放所有内存，如果你的vector是写在主函数里面,就一直不回超出范围，也就一直不会帮你释放内存，这时候就需要使用.clear()
}

void sort_file(int argc, char ** argv) {
  for (int i = 1; i < argc; i++) {
    std::ifstream ifs;
    ifs.open(argv[i], std::ifstream::in);

    if (!ifs.is_open()) {
      std::cerr << "file open fails" << std::endl;
      exit(EXIT_FAILURE);
    }

    std::string str_f;
    std::vector<std::string> lines_f;
    while(getline(ifs, str_f)) {
        lines_f.push_back(str_f);
    }
    sort(lines_f);
    ifs.close();
  }
}

int main(int argc, char ** argv) {
    if (argc == 1) {//read from cin 
        sort_lines();//如果希望给sort_lines里面传标准输入的参数，比如std::cin，那在外面的函数里面必须用std::istream & a 去兜住这个输入；如果不传参数，那也ok，外面的函数也不需要传参数，需要用到输入的时候在函数体里面直接用就好
    }
    else {//read from file
        sort_file(argc, argv);
    }
}

