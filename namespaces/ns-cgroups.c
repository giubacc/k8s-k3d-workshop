#define _GNU_SOURCE
#include <sched.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>

#define STACK_SIZE (1024 * 1024) // Stack size for cloned child

// Child function: runs in new namespaces
int child_main(void *arg)
{
  printf("Child [%d] in new UTS+PID+Mount namespace\n", getpid());

  // set hostname (isolated)
  sethostname("myccontainer", strlen("myccontainer"));

  // mount proc for PID namespace
  if (mount("proc", "/proc", "proc", 0, "") != 0)
  {
    perror("mount /proc failed");
  }

  // launch a shell inside
  char *const args[] = {"/bin/bash", NULL};
  execvp(args[0], args);
  perror("execvp");
  return 1;
}

// Helper: put pid into a cgroup
void add_to_cgroup(pid_t pid)
{
  const char *cgdir = "/sys/fs/cgroup/mydemo";
  char path[256];
  int fd;

  // Create cgroup directory (needs sudo, already mounted cgroup2)
  mkdir(cgdir, 0755);

  // Limit CPU: allow 20% usage
  snprintf(path, sizeof(path), "%s/cpu.max", cgdir);
  fd = open(path, O_WRONLY);
  if (fd >= 0)
  {
    write(fd, "20000 100000", strlen("20000 100000"));
    close(fd);
  }

  // Limit memory: 100 MB
  snprintf(path, sizeof(path), "%s/memory.max", cgdir);
  fd = open(path, O_WRONLY);
  if (fd >= 0)
  {
    write(fd, "104857600", strlen("104857600"));
    close(fd);
  }

  // Add process into cgroup
  snprintf(path, sizeof(path), "%s/cgroup.procs", cgdir);
  fd = open(path, O_WRONLY);
  if (fd >= 0)
  {
    char buf[32];
    snprintf(buf, sizeof(buf), "%d", pid);
    write(fd, buf, strlen(buf));
    close(fd);
  }
}

int main()
{
  char *stack; // Stack for child
  char *stackTop;
  pid_t pid;

  stack = malloc(STACK_SIZE);
  if (!stack)
  {
    perror("malloc");
    exit(1);
  }
  stackTop = stack + STACK_SIZE;

  // Create child in new UTS, PID, and Mount namespaces
  pid = clone(child_main, stackTop,
              CLONE_NEWUTS | CLONE_NEWPID | CLONE_NEWNS | SIGCHLD,
              NULL);
  if (pid == -1)
  {
    perror("clone");
    exit(1);
  }

  printf("Parent: child pid = %d\n", pid);

  // Put child into cgroup
  add_to_cgroup(pid);

  // Wait for child to exit
  waitpid(pid, NULL, 0);
  free(stack);
  return 0;
}
