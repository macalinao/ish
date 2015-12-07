#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sysexits.h>
#include <unistd.h>

#include "execution_step.h"
#include "program.h"

ExecutionStep::ExecutionStep(Program* program) {
  this->program = program;
}

void ExecutionStep::setPipe(ExecutionStep* step) {
  this->toPipe = step;
}

pid_t ExecutionStep::execute(int* fds) {
  pid_t pid;
  if ((pid = fork()) == -1) {
    fprintf(stderr, "ish: can't fork: %s\n", strerror(errno));
    throw std::string();
  }

  if (pid != 0) {
    return pid;
  }

  pipe(fds);

  const char* executable = this->program->getExecutable().c_str();
  char** argv = this->program->argv();
  execvp(executable, argv);
  fprintf(stderr, "ish: couldn't exec %s: %s\n", this->program->toString().c_str(), strerror(errno));
  exit(EX_DATAERR);
  return 0;
}
