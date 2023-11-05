#include "shell.h"

/**
 * error - handle errors
 * @message: the error message
 */

void error(char *message)
{
	perror(message);
	exit(EXIT_FAILURE);
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
 * @buffer: buffer to store the string in
 * @n: address of size of buffer after accepting input
 * @name: name of program
 * Return: 0 or -1
 */

void accept_command(char **buffer, size_t *n, char *name)
{
	if (getline(buffer, n, stdin) == -1)
	{
		if (feof(stdin))
		{
			free(*buffer);
			exit(EXIT_SUCCESS);
		}
		else
		{
			free(*buffer);
			error(name);
		}
	}
}

/**
 * execute_command - executes the command
 * @args: arguments of the progrm
 * @name: name of the program
 */

void execute_command(char **args, char *name)
{
	execve(args[0], args, NULL);
	error(name);
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
