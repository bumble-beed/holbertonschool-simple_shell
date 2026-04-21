#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>
#include <errno.h>

#define MAX_ARGS 64

extern char **environ;

/* shell.c */
void print_prompt(void);
char *trim_line(char *line);
char **split_line(char *line, char **argv);
void print_error(char *prog, int line_no, char *cmd);

/* path.c */
char *get_env(const char *name);
char *find_path(char *cmd);

/* builtins.c */
int handle_builtin(char **argv, char *line, int last_status);

/* main.c */
int execute_command(char **argv, char *prog, int line_no);

#endif /* MAIN_H */