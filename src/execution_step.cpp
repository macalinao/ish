#include <fcntl.h>
#include <iostream>
#include <sys/stat.h>
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
  this->toPipe = NULL;
  this->infile = "";
  this->outfile = "";
}

void ExecutionStep::setPipe(ExecutionStep* step) {
  toPipe = step;
}

void ExecutionStep::setInfile(std::string file) {
  infile = file;
}

void ExecutionStep::setOutfile(std::string file) {
  outfile = file;
}

void ExecutionStep::execute(int in_fd) {
  if (in_fd == -1) {
    if (fork() != 0) {
      wait(0);
      return;
    }
  }

  const char* executable = this->program->getExecutable().c_str();
  char** argv = this->program->argv();

  int out_fd = -1;
  if (outfile != "") {
    out_fd = open((char*) outfile.c_str(), O_WRONLY | O_CREAT, 0666);
  }

  if (toPipe == NULL) {
    dup2(in_fd, STDIN_FILENO);
    if (out_fd != -1) {
      dup2(out_fd, STDOUT_FILENO);
    }
    execvp(executable, argv);
    perror("execvp failed");
    exit(1);
    return;
  }

  int fd[2];
  if (pipe(fd) == -1) {
    perror("Pipe failed");
    exit(1);
  }

  switch (fork()) {
    case -1:
      perror("Fork failed");
      exit(1);
      break;

    case 0:
      close(fd[0]); /* unused */
      dup2(in_fd, STDIN_FILENO);  /* read from in_fd */
      dup2(fd[1], STDOUT_FILENO); /* write to fd[1] */
      execvp(executable, argv);
      perror("execvp failed");
      exit(1);
      break;

    default: /* parent: execute the rest of the commands */
      close(fd[1]); /* unused */
      close(in_fd); /* unused */
      toPipe->execute(fd[0]); /* execute the rest */
  }

}
