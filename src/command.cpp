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
  pid_t pid;
  try {
    ExecutionStep* start = parse_tokens(*tokenize(cmd));
    pid = start->execute(-1);
  } catch (std::string ex) {
    fprintf(stderr, "ish: error running command %s: %s\n", cmd, ex.c_str());
    return;
  }
}
