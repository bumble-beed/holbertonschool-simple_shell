#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

extern char **environ;
/**
 * environ - Pointer to an array of strings that constitute the environment
 *
 * Description: Inherited from the parent process; used to access
 * system variables and passed to execve when launching new programs.
 */
 
void print_prompt(void);

#endif