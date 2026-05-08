#include "main.h"

/**
 * handle_builtin - checks and handles builtin commands
 * @argv: argument array
 * @line: input line buffer to free if exiting
 * @last_status: last exit status
 *
 * Return: 1 if builtin was handled, 0 if not
 */
int handle_builtin(char **argv, char *line, int last_status);
{
	if (strcmp(argv[0], "exit") == 0)
	{
		free(line);
		exit(last_status);
	}
	return (0);
}
