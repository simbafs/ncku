#include "../include/command.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Read the user's input string
 *
 * @return char*
 * Return string
 */
char *read_line() {
  char *buffer = (char *)malloc(BUF_SIZE * sizeof(char));
  if (buffer == NULL) {
    perror("Unable to allocate buffer");
    exit(1);
  }

  if (fgets(buffer, BUF_SIZE, stdin) != NULL) {
    if (buffer[0] == '\n' || buffer[0] == ' ' || buffer[0] == '\t') {
      free(buffer);
      buffer = NULL;
    } else {
      buffer[strcspn(buffer, "\n")] = 0;
      strncpy(history[history_count % MAX_RECORD_NUM], buffer, BUF_SIZE);
      ++history_count;
    }
  }

  return buffer;
}

/**
 * @brief Parse the user's command
 *
 * @param line User input command
 * @return struct cmd*
 * Return the parsed cmd structure
 */
struct cmd *split_line(char *line) {
  int args_length = 10;
  struct cmd *new_cmd = (struct cmd *)malloc(sizeof(struct cmd));
  new_cmd->head = (struct cmd_node *)malloc(sizeof(struct cmd_node));
  new_cmd->head->args = (char **)malloc(args_length * sizeof(char *));
  for (int i = 0; i < args_length; ++i) {
    new_cmd->head->args[i] = NULL;
  }
  new_cmd->head->length = 0;
  new_cmd->head->next = NULL;
  new_cmd->pipe_num = 0;

  struct cmd_node *temp = new_cmd->head;
  temp->in_file = NULL;
  temp->out_file = NULL;
  temp->in = 0;
  temp->out = 1;
  char *token = strtok(line, " ");
  while (token != NULL) {
    switch (token[0]) {
    case '|':;
      struct cmd_node *new_pipe =
          (struct cmd_node *)malloc(sizeof(struct cmd_node));
      new_pipe->args = (char **)malloc(args_length * sizeof(char *));
      for (int i = 0; i < args_length; ++i)
        new_pipe->args[i] = NULL;
      new_pipe->length = 0;
      new_pipe->next = NULL;
      temp->next = new_pipe;
      temp = new_pipe;
      break;

    case '<':
      token = strtok(NULL, " ");
      temp->in_file = token;
      break;

    case '>':
      token = strtok(NULL, " ");
      temp->out_file = token;
      break;

    default:
      temp->args[temp->length] = token;
      temp->length++;
    }

    token = strtok(NULL, " ");
    new_cmd->pipe_num++;
  }

  return new_cmd;
}
/**
 * @brief Information used to test the cmd structure
 *
 * @param cmd Command structure
 */
void test_cmd_struct(FILE *f, struct cmd *cmd) {
  struct cmd_node *temp = cmd->head;
  int pipe_count = 0;
  fprintf(f, "============ COMMAND INFO ============\n");
  fflush(f);
  while (temp != NULL) {
    fprintf(f, "cmd_node %d: ", pipe_count);
    fflush(f);
    for (int i = 0; i < temp->length; ++i) {
      fprintf(f, "%s ", temp->args[i]);
      fflush(f);
    }
    fprintf(f, "\n");
    fflush(f);
    temp = temp->next;
    ++pipe_count;
  }
  fprintf(f, "============ COMMAND INFO END ============\n");
  fflush(f);
}

/**
 * @brief Information used to test the cmd_node structure
 *
 * @param temp cmd_node structure
 */
void test_pipe_struct(FILE *f, struct cmd_node *temp) {
  fprintf(f, "============ CMD_NODE INFO ============\n");
  fflush(f);

  for (int i = 0; i < temp->length; ++i) {
    fprintf(f, "temp->args[%d] :%s \n", i, temp->args[i]);
    fflush(f);
  }
  fprintf(f, " in-file: %s\n", temp->in_file ? temp->in_file : "none");
  fflush(f);
  fprintf(f, "out-file: %s\n", temp->out_file ? temp->out_file : "none");
  fflush(f);
  fprintf(f, " in: %d\n", temp->in);
  fflush(f);
  fprintf(f, "out: %d\n", temp->out);
  fflush(f);
  fprintf(f, "============ CMD_NODE END ============\n");
  fflush(f);
}

void print_cmd(FILE *f, struct cmd_node *cmd) {
  fprintf(f, "cmd_node: ");
  for (int i = 0; i < cmd->length; ++i) {
    fprintf(f, "%s ", cmd->args[i]);
  }
  fprintf(f, " in file: %s, out file: %s, in: %d, out: %d\n", cmd->in_file,
          cmd->out_file, cmd->in, cmd->out);

  fflush(f);
}

void print_cmds(FILE *f, struct cmd *cmd) {
  struct cmd_node *curr = cmd->head;
  while (curr != NULL) {
    print_cmd(f, curr);

    curr = curr->next;
  }
}
