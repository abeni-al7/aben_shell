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
char *accept_command(char *name);
void execute_command(char **args, char *buffer, char *full_path, char *name);
void prompt(int interactive);
char *Handle_path(char *exec, char *name);
void check_exit(char *command);
int check_env(char *command);

#endif
