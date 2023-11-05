#include "shell.h"

/**
 * remove_newline - removes newline
 * @str: string to modify
 */

void remove_newline(char *str)
{
	int len = strlen(str);

	if (len > 0 && str[len - 1] == '\n')
		str[len - 1] = '\0';
}

/**
 * tokenize - tokenizes a string
 * @str: string to tokenize
 * @name: name of program
 * Return: array of tokenized parts from str
 */

char **tokenize(char *str, char *name)
{
	int i = 0;
	char **args = NULL;
	char *token;
	char delim[] = " \t\n:";

	args = malloc(50 * sizeof(char *));
	if (args == NULL)
	{
		error(name);
	}
	token = strtok(str, delim);
	while (token != NULL)
	{
		args[i] = malloc((strlen(token) + 1) * sizeof(char));
		if (args[i] == NULL)
		{
			free_arr(args);
			error(name);
		}
		strcpy(args[i], token);
		token = strtok(NULL, delim);
		i++;
	}
	args[i] = NULL;

	return (args);
}
