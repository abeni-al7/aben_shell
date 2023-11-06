#include "shell.h"

/**
 * Handle_path - handles path
 * @exec: executable name
 * @name: name of program
 * Return: the full path of the executable
 */

char *Handle_path(char *exec, char *name)
{
	int i = 0;
	char *slash = "/";
	char *path = getenv("PATH");
	char **folders = tokenize(path, NULL);
	char *full_path;

	if (access(exec, X_OK) == 0)
	{
		free_arr(folders);
		return (exec);
	}
	while (folders[i] != NULL)
	{
		full_path = malloc(strlen(folders[i]) + strlen(exec) + 2);
		strcpy(full_path, folders[i]);
		strcat(full_path, slash);
		strcat(full_path, exec);
		if (access(full_path, X_OK) == 0)
		{
			free_arr(folders);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_arr(folders);
	return (NULL);
}
