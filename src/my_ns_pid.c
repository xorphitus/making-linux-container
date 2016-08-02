#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#define STACK_SIZE 1024*1024
static char child_stack[STACK_SIZE];

static int child_fn() {
  printf("child - self   pid: %ld\n", (long) getpid());
  printf("child - parent pid: %ld\n", (long) getppid());
  sleep(100);

  exit(0);
}

int main(int argc, char *argv[]) {
  int flags = SIGCHLD;
  int opt;
  while ((opt = getopt(argc, argv, "p")) != -1) {
    if (opt) {
      flags |= CLONE_NEWPID;
    } else {
      exit(1);
    }
  }

  pid_t child_pid = clone(child_fn, child_stack + STACK_SIZE, flags, NULL);
  printf("current - clone pid: %ld\n", (long) child_pid);
  printf("current - self  pid: %ld\n", (long) getpid());
  waitpid(child_pid, NULL, 0);

  exit(0);
}
