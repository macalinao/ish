#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sysexits.h>
#include <unistd.h>

#include "command.h"
#include "program.h"

Command::Command(std::string str) {
  this->str = str;
}

void Command::execute() {
  const char* cmd = this->str.c_str();
  pid_t pid;
  if ((pid = fork()) == -1) {
    fprintf(stderr, "shell: can't fork: %s\n", strerror(errno));
    return;
  }

  if (pid == 0) {
    Program program(cmd);
    const char* executable = program.getExecutable().c_str();
    char** argv = program.argv();
    execvp(executable, argv);
    delete argv;
    fprintf(stderr, "shell: couldn't exec %s: %s\n", cmd, strerror(errno));
    exit(EX_DATAERR);
  }

  int status;
  if ((pid = waitpid(pid, &status, 0)) < 0) {
    fprintf(stderr, "shell: waitpid error: %s\n", strerror(errno));
  }
}
