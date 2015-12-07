#include "execution_step.h"
#include "parser.h"

#define STATE_INIT 0
#define STATE_PIPE 1

ExecutionStep* parse(std::vector<std::string> tokens) throw (std::string) {
  ExecutionStep* head = NULL;
  ExecutionStep* prev = NULL;
  int executionState = STATE_INIT;

  std::vector<std::string> execTokens;

  for (std::vector<std::string>::iterator it = tokens.begin(); it != tokens.end(); it++) {
    std::string token = *it;

    // pipe
    if (token == "|") {

      if (!head) {
        throw "Invalid pipe -- no step before specified.";
      }

      ExecutionStep* step = new ExecutionStep(new Program(execTokens));

      if (executionState == STATE_INIT) {
        head = step;
      }

      if (executionState == STATE_PIPE) {
        prev->setPipe(step);
      }

      prev = step;

    } else {

      execTokens.push_back(token);

    }
  }

  ExecutionStep* end = new ExecutionStep(new Program(execTokens));
  if (executionState == STATE_INIT) {
    head = end;
  } else if (executionState == STATE_PIPE) {
    prev->setPipe(end);
  }

  return head;
}
