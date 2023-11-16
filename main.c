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
	int interactive = isatty(fileno(stdin)), line = 0, err;

	(void)argc;
	while (1)
	{
		line++;
		prompt(interactive);
		buffer = accept_command(argv[0], line);
		if (strspn(buffer, "/"))
		{
			args = tokenize(buffer, argv[0]);
			execute(args, buffer, NULL, argv[0], line);
			err = 1;
			continue;
		}
		if (check_env(buffer) == 0)
			continue;
		if (buffer[0] == '\0' || strspn(buffer, " ") == strlen(buffer))
		{
			free(buffer);
			continue;
		}
		args = tokenize(buffer, argv[0]);
		check_exit(args, buffer, err);
		err = 0;
		full_path = Handle_path(args, buffer, argv[0], line);
		if (full_path == NULL)
			continue;
		if (strcmp(args[0], full_path) != 0)
		{
			free(args[0]);
			args[0] = strdup(full_path);
			execute(args, buffer, full_path, argv[0], line);
			err = 1;
		}
		else
			execute(args, buffer, NULL, argv[0], line);
			err = 1;
	}
	return (0);
}
