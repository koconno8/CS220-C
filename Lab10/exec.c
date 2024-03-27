#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int main()
{
  char *prog = "./runner";
  char * args[] = {NULL}; /* Null terminated list of arguments */
  if (fork() == 0) {
    printf("child pid = %d, parent pid = %d\n", getpid(), getppid());
    execvp(prog, args);
    fprintf(stderr, "exec: %s\n", strerror(errno));
  } else {
    wait(NULL);
  }
  return 0;
}
