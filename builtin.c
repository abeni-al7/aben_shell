#include "shell.h"

/**
 * check_exit - handles the exit builtin
 * @command: command entered
 * @buffer: input buffer
 * @stat: exit status
 */

void check_exit(char **command, char *buffer, int *stat)
{
	int status;
	char *exit_command = "exit";

	if (strcmp(command[0], exit_command) == 0)
	{
		if (command[1] == NULL)
		{
			free(buffer);
			free_arr(command);
			exit(*stat);
		}
		else
		{
			status = atoi(command[1]);
			free(buffer);
			free_arr(command);
			exit(status);
		}
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
