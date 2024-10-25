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

// ======================= requirement 2.3 =======================
/**
 * @brief
 * Redirect command's stdin and stdout to the specified file descriptor
 * If you want to implement ( < , > ), use "in_file" and "out_file" included the
 * cmd_node structure If you want to implement ( | ), use "in" and "out"
 * included the cmd_node structure.
 *
 * @param p cmd_node structure
 *
 */
// TODO:
void redirection(struct cmd_node *p) {}
// ===============================================================

// ======================= requirement 2.2 =======================
/**
 * @brief
 * Execute external command
 * The external command is mainly divided into the following two steps:
 * 1. Call "fork()" to create child process
 * 2. Call "execvp()" to execute the corresponding executable file
 * @param p cmd_node structure
 * @return int
 * Return execution status
 */
// TODO:
int spawn_proc(struct cmd_node *p) { return 1; }
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
int fork_cmd_node(struct cmd *cmd) { return 1; }
// ===============================================================

void shell() {
  while (1) {
    printf(">>> $ ");
    char *buffer = read_line();
    if (buffer == NULL) {
      continue;
    }

    struct cmd *cmd = split_line(buffer);

    int status = -1;
    struct cmd_node *temp = cmd->head;

    if (temp->next == NULL) {
      // only a single command
      status = searchBuiltInCommand(temp);
      if (status != -1) {
        int in = dup(STDIN_FILENO);
        int out = dup(STDOUT_FILENO);
        if (in == -1 | out == -1) {
          perror("dup");
        }
        redirection(temp);
        status = execBuiltInCommand(status, temp);

        // recover shell stdin and stdout
        if (temp->in_file)
          dup2(in, stdin);
        if (temp->out_file) {
          dup2(out, stdout);
        }

        close(in);
        close(out);
      } else {
        // external command
        status = spawn_proc(cmd->head);
      }
    } else {
      // There are multiple commands ( | )
      status = fork_cmd_node(cmd);
    }
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
  }
}