#include "shell.h"

/**
 * _getline - read a line of input from a stream
 * @lineptr: buffer to store the line read
 * @n: size of the buffer
 * @stream: stream from which to read
 * Return: number of bytes read or -1
 */

ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	char *buffer = NULL, c;
	size_t bytes, i = 0;

	if (lineptr == NULL || n == NULL || stream == NULL)
		return (-1);
	bytes = *n;
	if ((*lineptr) == NULL || bytes == 0)
	{
		bytes = 120;
		(*lineptr) = malloc(sizeof(char) * bytes);
		if (lineptr == NULL)
			return (-1);
	}
	while ((c = fgetc(stream)) != EOF && c != '\n')
	{
		if (i == bytes - 1)
		{
			bytes *= 2;
			buffer = realloc((*lineptr), bytes);
			if (buffer == NULL)
			{
				free(*lineptr);
				*lineptr = NULL;
				return (-1);
			}
			*lineptr = buffer;
		}
		(*lineptr)[i++] = c;
	}
	if (i > 0 || c == '\n')
		(*lineptr)[i] = '\0';
	if (i > 0 || c == '\n' || c == EOF)
	{
		*n = bytes;
		return (i);
	}
	return (-1);
}

/**
 * _strtok - tokenizes a string based on dilimiters
 * @str: string to tokenize
 * @delimiters: a string of delimiter characters
 * Return: a pointer to the next token or NULL
 */

char *_strtok(char *str, const char *delimiters)
{
	static char *p;
	char *start = p;

	if (str != NULL)
		p = str;
	while (*p != '\0' && strchr(delimiters, *p) != NULL)
		p++;
	if (*p == '\0')
		return (NULL);
	start = p;
	while (*p != '\0')
	{
		if (strchr(delimiters, *p) != NULL)
		{
			*p = '\0';
			p++;
			return (start);
		}
		p++;
	}
	return (start);
}
