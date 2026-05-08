int handle_builtin(char **argv, char *line, int last_status);

if (strcmp(argv[0], "exit") == 0)
{
    free(line);
    exit(last_status);
}
return (0);
