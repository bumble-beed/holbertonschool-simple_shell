# Simple Shell

## Description

A simple UNIX command line interpreter built as a project for Holberton School.
The shell supports the following features:

* Displays a prompt and waits for the user to enter a command
* Executes commands with arguments
* Searches the PATH to locate executables
* Handles errors and prints informative messages when a command is not found
* Handles end of file (Ctrl + D) to exit cleanly
* Works in both interactive and non-interactive mode

Written by Shirleen Asre and Sean Sabino

---

## Compilation

```
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```

---

## Requirements

* Allowed editors: vi, vim, emacs
* Compiled on Ubuntu 20.04 LTS using gcc with `-Wall -Werror -Wextra -pedantic -std=gnu89`
* All files end with a new line
* Code follows the Betty style
* No memory leaks
* No more than 5 functions per file
* All header files are include guarded
* System calls are only used when necessary

---

## File Overview

### main.h

The header file included by every other file in the project. It holds all the standard library includes and function prototypes so each file knows what exists across the project.

It also declares:

```c
extern char **environ
```

which gives the program access to the environment variable list inherited from the parent process.

### main.c

The entry point of the shell. Contains `main()` and the core loop that keeps the shell running.

On each iteration it:
1. Prints the prompt if running interactively
2. Reads a line of input using `getline`
3. Strips the newline and cleans up any extra whitespace
4. Splits the input into tokens (command and arguments)
5. Forks a child process to run the command
6. Waits for the child to finish before looping back

If `getline` returns -1 (Ctrl + D), the shell exits cleanly.

### shell.c

Contains `print_prompt()`, which writes the shell prompt to the terminal:

```
($)
```

`fflush` is called immediately after to make sure the prompt appears before `getline` blocks waiting for input.

### path.c

Handles finding where a command lives on the system.

`get_env` loops through `environ` to find a variable by name and return its value. For example, calling `get_env("PATH")` returns something like:

```
/usr/local/sbin:/usr/local/bin:/usr/bin:/bin
```

`find_path` takes that PATH string, splits it on `:` to get individual directories, and checks each one for the command. It builds candidate paths like `/usr/bin/ls` and tests them until it finds one that is executable. If nothing is found, it returns NULL.

---

## How to Use

### Interactive mode

Run the shell:

```
./hsh
```

A prompt appears:

```
($)
```

From here, type any command:

```
($) ls -la
($) /bin/echo hello
```

Input is tokenised so `ls -la` becomes:

```
argv[0] = "ls"
argv[1] = "-la"
argv[2] = NULL
```

The shell forks a child and runs the command with `execve`. The parent waits with `wait` until the child finishes, then the prompt appears again.

### Non-interactive mode

Commands can be piped in:

```
echo "ls -l" | ./hsh
```

No prompt is printed in this mode.

### Exiting

Press **Ctrl + D** at the prompt to exit. The shell detects the end-of-file condition and exits with the status of the last command run.

---

## Authors

* Shirleen Asre — https://github.com/bumble-beed
* Sean Sabino — https://github.com/SSabin0