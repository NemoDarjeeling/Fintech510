#include <algorithm>  //std::sort
#include <cstdlib>    //EXIT_SUCCESS
#include <fstream>    //std::ifstream
#include <iostream>   //std::cin std::cout std::cerr
#include <vector>     //std::vector

void sort_lines(std::istream & is) {//used to sort if only standard input is provided//创建流对象is,in the type of istream,is what you want to read into the computer
  std::string str;//declare a string called str
  std::vector<std::string> lines;//declare a vector called lines, in which elements are strings
  while (getline(is, str)) {//get line from istream called is, and store value(which is a string) in str
    lines.push_back(str);//store each str in lines using lines
  }
  if ((is.eof() != 1) && (is.good() != 1)) {//check if EOF is true, which means "is" is empty; check if "is" stream is working properly
    std::cerr << "error occurs when read lines from file" << std::endl;//if not, standard output stream for errors
    exit(EXIT_FAILURE);
  }
  std::sort(lines.begin(), lines.end());//sort vector lines from the beginning to the end
  std::vector<std::string>::iterator it = lines.begin();//construct a specific iterator for lines
  while (it != lines.end()) {
    std::cout << *it << std::endl;//as "it" is a pointer, we have to dereference it to get the actual value inside
    ++it;//move the pointer one further down
  }
}

void sort_file(int argc, char ** argv) {//used to sort if fileName is provided, and typical way to read from files: argc is the length of the command line, and argv is the command line itself, in which there are multiple strings representing the 
  for (int i = 1; i < argc; i++) {//iterate through the command line to deal with each file needs to be sorted
    std::ifstream ifs(argv[i], std::ifstream::in);//创建流对象ifs; 以读文件的形式形式(in)打开argv[i]对应文件
    if (!ifs.is_open()) {//judge if the file has been opened successfully
      std::cerr << "file open fails" << std::endl;//if not, standard output stream for errors
      exit(EXIT_FAILURE);
    }
    sort_lines(ifs);//employ sort_lines to deal with information in stream ifs
    ifs.close();//close file
  }
}

int main(int argc, char ** argv) {
  if (argc == 1) {
    sort_lines(std::cin);
  }
  if (argc > 1) {
    sort_file(argc, argv);
  }
  return EXIT_SUCCESS;
}