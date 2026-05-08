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
	char *argv[MAX_ARGS];
	char *start;
	char *path;
	int status;
	int last_status = 0;
	int j;
	int i;

	(void)ac;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			print_prompt();
		/*waits for user to type something in and hit enter*/
		nread = getline(&line, &len, stdin);
		if (nread == -1)
		{
			if (isatty(STDIN_FILENO))
				printf("\n");
			free(line);
			exit(last_status);
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
		i = 0;
		argv[i] = strtok(start, " ");
		while (argv[i] != NULL)
		{
			i++;
			argv[i] = strtok(NULL, " ");
		}
		if (handle_builtin(argv, line, last_status))
			continue;
		path = find_path(argv[0]);
                if (path == NULL)
		{
		       	/* command not found — print error, exit child */
			fprintf(stderr,"%s: 1: %s: not found\n", av[0], argv[0]);
			last_status = 127;
			continue;
		}
		child_pid = fork();
		if (child_pid == -1)
		{
			perror("Error");
			free(line);
			return (1);
		}

		if (child_pid == 0)
		{
			execve(path, argv, env);
			perror(av[0]);
			free(path);
			free(line);
			exit(1);
		}
		else
		{
			wait(&status);
			if (WIFEXITED(status))
				last_status = WEXITSTATUS(status);
			if (path != argv[0])
				free(path);
		}
	}
	free(line);
	return (last_status);
}
