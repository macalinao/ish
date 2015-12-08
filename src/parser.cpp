#include <exception>
#include <iostream>
#include <vector>

#include "execution_step.h"
#include "parser.h"

#define STATE_INIT 0
#define STATE_PIPE 1

std::vector<ExecutionStep*> parse_tokens(std::vector<std::string> tokens) throw (std::string) {

  std::vector<ExecutionStep*> ret;

  ExecutionStep* head = NULL;
  ExecutionStep* prev = NULL;
  int executionState = STATE_INIT;

  std::vector<std::string> execTokens;

  for (std::vector<std::string>::iterator it = tokens.begin(); it != tokens.end(); it++) {
    std::string token = *it;

    if (token == ";" || token == "\n") {

      if (execTokens.size() == 0) {
        continue;
      }

      ExecutionStep* end = new ExecutionStep(new Program(execTokens));
      if (executionState == STATE_INIT) {
        head = end;
      } else if (executionState == STATE_PIPE) {
        prev->setPipe(end);
      }
      ret.push_back(head);
      executionState = STATE_INIT;
      execTokens = std::vector<std::string>();

    } else if (token == "|") {

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
  ret.push_back(head);

  return ret;
}
