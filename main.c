#include "shell.h"

/**
 * main - entry point for the shell
 * @argc: argument count
 * @argv: array of arguments
 * Return: 0
 */

int main(int argc, char **argv)
{
	char *buffer = NULL, **args = NULL, *full_path = NULL;
	int interactive = isatty(fileno(stdin));
	int full_path_found = 0;

	while (1)
	{
		prompt(interactive);
		buffer = accept_command(argv[0]);
		if (check_env(buffer) == 0)
			continue;
		if (buffer[0] == '\0' || strlen(buffer) == 0)
		{
			free(buffer);
			continue;
		}
		args = tokenize(buffer, argv[0]);
		check_exit(args, buffer);
		full_path = Handle_path(args, buffer, argv[0]);
		if (full_path == NULL)
			continue;
		if (strcmp(args[0], full_path) != 0)
		{
			free(args[0]);
			args[0] = strdup(full_path);
			printf("After copying: %s\n", args[0]);
			execute_command(args, buffer, full_path, argv[0]);
		}
		else
			execute_command(args, buffer, NULL, argv[0]);
	}
	return (0);
}
