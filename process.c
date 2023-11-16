#include "shell.h"

/**
 * error - handle errors
 * @name: the name of the program
 * @line: line number
 * @command: the command with error
 * @message: error message
 * Return: error code
 */

int error(char *name, int line, char *command, char *message)
{
	dprintf(STDERR_FILENO, "%s: %d: %s: %s\n", name, line, command, message);
	return (127);
}

/**
 * free_arr - frees an array of strings
 * @arr: array of strings
 */

void free_arr(char **arr)
{
	int i = 0;

	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}

	free(arr);
}

/**
 * accept_command - acceps command from stdin
 * @name: name of program
 * @line: line number
 * Return: 0 or -1
 */

char *accept_command(char *name, int line)
{
	char *buffer = NULL;
	size_t n = 0;

	if (getline(&buffer, &n, stdin) == -1)
	{
		if (feof(stdin))
		{
			free(buffer);
			exit(EXIT_SUCCESS);
		}
		else
		{
			free(buffer);
			error(name, line, NULL, "can not accept");
		}
	}
	remove_newline(buffer);

	return (buffer);
}

/**
 * execute_command - executes the command
 * @args: arguments of the progrm
 * @buffer: input buffer
 * @full_path: path of the executable
 * @name: name of the program
 * @line: command number
 */

void execute(char **args, char *buffer, char *full_path, char *name, int line)
{
	pid_t pid;

	if (check_executable(args[0]) != 0)
	{
		if (args != NULL)
			free_arr(args);
		if (full_path != NULL)
			free(full_path);
		if (buffer != NULL)
			free(buffer);
		error(name, line, args[0], "not found");
		return;
	}
		
	pid = fork();
	if (pid == -1)
	{
		free(buffer);
		if (full_path != NULL)
			free(full_path);
		free_arr(args);
		error(name, 0, NULL, "can not create process");
	}
	if (pid == 0)
	{
		execve(args[0], args, environ);
	}
	else
	{
		wait(NULL);
		if (args != NULL)
			free_arr(args);
		if (full_path != NULL)
			free(full_path);
		if (buffer != NULL)
			free(buffer);
	}
}

/**
 * prompt - prints prompt
 * @interactive: checks for interactive mode
 */

void prompt(int interactive)
{
	if (interactive)
	{
		printf("$ ");
		fflush(stdout);
	}
}
