#include "shell.h"

/**
 * err - handles errors
 * @dir: path
 * @non: error path
 * @message: error message
 */

void err(char *dir, char *non, char *message)
{
	dprintf(2, "%s: cannot access '%s': %s\n", dir, non, message);
	exit(2);
}
