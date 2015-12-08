#include <exception>
#include <iostream>
#include <vector>

#include "execution_step.h"
#include "parser.h"

std::vector<ExecutionStep*> parse_tokens(std::vector<std::string> tokens) throw (std::string) {

  std::vector<ExecutionStep*> ret;

  ExecutionStep* head = NULL;
  ExecutionStep* prev = NULL;
  ExecutionStep* cur = NULL;
  std::vector<std::string> execTokens;

  for (std::vector<std::string>::iterator it = tokens.begin(); it != tokens.end(); it++) {
    std::string token = *it;

    if (token == ";" || token == "\n") {

      if (execTokens.size() != 0) {
        cur = new ExecutionStep(new Program(execTokens));
        if (prev != NULL) {
          prev->setPipe(cur);
        } else {
          head = cur;
        }
      }

      ret.push_back(head);
      execTokens = std::vector<std::string>();

    } else if (token == "|") {

      if (cur == NULL) {
        if (execTokens.size() == 0) {
          throw std::string("No tokens.");
        }
        cur = new ExecutionStep(new Program(execTokens));
      }

      if (prev != NULL) {
        prev->setPipe(cur);
      } else {
        head = cur;
      }
      prev = cur;
      cur = NULL;
      execTokens = std::vector<std::string>();

    } else if (token == "<" || token == ">" || token == ">>") {

      if (cur == NULL) {
        if (execTokens.size() == 0) {
          throw std::string("No tokens.");
        }
        cur = new ExecutionStep(new Program(execTokens));
      }

      it++;
      if (token == "<") {
        cur->setInfile(*it);
      } else {
        cur->setOutfile(*it);
        if (token == ">>") {
          cur->setOutappend(true);
        }
      }
      execTokens = std::vector<std::string>();

    } else {

      execTokens.push_back(token);

    }
  }

  if (cur != NULL) {
    if (prev != NULL) {
      prev->setPipe(cur);
    } else {
      head = cur;
    }
    cur = NULL;
  }

  if (execTokens.size() > 0 && cur == NULL) {
    cur = new ExecutionStep(new Program(execTokens));
    if (prev != NULL) {
      prev->setPipe(cur);
    } else {
      head = cur;
    }
  }
  ret.push_back(head);

  return ret;
}
