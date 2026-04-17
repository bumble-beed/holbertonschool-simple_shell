#include "main.h"

/**
 * main entry point
 *
 * while to create a loop 
 **/
int main(int ac, char **av, char **env)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	pid_t child_pid;
	char *argv[] = {NULL, NULL};
	char *start;
	int j;

	(void)ac;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			printf("($) ");

		nread = getline(&line, &len, stdin);
		if (nread == -1)
		{
			if (isatty(STDIN_FILENO))
				printf("\n");
			free(line);
			exit(0);
		}

		if (line[nread - 1] == '\n')
			line[nread - 1] = '\0';

		/* 1. Trim trailing spaces */
		j = 0;
		while (line[j] != '\0')
			j++;
		j--;
		while (j >= 0 && line[j] == ' ')
		{
			line[j] = '\0';
			j--;
		}

		/* 2. Skip leading spaces */
		start = line;
		while (*start == ' ')
			start++;

		/* If the line was only spaces, don't try to execute */
		if (*start == '\0')
			continue;

		child_pid = fork();
		if (child_pid == -1)
		{
			perror("Error");
			free(line);
			return (1);
		}

		if (child_pid == 0)
		{
			/* Use 'start' (the cleaned path), not 'line' */
			argv[0] = start;
			if (execve(argv[0], argv, env) == -1)
			{
				perror(av[0]);
				free(line);
				exit(1);
			}
		}
		else
		{
			wait(NULL);
		}
	}
	free(line);
	return (0);
}