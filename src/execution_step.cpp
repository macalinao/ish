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
  if (pipe(fds) == -1) {
    throw std::string("Pipe failed");
  }

  pid_t pid = fork();

  // error check
  if (pid == -1) {
    throw std::string("can't fork");
  }

  // return child pid
  if (pid != 0) {
    return pid;
  } else {

    const char* executable = this->program->getExecutable().c_str();
    char** argv = this->program->argv();
    execvp(executable, argv);

    // Error
    fprintf(stderr, "ish: couldn't exec %s: %s\n", this->program->toString().c_str(), strerror(errno));
    exit(EX_DATAERR);
    return 0;

  }

  int status;
  if ((pid = waitpid(pid, &status, 0)) < 0) {
    fprintf(stderr, "ish: waitpid error: %s\n", strerror(errno));
  }
}
