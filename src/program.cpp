#include <iostream>
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

char* convert(const std::string & s) {
	char *pc = new char[s.size() + 1];
	std::strcpy(pc, s.c_str());
	return pc;
}

char** Program::argv() {
  std::vector<std::string> args = this->arguments;
  std::vector<char*> argv;
  argv.push_back((char*) this->executable.c_str());
  std::transform(args.begin(), args.end(), std::back_inserter(argv), convert);
  argv.push_back((char*) NULL);
  return (char**) &argv[0];
}
