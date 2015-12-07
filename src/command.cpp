#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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
    ExecutionStep* start = parse_tokens(*tokenize(cmd));
    start->execute(-1);
    wait(0);
  } catch (std::string ex) {
    fprintf(stderr, "ish: error running command %s: %s\n", cmd, ex.c_str());
    return;
  }
}
