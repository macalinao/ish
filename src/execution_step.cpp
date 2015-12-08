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

  if (toPipe == NULL) {
    dup2(in_fd, STDIN_FILENO);
    if (outfile != "") {
      int out_fd = open((char*) outfile.c_str(), O_WRONLY | O_CREAT, 0666);
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
      close(fd[0]);
      if (infile != "") {
        int in_fd = open((char*) infile.c_str(), O_RDONLY, 0666);
        if (in_fd < 0) {
          perror("File not found");
          exit(1);
        }
      }
      dup2(in_fd, STDIN_FILENO);
      dup2(fd[1], STDOUT_FILENO);
      execvp(executable, argv);
      perror("execvp failed");
      exit(1);
      break;

    default:
      close(fd[1]);
      close(in_fd);
      toPipe->execute(fd[0]);
  }

}
