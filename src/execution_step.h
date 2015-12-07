#pragma once

#include "program.h"

class ExecutionStep {
  public:
    ExecutionStep(Program* program);
    void setPipe(ExecutionStep* step);
    void execute(int in_fd);
  private:
    Program* program;
    ExecutionStep* toPipe;
};
