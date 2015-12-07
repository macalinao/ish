#pragma once

#include "program.h"

class ExecutionStep {
  public:
    ExecutionStep(Program* program);
    void setPipe(ExecutionStep* step);
    pid_t execute(int* pfds);
  private:
    Program* program;
    ExecutionStep* pipe;
};
