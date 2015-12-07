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

int main(int argc, char **argv) {
  char buf[1024];
  pid_t pid;
  int status;

  while (getinput(buf, sizeof(buf))) {
    buf[strlen(buf) - 1] = '\0';

    if ((pid = fork()) == -1) {
      fprintf(stderr, "shell: can't fork: %s\n", strerror(errno));
      continue;
    } else if (pid == 0) {
      execlp(buf, buf, (char*) 0);
      fprintf(stderr, "shell: couldn't exec %s: %s\n", buf, strerror(errno));
      exit(EX_DATAERR);
    }

    if ((pid = waitpid(pid, &status, 0)) < 0) {
      fprintf(stderr, "shell: waitpid error: %s\n", strerror(errno));
    }
  }

  exit(EX_OK);

  return 0;
}
