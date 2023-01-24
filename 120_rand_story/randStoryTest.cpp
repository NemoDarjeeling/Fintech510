#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <sstream>

class wordinfo{
private:
  std::string name;
  std::vector<std::string> list;
  size_t size;
//for instance: name: animal; list: dragon, cat, walrus; size: 3.
public:
  wordinfo(std::string _name){
    name = _name;
    size = 0;
  }

  ~wordinfo() {}

  void add_list(std::string word){
    list.push_back(word);
  }

  std::vector<std::string> get_list(){
    return list;
  }

  std::string get_name(){
    return name;
  }

  size_t get_size(){
    return size;
  }

  void add_size(){
    size += 1;
  }
};

size_t search_key(std::vector<wordinfo> all_wordlist, std::string key){//input the comprehensive wordlist and the word type, return the index of that "wordinfo"
  if (all_wordlist.size() == 0){//an empty all_wordlist and naturally nothing found
    return -1;
  }
  for (size_t i = 0; i < all_wordlist.size(); i++) {//iterate to see if there is the right type of word
    if ((all_wordlist[i]).get_name() == key) {//if there is the right type, return the index of that "wordinfo"
      return i;
    }
  }
  return -1; //searched across all_wordlist and nothing found, -1 indicates no such a key
}

std::vector<wordinfo> read_word(std::string FileName){//input words.txt, return the comprehensive wordlist
  std::fstream file(FileName, std::ios::in);//construct an object "file" in type fstream, open words.txt for read only and store everything in FileName into file
  //FILE * file = fopen(FileName, "r"); will also work, but you have to use fget rather than just getline
  //or this: std::ifstream file; file.open(FileName, std::ifstream::in); almost the same thing, ifstream subclass of fstream
  if (file.fail()) {//ios inheritance: fail
    std::cerr << "Wrong file " << std::endl;
    exit(EXIT_FAILURE);
  }
  if (file.eof()){//ios inheritance: eof
    std::cerr<<"The file is blank.";
    exit(EXIT_FAILURE);
  }

  std::vector<wordinfo> all_wordlist;  // remember to clear
  std::string line;
  std::string container;
  // get the first line
  while(std::getline(file, line)) {//get the file (from words.txt) line by line and store each line into "line"
    std::string wordtype;
    std::string word;
    std::istringstream buffer(line);//istringstream is a child class for istream, store what's in "line" into buffer
    size_t counter = 0;
    while (buffer.good()) {//ios inheritance: good
      std::getline(buffer, container, ':');//get buffer and store what's inside into container until meet ":"
      if (counter == 0){
        wordtype = container;
        counter++;
      }
      else{
        word = container;
      }
    }
    //while (std::getline(buffer, container, ':')) {
    //   if (counter == 0) {
    //      wordtype = container;
    //      counter++;
    //   }
    //   else{
    //    word = container;
    //   } 
    //}
//remember below just works for one line in words.txt!!!
    int index = search_key(all_wordlist, wordtype);//search in all wordlist to see if there is that wordtype, for instance "animal"
    if ((all_wordlist.size() == 0) || (index == -1)){//if all wordlist is empty or the wordtype is yet in all_wordlist
        wordinfo wordlist(wordtype);//construct "wordlist" in type wordinfo, and wordlist->name = wordtype, size = 0
        wordlist.add_list(word);//add word to wordlist->list
        wordlist.add_size();//add 1 to wordlist->size
        all_wordlist.push_back(wordlist);//add wordlist to all_wordlist
      }
      else {//if there is already that wordtype
        (all_wordlist[index]).add_list(word);//add word to wordlist->list
        (all_wordlist[index]).add_size();//add 1 to wordlist->size
      }
    }

  file.close();//we can test if the file is closed successfully here...
  return all_wordlist;
}

void parse_story(std::string FileName, std::vector<wordinfo> all_wordlist, int seed) {
  std::fstream file(FileName, std::ios::in);
  if (file.fail()) {
    std::cerr << "Wrong file "<< std::endl;
    exit(EXIT_FAILURE);
  }
  if (file.eof()){
    std::cerr<<"The file is blank.";
    exit(EXIT_FAILURE);
  }
//nothing special, read from story.txt and check if it successful
  std::srand(seed);//pseudo-random number generator
  std::vector<std::string> UsedWords;
  std::vector<std::string> sentence;
  std::vector<std::vector<std::string>> passage;
  int underscore = 0;
  std::string line;
  std::string word;
  while(std::getline(file, line)){
    std::istringstream buffer(line);
    while (buffer.good()) {
      std::getline(buffer, word, '_');//读到“_”就停下来，先用手头的东西往下执行
      underscore++;
      try{//take care of _1_
        int a = std::stoi(word);
        if (a != 0){
            if (a > UsedWords.size()){//不存在前a次用的词，比如一共填了俩词，第三个空你要我填写5次前填的词，那就不对 
            std::cerr<<"Index out of limit.";
            exit(EXIT_FAILURE);
            }
            std::string uword = UsedWords[UsedWords.size()-a];//往前回溯a次拿词
            sentence.push_back(uword);//把这个词添加到sentence里面
            UsedWords.push_back(uword);//也要把这个词添加到UsedWords里面，因为刚刚用过一次了
            }
      }
      catch(std::invalid_argument & e) {//take care of _animal_ and all other stuff requires no modification
      int index = search_key(all_wordlist, word);//在所有词汇类表中找这个类
      if (index == -1) {//如果没找到这个词类，说明word里面存的是两个_外面的东西，不需要做任何修改，原来是什么就是什么，直接抄就好
        sentence.push_back(word);//直接把这些短语/词/字母标点组合添加到sentence里面
      }
      else {//如果找到这个词类
        std::string rand_word = (all_wordlist[index].get_list())[rand() % all_wordlist[index].get_size()];//随机取词，用随机数%列表长度的余数做index
        sentence.push_back(rand_word);//把这个词添加到sentence里面
        UsedWords.push_back(rand_word);//也要把这个词添加到UsedWords里面，因为刚刚用过一次了
        }
      }
    }
    passage.push_back(sentence);//原封不动给每一行再安回去，“_”本来要后期去掉，但是因为直接getline的时候就读了没存，所以直接丢掉了，这里也不需要处理多余"_"的问题了
    sentence.clear();//清理这一行，以便读取下一行（直接重载可能会出现记忆丢失或者存储空间不足）
  }
  if (underscore % 2 != 0) {//下划线不一对一对出现铁有问题
    std::cerr<<"Wrong number of underscores";
    exit(EXIT_FAILURE);
  }

  for (size_t i = 0; i < passage.size(); i++) {//一行一行打印
    for (size_t j = 0; j < passage[i].size(); j++) {
      std::cout<<(passage[i])[j];
    }
    std::cout<<"\n";
  }
}

  int main(int argc, char ** argv) {
    if (argc != 4) {
      std::cerr<<"Wrong number of arguments";
      exit(EXIT_FAILURE);
    }

    std::vector<wordinfo> all_wordlist = read_word(argv[2]);

    int seed = std::atoi(argv[3]);
    if (seed < 1) {
      std::cerr<<"Wrong seed";
      exit(EXIT_FAILURE);
    }
    parse_story(argv[1],all_wordlist,seed);

    return EXIT_SUCCESS;
  }
