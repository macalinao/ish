#include "execution_step.h"
#include "program.h"

ExecutionStep::ExecutionStep(Program* program) {
  this->program = program;
}

void ExecutionStep::setPipe(ExecutionStep* step) {
  this->pipe = step;
}

void ExecutionStep::execute(int* pfds) {
  pfds[0] = 1;
}
