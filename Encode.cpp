#include "Encode.h"

std::string encode(std::string word) {
  std::string result;

  for (size_t i = 0; i < word.size(); ++i) {
    result.push_back(encodech(word[i]));
  }

  return result;
}

char encodech(char ch) {
  int tmp = ch;
  return '!' + (tmp * 1024) % 90;
}
