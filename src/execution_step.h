#pragma once

#include "program.h"

class ExecutionStep {

  public:
    ExecutionStep(Program* program);
    void setPipe(ExecutionStep* step);
    void setInfile(std::string file);
    void setOutfile(std::string file);
    void execute(int in_fd);
    void describe();
    void describeR();

  private:
    Program* program;
    ExecutionStep* toPipe;
    std::string infile;
    std::string outfile;
};
