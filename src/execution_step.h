#pragma once

#include "program.h"

class ExecutionStep {
  public:
    ExecutionStep(Program* program);
    void setPipe(ExecutionStep* step);
    pid_t execute(int infd);
  private:
    Program* program;
    ExecutionStep* toPipe;
};
