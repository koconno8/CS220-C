#include <stdio.h>
#include <unistd.h>

int main() {
  int x = 1;
  pid_t pid;
  pid = fork();

  if (pid == 0) {
    x++;
    printf("In child\n");
    printf("Child PID: %d\n", getpid());
    printf("Parent PID in child: %d\n", getppid());
    printf("Value of x in child: %d\n", x); // Added line to print value of x in child
  } else {
    x--;
    sleep(1);
    printf("In parent\n");
    printf("Parent PID: %d\n", getpid());
    printf("Parent PID in parent: %d\n", getppid());
    printf("Value of x in parent: %d\n", x); // Added line to print value of x in parent
  }
  return 0;
}
