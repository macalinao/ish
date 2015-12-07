#pragma once

#include "program.h"

class ExecutionStep {
  public:
    ExecutionStep(Program* program);
    void setPipe(ExecutionStep* step);
    void execute(int* pfds);
  private:
    Program* program;
    ExecutionStep* pipe;
};
