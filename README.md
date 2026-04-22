### Description 
This project is a group project done for Holberton School to build a simple UNIX command interpreter

### Requirements
- Allowed editors: vi, vim, emacs
- All your files should end with a new line
- A README.md file, at the root of the folder of the project is mandatory
- Code must follow Betty style. 
- No memory leaks
- No more than 5 functions per file
- All your header files should be include guarded
- System calls only when needed

### How to compile
Compiled on Ubuntu 20.04 LTS with gcc using `-Wall -Werror -Wextra -pedantic -std=gnu89`

### Functions and use cases
==shell.c==
- `print_prompt` — prints `($)`  to the terminal so the user knows to type
- `trim_line` — cleans up the input by removing leading and trailing spaces and the newline at the end
- `split_line` — splits the cleaned input into an array of words using strtok e.g. "ls /var" becomes ["ls", "/var", NULL]
- `print_error` — prints an error message in the correct format using the program name and line number e.g. ./hsh: 1: ls: not found

path.c
get_env — searches through environ to find a variable and return its value e.g. get_env("PATH") returns the PATH string
find_path — uses get_env to get PATH, splits it by :, checks each directory for the command, returns the full path if found

builtins.c

handle_builtin — checks if the command is a builtin like exit or env and handles it without forking

main.c

execute_command — handles the fork, calls find_path to get the full path, runs execve in the child, waits in the parent

##### List of allowed functions and system calls+
| Function | Manual |
| -------- | ------ |
| All functions from string.h | - |
| `access` | man 2 access |
| `chdir` | man 2 chdir |
| `close` | man 2 close |
| `closedir` | man 3 closedir |
| `execve` | man 2 execve |
| `exit` | man 3 exit |
| `_exit` | man 2 _exit |
| `fflush` | man 3 fflush |
| `fork` | man 2 fork |
| `free` | man 3 free |
| `getcwd` | man 3 getcwd |
| `getline` | man 3 getline |
| `getpid` | man 2 getpid |
| `isatty` | man 3 isatty |
| `kill` | man 2 kill |
| `malloc` | man 3 malloc |
| `open` | man 2 open |
| `opendir` | man 3 opendir |
| `perror` | man 3 perror |
| `printf` | man 3 printf |
| `fprintf` | man 3 fprintf |
| `vfprintf` | man 3 vfprintf |
| `sprintf` | man 3 sprintf |
| `putchar` | man 3 putchar |
| `read` | man 2 read |
| `readdir` | man 3 readdir |
| `signal` | man 2 signal |
| `stat (__xstat)` | man 2 stat |
| `lstat (__lxstat)` | man 2 lstat |
| `fstat (__fxstat)` | man 2 fstat |
| `strtok` | man 3 strtok |
| `wait` | man 2 wait |
| `waitpid` | man 2 waitpid |
| `wait3` | man 2 wait3 |
| `wait4` | man 2 wait4 |
| `write` | man 2 write |

### Authors 
- Shirleen Asre - https://github.com/bumble-beed
- Sean Sabino - https://github.com/SSabin0 
