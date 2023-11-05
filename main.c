#include "shell.h"

/**
 * main - entry point for the shell
 * @argc: argument count
 * @argv: array of arguments
 * Return: 0
 */

int main(int argc, char **argv)
{
	char *buffer = NULL, **args = NULL;
	size_t n = 0;
	pid_t pid;
	int interactive = isatty(fileno(stdin));

	while (1)
	{
		prompt(interactive);
		accept_command(&buffer, &n, argv[0]);
		remove_newline(buffer);
		if (buffer[0] == '\0')
			continue;
		args = tokenize(buffer, argv[0]);
		args[0] = Handle_path(args[0], argv[0]);
		if (args[0] == NULL)
		{
			free(buffer);
			free_arr(args);
			error(argv[0]);
		}
		pid = fork();
		if (pid == -1)
		{
			free(buffer);
			free_arr(args);
			error(argv[0]);
		}
		if (pid == 0)
		{
			execute_command(args, argv[0]);
		}
		else
		{
			wait(NULL);
			if (args != NULL)
				free_arr(args);
		}
	}

	free(buffer);
	return (0);
}
