#include <iostream>
#include <string>
#include <vector>

std::vector<std::string>* tokenize(std::string str) {
  std::vector<std::string>* tokens = new std::vector<std::string>();
  std::string curToken = "";

  bool proceed = false;
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

      case ' ':
        proceed = true;
        break;

      default:
        curToken += c;
        break;

    }

    if (proceed) {
      tokens->push_back(curToken);
      curToken = "";
      proceed = false;
    }

  }

  tokens->push_back(curToken);

  return tokens;
}
