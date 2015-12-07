#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sysexits.h>
#include <unistd.h>

char* getinput(char *buffer, size_t buflen) {
  printf("$ ");
  return fgets(buffer, buflen, stdin);
}

void run_cmd(char* cmd) {
  pid_t pid;
  if ((pid = fork()) == -1) {
    fprintf(stderr, "shell: can't fork: %s\n", strerror(errno));
    return;
  }

  if (pid == 0) {
    execlp(cmd, cmd, (char*) 0);
    fprintf(stderr, "shell: couldn't exec %s: %s\n", cmd, strerror(errno));
    exit(EX_DATAERR);
  }

  int status;
  if ((pid = waitpid(pid, &status, 0)) < 0) {
    fprintf(stderr, "shell: waitpid error: %s\n", strerror(errno));
  }
}

int main(int argc, char **argv) {
  char buf[1024];

  while (getinput(buf, sizeof(buf))) {
    buf[strlen(buf) - 1] = '\0';
    run_cmd(buf);
  }

  exit(EX_OK);
}
