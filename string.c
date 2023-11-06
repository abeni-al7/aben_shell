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
	char delim[] = " \t\n\r:";

	args = malloc(64 * sizeof(char *));
	if (args == NULL)
	{
		error(name);
	}
	token = strtok(str, delim);
	while (token != NULL)
	{
		if (token[0] == '"' || token[0] == '\'')
			args[i] = strndup(token + 1, strlen(token) - 2);
		else
			args[i] = strdup(token);
		token = strtok(NULL, delim);
		i++;
	}
	args[i] = NULL;

	return (args);
}
