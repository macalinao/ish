#include <iostream>
#include <string>
#include <vector>

#include "tokenizer.h"

std::vector<std::string>* tokenize(std::string str) {
  std::vector<std::string>* tokens = new std::vector<std::string>();
  std::string curToken = "";

  bool inString = false;

  for (std::string::iterator it = str.begin(); it != str.end(); it++) {
    char c = *it;

    if (inString && c != '"') {
      curToken += c;
      continue;
    }

    switch (c) {

      case '"':
        inString = !inString;
        break;

      case '\n':
      case ';':
      case '|':
      case '<':
      case '>':
        if (curToken != "") {
          tokens->push_back(curToken);
        }
        tokens->push_back(std::string(1, c));
        curToken = "";
        break;

      case ' ':
        if (curToken != "") {
          tokens->push_back(curToken);
        }
        curToken = "";
        break;

      default:
        curToken += c;
        break;

   }

  }

  tokens->push_back(curToken);

  return tokens;
}
