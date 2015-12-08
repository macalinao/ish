#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <vector>

#include "command.h"
#include "execution_step.h"
#include "parser.h"
#include "program.h"
#include "tokenizer.h"

Command::Command(std::string str) {
  this->str = str;
}

void Command::execute() {
  const char* cmd = this->str.c_str();
  try {
    std::vector<ExecutionStep*> steps = parse_tokens(*tokenize(cmd));
    for (std::vector<ExecutionStep*>::iterator it = steps.begin(); it != steps.end(); it++) {
#if PARSE_ONLY
      (*it)->describeR();
#else
      (*it)->execute(-1);
#endif
    }
  } catch (std::string ex) {
    fprintf(stderr, "ish: error running command %s: %s\n", cmd, ex.c_str());
    return;
  }
}
