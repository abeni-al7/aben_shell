#include "shell.h"

/**
 * check_exit - handles the exit builtin
 * @command: command entered
 */

void check_exit(char *command)
{
	char *exit_command = "exit";

	if (strcmp(command, exit_command) == 0)
	{
		free(command);
		exit(EXIT_SUCCESS);
	}
}

/**
 * check_env - handles the env builtin
 * @command: command entered
 * Return: 0 or 1
 */

int check_env(char *command)
{
	int i = 0;
	char *env = "env";

	if (strcmp(command, env) == 0)
	{
		while (environ[i] != NULL)
		{
			printf("%s\n", environ[i]);
			i++;
		}
		free(command);
		return (0);
	}
	return (1);
}
