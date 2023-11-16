#include "shell.h"

/**
 * tokenize_path - tokenize the path dirs
 * @path: path variable
 * @name: name of program
 * Return: array of directories in path
 */

char **tokenize_path(char *path, char *name)
{
	int i = 0;
	char **dirs = NULL;
	char delim[] = ":";
	char *token;

	dirs = malloc(64 * sizeof(char *));
	if (dirs == NULL)
		error(name, 0, NULL, NULL);
	token = strtok(path, delim);
	while (token != NULL)
	{
		dirs[i] = strdup(token);
		token = strtok(NULL, delim);
		i++;
	}
	dirs[i] = NULL;

	return (dirs);
}

/**
 * parse_path - parses the path variable
 * @name: name of the program
 * Return: an array containing the directories in path
 */

char **parse_path(char *name)
{
	char *path = NULL;
	char *path_copy;
	char **dirs;

	path = getenv("PATH");
	path_copy = strdup(path);
	dirs = tokenize_path(path_copy, name);
	free(path_copy);

	return (dirs);
}

/**
 * Handle_path - handles path
 * @args: executable array
 * @buffer: input command
 * @name: name of program
 * @line: line number of command
 * Return: the full path of the executable
 */

char *Handle_path(char **args, char *buffer, char *name, int line)
{
	int i;
	char *slash = "/", **folders = parse_path(name), *full_path = NULL;

	if (check_executable(args[0]) == 0)
	{
		free_arr(folders);
		return (args[0]);
	}
	i = 0;
	while (folders[i] != NULL)
	{
		full_path = malloc(strlen(folders[i]) + strlen(args[0]) + 2);
		if (full_path == NULL)
		{
			perror(name);
			free_arr(folders);
			return (NULL);
		}
		strcpy(full_path, folders[i]);
		strcat(full_path, slash);
		strcat(full_path, args[0]);
		if (check_executable(full_path) == 0)
		{
			free_arr(folders);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	if (folders != NULL)
		free_arr(folders);
	free_arr(args);
	error(name, line, buffer, "not found");
	free(buffer);
	return (NULL);
}

/**
 * check_executable - checks if a path is executable
 * @path: path to the file
 * Return: 0 or 1
 */

int check_executable(char *path)
{
	if (access(path, X_OK) == 0)
	{
		struct stat st;

		if (stat(path, &st) == 0)
		{
			if (S_ISREG(st.st_mode))
				return (0);
		}
	}

	return (1);
}
