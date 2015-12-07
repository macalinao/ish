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

pid_t ExecutionStep::execute(int infd) {
  pid_t pid = fork();

  // error check
  if (pid == -1) {
    throw std::string("can't fork");
  }

  if (infd != -1) {
    close(0); // Close stdin
    dup2(infd, 0); // redirect in from other prog to here
  }

  int fds[2];
  if (pipe(fds) == -1) {
    throw std::string("Pipe failed");
  }

  // return child pid
  if (pid != 0) {

    // Create pipe
    if (toPipe != NULL) {
      return toPipe->execute(fds[0]);
    }

    return pid;
  }

  // Fork

  if (pid == 0) {

    if (toPipe != NULL) {
      // Pipe
      close(1); // Close stdout
      dup(fds[1]); // Use pipe write
    }

    if (toPipe != NULL || infd != -1) {
      close(fds[0]); // close pipe read
      close(fds[1]);
    }

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

  return pid;

}
