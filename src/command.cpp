#include <exception>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sysexits.h>
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
  if ((pid = fork()) == -1) {
    fprintf(stderr, "ish: can't fork: %s\n", strerror(errno));
    return;
  }

  if (pid == 0) {
    try {
      ExecutionStep* start = parse_tokens(*tokenize(cmd));
      start->execute(new int[3]);
    } catch (std::string ex) {
      fprintf(stderr, "ish: error running command %s: %s\n", cmd, ex.c_str());
      return;
    }
  }

  int status;
  if ((pid = waitpid(pid, &status, 0)) < 0) {
    fprintf(stderr, "ish: waitpid error: %s\n", strerror(errno));
  }

}
