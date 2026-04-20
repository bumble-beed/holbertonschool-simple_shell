#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_ARGS 64

extern char **environ;
/**
 * Description: Inherited from the parent process; used to access
 * system variables and passed to execve when launching new programs.
 */
 
void print_prompt(void);

#endif
