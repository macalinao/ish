#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sysexits.h>
#include <unistd.h>

#include "command.h"

char* getinput(char *buffer, size_t buflen) {
  printf("$ ");
  return fgets(buffer, buflen, stdin);
}

int main() {
  char buf[1024];

  while (getinput(buf, sizeof(buf))) {
    buf[strlen(buf) - 1] = '\0';
    Command cmd(buf);
    cmd.execute();
  }

  exit(EX_OK);
}
