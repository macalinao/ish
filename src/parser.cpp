#include <exception>
#include <iostream>

#include "execution_step.h"
#include "parser.h"

#define STATE_INIT 0
#define STATE_PIPE 1

ExecutionStep* parse_tokens(std::vector<std::string> tokens) throw (std::string) {
  ExecutionStep* head = NULL;
  ExecutionStep* prev = NULL;
  int executionState = STATE_INIT;

  std::vector<std::string> execTokens;

  for (std::vector<std::string>::iterator it = tokens.begin(); it != tokens.end(); it++) {
    std::string token = *it;

    // pipe
    if (token == "|") {

      ExecutionStep* step = new ExecutionStep(new Program(execTokens));
      if (executionState == STATE_INIT) {
        head = step;
      }

      if (head == NULL) {
        throw std::string("Invalid pipe -- no step before specified.");
      }

      if (executionState == STATE_PIPE) {
        prev->setPipe(step);
      }

      prev = step;

      execTokens = std::vector<std::string>();

      executionState = STATE_PIPE;

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
