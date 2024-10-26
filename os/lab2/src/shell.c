#include "../include/builtin.h"
#include "../include/command.h"
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

FILE *flog;

void redirection(struct cmd_node *p) {
  if (p->in_file) {
    fprintf(flog, "Redirect stdin to %s\n", p->in_file);
    fflush(flog);

    int fd = open(p->in_file, O_RDONLY);
    if (fd == -1) {
      perror("open");
    }
    fprintf(flog, "fd = %d\n", fd);
    fflush(flog);
    if (dup2(fd, STDIN_FILENO) == -1) {
      perror("dup2(fd, stdout) failed");
    }
    close(fd);
  } else if (p->in != STDIN_FILENO) {
    fprintf(flog, "p->in = %d\n", p->in);
    fflush(flog);

    dup2(p->in, STDIN_FILENO);
    close(p->in);
  }

  if (p->out_file) {
    fprintf(flog, "Redirect stdout to %s\n", p->out_file);
    fflush(flog);

    int fd = open(p->out_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
      perror("open");
    }
    if (dup2(fd, STDOUT_FILENO) == -1) {
      perror("dup2(fd, stdout) failed");
    }
    close(fd);
  } else if (p->out != STDOUT_FILENO) {
    fprintf(flog, "p->out = %d\n", p->out);
    fflush(flog);

    dup2(p->out, STDOUT_FILENO);
    close(p->out);
  }
}

int spawn_proc(struct cmd_node *p) {
  pid_t pid = fork();

  if (pid == 0) {
    redirection(p);
    fprintf(flog, "execvp: %s\n", p->args[0]);
    if (execvp(p->args[0], p->args) == -1) {
      perror("execvp failed");
      exit(EXIT_FAILURE);
    }
    return 0;
  }

  fprintf(flog, "spawn_proc: pid = %d\n", pid);

  return pid;
}
// ===============================================================

// ======================= requirement 2.4 =======================
/**
 * @brief
 * Use "pipe()" to create a communication bridge between processes
 * Call "spawn_proc()" in order according to the number of cmd_node
 * @param cmd Command structure
 * @return int
 * Return execution status
 */
// TODO:
int fork_cmd_node(struct cmd *cmd) {
  int fd[cmd->pipe_num][2];
  int pid[cmd->pipe_num + 1];

  // open pipes
  for (int i = 0; i < cmd->pipe_num; i++) {
    if (pipe(fd[i]) == -1) {
      perror("pipe");
      return -1;
    }
  }

  // others
  int n = 0;
  struct cmd_node *curr;
  for (curr = cmd->head; curr; curr = curr->next) {
    curr->in = n == 0 ? STDIN_FILENO : fd[n - 1][0];
    curr->out = curr->next == NULL ? STDOUT_FILENO : fd[n][1];
    pid[n] = spawn_proc(curr);

    fprintf(flog, "exec pid = %d ", pid[n]);
    print_cmd(flog, curr);

    if (n > 0) {
      close(fd[n - 1][0]);

      fprintf(flog, "%d not first command\n", n);
      fflush(flog);
    }
    if (curr->next != NULL) {
      close(fd[n][1]);

      fprintf(flog, "%d not last command\n", n);
      fflush(flog);
    }

    n++;
  }

  fprintf(flog, "n = %d\n", n);
  fflush(flog);

  // wait for all children
  for (int i = 0; i < n; i++) {
    if (waitpid(pid[i], NULL, 0) == -1) {
      perror("waitpid failed");
      printf("pid[%d] = %d\n", i, pid[i]);
      return -1;
    }
  }

  // close pipes
  for (int i = 0; i < n; i++) {
    close(fd[i][0]);
    close(fd[i][1]);
  }

  /* fflush(stdout); */

  return 1;
}
// ===============================================================

void shell() {
  int fd = open("log.txt", O_APPEND | O_CREAT | O_WRONLY, 0644);
  flog = fdopen(fd, "w");
  fprintf(flog, "Shell Start\n");
  fflush(flog);

  while (1) {
    printf(">>> $ ");
    char *buffer = read_line();
    if (buffer == NULL) {
      continue;
    }

    struct cmd *cmd = split_line(buffer);

    fprintf(flog, "cmd->pipe_num = %d\n", cmd->pipe_num);

    int status = -1;
    struct cmd_node *temp = cmd->head;

    print_cmds(flog, cmd);

    // int and out is the backup of stdio to recover them
    int in = dup(STDIN_FILENO);
    int out = dup(STDOUT_FILENO);
    if ((in == -1) | (out == -1)) {
      perror("dup");
    }

    if (temp->next == NULL) {
      // only a single command
      status = searchBuiltInCommand(temp);
      if (status != -1) {
        fprintf(flog, "internal command: %s\n", temp->args[0]);
        fflush(flog);

        redirection(temp);
        status = execBuiltInCommand(status, temp);
      } else {
        // external command
        fprintf(flog, "external command: %s\n", temp->args[0]);
        fflush(flog);

        int pid = spawn_proc(cmd->head);
        if (pid == -1) {
          fprintf(flog, "Failed to fork\n");
          fflush(flog);
          exit(1);
        }

        if (waitpid(pid, &status, 0) == -1) {
          perror("waitpid failed");
          exit(1);
        }

        if (status == 0) {
          status = 1;
        }
      }
    } else {
      status = fork_cmd_node(cmd);
    }

    // recover shell stdin and stdout
    if (temp->in_file)
      dup2(in, STDIN_FILENO);
    if (temp->out_file) {
      dup2(out, STDOUT_FILENO);
    }

    close(in);
    close(out);

    // free space
    while (cmd->head) {
      struct cmd_node *temp = cmd->head;
      cmd->head = cmd->head->next;
      free(temp->args);
      free(temp);
    }
    free(cmd);
    free(buffer);

    if (status == 0) {
      break;
    }

    fprintf(flog, "\n");
    fflush(flog);
  }

  fprintf(flog, "-------\n");
  fflush(flog);

  fclose(flog);
}
