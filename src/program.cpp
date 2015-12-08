#include <iostream>
#include <sstream>
#include <stdio.h>
#include <string>
#include <vector>

#include "program.h"

Program::Program(std::string str) {
  std::vector<std::string> args;
  const char* s = str.c_str();
  char* p = strtok((char*) s, " ");
  this->executable = p;
  while ((p = strtok(NULL, " "))) {
    args.push_back(p);
  }
  this->arguments = args;
}

Program::Program(std::vector<std::string> tokens) {
  this->executable = tokens.front();
  tokens.erase(tokens.begin(), tokens.begin() + 1);
  this->arguments = tokens;
}

std::string Program::getExecutable() {
  return this->executable;
}

std::vector<std::string> Program::getArguments() {
  return this->arguments;
}

std::vector<std::string> Program::getArgumentsWithoutOptions() {
  return this->argsWithPrefix("-", true);
}

std::vector<std::string> Program::getOptions() {
  return this->argsWithPrefix("-", false);
}

std::vector<std::string> Program::argsWithPrefix(std::string prefix, bool negate) {
  std::vector<std::string> args = this->arguments;
  std::vector<std::string> ret;
  for (std::vector<std::string>::iterator it = args.begin(); it != args.end(); it++) {
    std::string arg = *it;
    if ((!negate && arg.find(prefix) == 0) || (negate && arg.find(prefix) != 0)) {
      ret.push_back(arg);
    }
  }
  return ret;
}

const char* convert(const std::string & s) {
  return s.c_str();
}

char** Program::argv() {
  std::vector<std::string> args = this->arguments;
  std::vector<const char*>* argv = new std::vector<const char*>();
  argv->push_back(this->executable.c_str());
  std::transform(args.begin(), args.end(), std::back_inserter(*argv), convert);
  argv->push_back((char*) NULL);
  return (char**) &(*argv)[0];
}

std::string Program::toString() {
  return this->executable;
}

void Program::describe() {
  std::cout << "Command: " << this->executable << std::endl;

  std::vector<std::string> opts = getOptions();
  std::vector<std::string> args = getArgumentsWithoutOptions();

  std::stringstream optss;
  for (std::vector<std::string>::iterator it = opts.begin(); it != opts.end(); it++) {
    optss << *it << " ";
  }

  std::cout << "Options: " << optss.str() << std::endl;

  std::stringstream argss;
  for (std::vector<std::string>::iterator it = args.begin(); it != args.end(); it++) {
    argss << *it << " ";
  }

  std::cout << "Arguments: " << argss.str() << std::endl;
}
