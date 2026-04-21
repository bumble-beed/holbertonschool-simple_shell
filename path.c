#include "main.h"

/**
 * get_env - look up a variable in environ
 * @name: variable name (without '=')
 *
 * Return: pointer to value inside environ (do not free), or NULL
 */
char *get_env(const char *name)
{
	size_t len;
	int i;

	if (name == NULL || environ == NULL)
		return (NULL);
	len = strlen(name);
	for (i = 0; environ[i] != NULL; i++)
	{
		if (strncmp(environ[i], name, len) == 0 && environ[i][len] == '=')
			return (environ[i] + len + 1);
	}
	return (NULL);
}

/**
 * find_path - resolve a command using $PATH
 * @cmd: command name (no '/' means search PATH; with '/' return as-is if X_OK)
 *
 * Return: malloc'd path that is executable, or NULL if not found.
 *         Caller must free unless cmd already contained '/'.
 */
char *find_path(char *cmd)
{
	char *path_env, *copy, *dir, *full;
	size_t dlen, clen;

	if (cmd == NULL || *cmd == '\0')
		return (NULL);
	if (strchr(cmd, '/') != NULL)
		return (access(cmd, X_OK) == 0 ? cmd : NULL);
	path_env = get_env("PATH");
	if (path_env == NULL || *path_env == '\0')
		return (NULL);
	copy = strdup(path_env);
	if (copy == NULL)
		return (NULL);
	clen = strlen(cmd);
	dir = strtok(copy, ":");
	while (dir != NULL)
	{
		dlen = strlen(dir);
		full = malloc(dlen + clen + 2);
		if (full == NULL)
		{
			free(copy);
			return (NULL);
		}
		sprintf(full, "%s/%s", dir, cmd);
		if (access(full, X_OK) == 0)
		{
			free(copy);
			return (full);
		}
		free(full);
		dir = strtok(NULL, ":");
	}
	free(copy);
	return (NULL);
}
