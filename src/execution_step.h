#pragma once

#include "program.h"

class ExecutionStep {
  public:
    ExecutionStep(Program* program);
    void setPipe(ExecutionStep* step);
    void execute(int* parent_des_p);
  private:
    Program* program;
    ExecutionStep* toPipe;
};
