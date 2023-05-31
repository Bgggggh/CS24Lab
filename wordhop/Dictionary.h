#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <istream>
#include <string>
#include <vector>
#include <unordered_map>
#include <cmath>

class Dictionary {
  // Member Variables
  public:
  std::vector<std::unordered_map<std::string,std::vector<std::string>>*> dict;


  // Helper Functions

public:
  Dictionary(std::istream& stream);
  ~Dictionary();
  // The create function used by the autograder:
  static Dictionary* create(std::istream& stream);

public:
  // The function that does all the work:
  std::vector<std::string> hop(const std::string& from, const std::string& to);

};



#endif
