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
  this->toPipe = NULL;
}

void ExecutionStep::setPipe(ExecutionStep* step) {
  this->toPipe = step;
}

void ExecutionStep::execute(int* parent_des_p) {
  int* des_p = new int[2];
  if (pipe(des_p) == -1) {
    perror("Pipe failed");
    exit(1);
  }

  if (fork() == 0) {
    if (toPipe != NULL) {
      close(STDOUT_FILENO);          // closing stdout
      dup(des_p[1]);     // replacing stdout with pipe write
      close(des_p[0]);   // closing pipe read
      close(des_p[1]);

      toPipe->execute(des_p);
    }

    if (parent_des_p != NULL) {
      close(0);          //closing stdin
      dup2(parent_des_p[0], STDIN_FILENO);     //replacing stdin with pipe read
      close(parent_des_p[1]);   //closing pipe write
      close(parent_des_p[0]);
    }

    const char* executable = this->program->getExecutable().c_str();
    char** argv = this->program->argv();
    execvp(executable, argv);
    perror("execvp failed");
    exit(1);
  }

  wait(0);
  if (toPipe != NULL) wait(0);

}
