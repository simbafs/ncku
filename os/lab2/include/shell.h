#ifndef SHELL_H
#define SHELL_H

#include "command.h"

int spawn_proc(struct cmd_node *p);
int fork_cmd_node(struct cmd *cmd);
void redirection(struct cmd_node *p);
void shell();

#endif
