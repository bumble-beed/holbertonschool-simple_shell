
## Description

A simple UNIX command line interpreter built as a project for Holberton School.
The shell currently supports:

* Displaying a prompt and waiting for the user to enter a command
* Executing commands passed as a direct path (e.g. `/bin/ls`)
* Executing commands with arguments
* Handling errors when a command cannot be run
* Handling end of file (Ctrl + D) to exit cleanly
* Running in both interactive and non-interactive mode

---

## Compilation

```
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 main.c shell.c -o hsh
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

## Progress on the project tasks
  
  | Task | Requirement | Status | Notes |
  |---|---|---|---|
  | 0. README / man / AUTHORS | All three files at root | Done | `README.md`, `man_1_simple_shell`, `AUTHORS` present |
  | 0.1 Simple shell 0.1 | Prompt, single-word command, EOF, errors | Done | Works in interactive and non-interactive mode |
  | 0.2 Simple shell 0.2 | Handle command arguments | Done | Tokenised with `strtok` inside `main.c` |
  | 0.3 Simple shell 0.3 | Use PATH; do not fork if command not found | Partial | `find_path()` exists in `path.c` but `main.c` still calls `execve(argv[0], …)` directly and forks every time |
  | 0.4 Simple shell 0.4 | `exit` built-in | Not done |  |
  | 1.0 Simple shell 1.0 | `env` built-in | Partial | Set up but not connected |
  | Error format | `./hsh: 1: cmd: not found` (argv[0] + line number) | Not done |  |

## File Overview

### main.h

The header file included by every other file in the project. Holds all standard library includes and function prototypes so that each file knows what exists across the codebase.

Also declares:

```c
extern char **environ
```

which gives the program access to the environment variable list inherited from the parent process.

### main.c

The entry point and core of the shell. Contains `main()` and the loop that keeps it running.

On each iteration:
1. Prints the prompt if running interactively
2. Reads a line of input with `getline`
3. Strips the trailing newline and trims extra whitespace
4. Splits the input into an argument array using `strtok`
5. Forks a child process to run the command via `execve`
6. Waits for the child to finish before looping back

Commands must currently be given as a full path (e.g. `/bin/ls`). If `getline` returns -1, the shell exits cleanly.

### shell.c

Contains `print_prompt()`, which prints the prompt:

```
($)
```

`fflush` is called straight after to ensure the prompt displays before the program pauses to wait for input.

### path.c

Contains two functions for resolving command paths, written in preparation for PATH handling:

`get_env` searches through `environ` to find a variable by name and return its value. For example:

```
get_env("PATH")
```

would return something like:

```
/usr/local/sbin:/usr/local/bin:/usr/bin:/bin
```

`find_path` uses `get_env` to retrieve the PATH string, splits it on `:`, and checks each directory for the command by building candidate paths and testing them with `access`. Returns the full executable path if found, or NULL if not.

These functions are not yet connected to the main execution flow.

---

## How to Use

### Interactive mode

Run the shell after compiling:

```
./hsh
```

The prompt will appear:

```
($)
```

Commands must currently be entered as a full path:

```
($) /bin/ls
($) /bin/echo hello
```

The input is tokenised, so `/bin/ls -la` becomes:

```
argv[0] = "/bin/ls"
argv[1] = "-la"
argv[2] = NULL
```

The shell forks a child and runs the command with `execve`. The parent waits using `wait` until the child exits, then the prompt appears again.

### Non-interactive mode

Commands can also be piped in:

```
echo "/bin/ls" | ./hsh
```

No prompt is printed in this mode.

### Exiting

Press **Ctrl + D** at the prompt. The shell catches the end-of-file signal from `getline` and exits.

---
<img width="800" height="1000" alt="simple_shell_workflow" src="https://github.com/user-attachments/assets/498aba43-2f0b-4b10-9c73-999a3b575c1f" /># Simple Shell

---

## Authors

* Shirleen Asre — https://github.com/bumble-beed
* Sean Sabino — https://github.com/SSabin0
