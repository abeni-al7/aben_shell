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
	pid_t pid;
	int interactive = isatty(fileno(stdin));

	while (1)
	{
		prompt(interactive);
		buffer = accept_command(argv[0]);
		check_exit(buffer);
		if (check_env(buffer) == 0)
			continue;
		if (buffer[0] == '\0' || strlen(buffer) == 0)
			continue;
		args = tokenize(buffer, argv[0]);
		printf("Before handling path: %s\n", args[0]);
		full_path = Handle_path(args[0], argv[0]);
		printf("After Handling path: %s\n", full_path);
		if (full_path == NULL)
		{
			free(buffer);
			perror(argv[0]);
			continue;
		}
		if (strcmp(args[0], full_path) != 0)
		{
			free(args[0]);
			args[0] = strdup(full_path);
			printf("After copying: %s\n", args[0]);
		}
		execute_command(args, buffer, full_path, argv[0]);
	}

	free(buffer);
	return (0);
}
