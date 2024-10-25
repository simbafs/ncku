#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define EOC (char *)0 // End Of Command

int main() {
  char *cmd[] = {"ls", "-la", "include", EOC};

  // rediect the stdout to output.txt
  freopen("output.txt", "r+", stdout);

  int ret = execvp("ls", cmd);
  if (ret == -1) {
    perror("execvp");
    return 1;
  }

  return 0;
}
