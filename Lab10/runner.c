#include <unistd.h>
#include <stdio.h>

int main(){
  printf("My pid is %d, parent pid is %d.\n", getpid(), getppid());
}