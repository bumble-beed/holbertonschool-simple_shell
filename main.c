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

	(void)ac;

	while (1)
	{
		/* 1. Display prompt if in interactive mode */
		if (isatty(STDIN_FILENO))
			printf("($) ");

		/* 2. Read the user input */
		nread = getline(&line, &len, stdin);

		/* Handle Ctrl+D (End of File) */
		if (nread == -1)
		{
			if (isatty(STDIN_FILENO))
				printf("\n");
			free(line);
			exit(0);
		}

		/* 3. Remove the newline character added by Enter */
		if (line[nread - 1] == '\n')
			line[nread - 1] = '\0';

			{
            int j = 0;
            while (line[j] != '\0')
                j++;
            j--; /* Go to the last character before the null terminator */
            while (j >= 0 && line[j] == ' ')
            {
                line[j] = '\0';
                j--;
            }
        }

        /* Skip leading spaces */
        {
            char *start = line;
            while (*start == ' ')
                start++;
            argv[0] = start;
        }

		/* 4. Create a clone (The Fork) */
		child_pid = fork();
		if (child_pid == -1)
		{
			perror("Error");
			free(line);
			return (1);
		}

		if (child_pid == 0) /* The Clone Universe */
		{
			argv[0] = line;
			if (execve(argv[0], argv, env) == -1)
			{
				/* Print error using the program name (av[0]) */
				perror(av[0]);
				free(line);
				exit(1);
			}
		}
		else /* The Parent Universe */
		{
			/* Wait for the child process to finish its task */
			wait(NULL);
		}
	}
	free(line);
	return (0);
}
