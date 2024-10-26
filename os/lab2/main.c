#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define EOC (char *)0 // End Of Command

int spawn(int argc, char *argv[], int in, int out) {
  pid_t pid = fork();
  if (pid < 0) {
    perror("fork");
    return -1;
  }

  if (pid == 0) {
    if (in != STDIN_FILENO) {
      dup2(in, STDIN_FILENO);
      close(in);
    }

    if (out != STDOUT_FILENO) {
      dup2(out, STDOUT_FILENO);
      close(out);
    }

    execvp(argv[0], argv);

    perror("execvp");
    exit(EXIT_FAILURE);
  }

  return pid;
}

int main() {
  char *cmd[] = {"cat", EOC};

  int out = dup(STDOUT_FILENO);

  int fd[2];
  pipe(fd);

  pid_t pid = spawn(1, cmd, fd[0], STDOUT_FILENO);

  write(fd[1], "hello", 5);
  write(fd[1], " world\n", 7);

  close(fd[1]);
  close(fd[0]);

  if (waitpid(pid, NULL, 0) == -1) {
    perror("waitpid");
  }
  printf("waitpid pid2\n");

  dup2(out, STDOUT_FILENO);

  return 0;
}
