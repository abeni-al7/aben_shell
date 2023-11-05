#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

extern char **environ;

void error(char *message);
void remove_newline(char *str);
char **tokenize(char *str, char *name);
void free_arr(char **arr);
void accept_command(char **buffer, size_t *n, char *name);
void execute_command(char **args, char *name);
void prompt(int interactive);
char *Handle_path(char *exec, char *name);

#endif
