<img width="103" height="150" alt="simple_shell_workflow" src="https://github.com/user-attachments/assets/498aba43-2f0b-4b10-9c73-999a3b575c1f" /># Simple Shell

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

![Uploading simple_shell_workflow.svg…<svg width="100%" viewBox="0 0 680 994" role="img" style="" xmlns="http://www.w3.org/2000/svg">
  <title style="fill:rgb(0, 0, 0);stroke:none;color:rgb(255, 255, 255);stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:16px;font-weight:400;text-anchor:start;dominant-baseline:auto">Simple shell workflow diagram</title>
  <desc style="fill:rgb(0, 0, 0);stroke:none;color:rgb(255, 255, 255);stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:16px;font-weight:400;text-anchor:start;dominant-baseline:auto">End-to-end flow of the holbertonschool-simple_shell: from main loop through input, parsing, path resolution, and fork/exec.</desc>
  <defs>
    <marker id="arrow" viewBox="0 0 10 10" refX="8" refY="5" markerWidth="6" markerHeight="6" orient="auto-start-reverse">
      <path d="M2 1L8 5L2 9" fill="none" stroke="context-stroke" stroke-width="1.5" stroke-linecap="round" stroke-linejoin="round"/>
    </marker>
  <mask id="imagine-text-gaps-n3rbh3" maskUnits="userSpaceOnUse"><rect x="0" y="0" width="680" height="994" fill="white"/><rect x="36" y="18" width="45.84375" height="19" fill="black" rx="2"/><rect x="236" y="18" width="44.9765625" height="19" fill="black" rx="2"/><rect x="426" y="18" width="44.1015625" height="19" fill="black" rx="2"/><rect x="566" y="18" width="43.703125" height="19" fill="black" rx="2"/><rect x="82.921875" y="46" width="52.15625" height="21.5" fill="black" rx="2"/><rect x="39.56640625" y="66" width="138.8671875" height="19" fill="black" rx="2"/><rect x="34" y="86" width="124.4375" height="19" fill="black" rx="2"/><rect x="34" y="102" width="133.09375" height="19" fill="black" rx="2"/><rect x="34" y="118" width="139.0625" height="19" fill="black" rx="2"/><rect x="34" y="134" width="129.5" height="19" fill="black" rx="2"/><rect x="34" y="150" width="123.3828125" height="19" fill="black" rx="2"/><rect x="181.2578125" y="89" width="55.484375" height="19" fill="black" rx="2"/><rect x="269.01953125" y="47" width="105.9609375" height="21.5" fill="black" rx="2"/><rect x="262.65234375" y="67" width="118.6953125" height="19" fill="black" rx="2"/><rect x="268.609375" y="127" width="106.78125" height="21.5" fill="black" rx="2"/><rect x="242.7109375" y="147" width="158.578125" height="19" fill="black" rx="2"/><rect x="235.953125" y="207" width="172.09375" height="21.5" fill="black" rx="2"/><rect x="259.5703125" y="227" width="124.859375" height="19" fill="black" rx="2"/><rect x="423.15625" y="209" width="27.6875" height="19" fill="black" rx="2"/><rect x="497.875" y="207" width="108.25" height="21.5" fill="black" rx="2"/><rect x="470.0859375" y="227" width="163.828125" height="19" fill="black" rx="2"/><rect x="328" y="259" width="66.609375" height="19" fill="black" rx="2"/><rect x="281.91796875" y="287" width="80.1640625" height="21.5" fill="black" rx="2"/><rect x="254.26953125" y="307" width="135.4609375" height="19" fill="black" rx="2"/><rect x="126.78125" y="289" width="98.4375" height="19" fill="black" rx="2"/><rect x="40.30078125" y="291" width="71.3984375" height="21.5" fill="black" rx="2"/><rect x="52.84765625" y="309" width="46.3046875" height="19" fill="black" rx="2"/><rect x="267.25" y="367" width="109.5" height="21.5" fill="black" rx="2"/><rect x="267.43359375" y="387" width="109.1328125" height="19" fill="black" rx="2"/><rect x="271.5" y="447" width="101" height="21.5" fill="black" rx="2"/><rect x="257.67578125" y="467" width="128.6484375" height="19" fill="black" rx="2"/><rect x="260.28125" y="483" width="123.4375" height="19" fill="black" rx="2"/><rect x="246" y="541" width="152" height="21.5" fill="black" rx="2"/><rect x="286.484375" y="561" width="71.03125" height="19" fill="black" rx="2"/><rect x="243.375" y="577" width="157.25" height="19" fill="black" rx="2"/><rect x="145.15234375" y="550" width="61.6953125" height="19" fill="black" rx="2"/><rect x="42.56640625" y="554" width="66.8671875" height="21.5" fill="black" rx="2"/><rect x="26.71484375" y="572" width="98.5703125" height="19" fill="black" rx="2"/><rect x="268.62109375" y="635" width="106.7578125" height="21.5" fill="black" rx="2"/><rect x="248.37890625" y="655" width="147.2421875" height="19" fill="black" rx="2"/><rect x="248.859375" y="671" width="146.28125" height="19" fill="black" rx="2"/><rect x="291.34375" y="729" width="61.3125" height="21.5" fill="black" rx="2"/><rect x="252.8359375" y="749" width="138.328125" height="19" fill="black" rx="2"/><rect x="148.3828125" y="731" width="55.234375" height="19" fill="black" rx="2"/><rect x="21.7734375" y="735" width="108.453125" height="21.5" fill="black" rx="2"/><rect x="50.69140625" y="753" width="50.6171875" height="19" fill="black" rx="2"/><rect x="249.06640625" y="809" width="145.8671875" height="21.5" fill="black" rx="2"/><rect x="260.73828125" y="829" width="122.5234375" height="19" fill="black" rx="2"/><rect x="249.171875" y="845" width="145.65625" height="19" fill="black" rx="2"/><rect x="492.2734375" y="785" width="119.453125" height="21.5" fill="black" rx="2"/><rect x="469.59375" y="805" width="164.8125" height="19" fill="black" rx="2"/><rect x="420.30078125" y="794" width="33.3984375" height="19" fill="black" rx="2"/><rect x="479.453125" y="857" width="145.09375" height="21.5" fill="black" rx="2"/><rect x="501.859375" y="877" width="100.28125" height="19" fill="black" rx="2"/><rect x="478.77734375" y="893" width="146.4453125" height="19" fill="black" rx="2"/><rect x="280.14453125" y="903" width="83.7109375" height="21.5" fill="black" rx="2"/><rect x="238.47265625" y="923" width="167.0546875" height="19" fill="black" rx="2"/><rect x="421.34375" y="905" width="31.3125" height="19" fill="black" rx="2"/><rect x="478.16796875" y="945" width="145.6640625" height="21.5" fill="black" rx="2"/><rect x="138.87890625" y="905" width="74.2421875" height="19" fill="black" rx="2"/><rect x="33.2578125" y="909" width="85.484375" height="21.5" fill="black" rx="2"/><rect x="32.5078125" y="927" width="86.984375" height="19" fill="black" rx="2"/><rect x="10" y="561" width="125.2734375" height="19" fill="black" rx="2"/></mask></defs>

  <!-- FILE LABELS -->
  <text x="40" y="32" style="font-weight:500;fill:var(--color-text-secondary);fill:rgb(194, 192, 182);stroke:none;color:rgb(255, 255, 255);stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:12px;font-weight:500;text-anchor:start;dominant-baseline:auto">main.h</text>
  <text x="240" y="32" style="font-weight:500;fill:var(--color-text-secondary);fill:rgb(194, 192, 182);stroke:none;color:rgb(255, 255, 255);stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:12px;font-weight:500;text-anchor:start;dominant-baseline:auto">main.c</text>
  <text x="430" y="32" style="font-weight:500;fill:var(--color-text-secondary);fill:rgb(194, 192, 182);stroke:none;color:rgb(255, 255, 255);stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:12px;font-weight:500;text-anchor:start;dominant-baseline:auto">shell.c</text>
  <text x="570" y="32" style="font-weight:500;fill:var(--color-text-secondary);fill:rgb(194, 192, 182);stroke:none;color:rgb(255, 255, 255);stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:12px;font-weight:500;text-anchor:start;dominant-baseline:auto">path.c</text>

  <!-- MAIN.H box -->
  <g style="fill:rgb(0, 0, 0);stroke:none;color:rgb(255, 255, 255);stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:16px;font-weight:400;text-anchor:start;dominant-baseline:auto">
    <rect x="22" y="42" width="174" height="136" rx="8" stroke-width="0.5" style="fill:rgb(68, 68, 65);stroke:rgb(180, 178, 169);color:rgb(255, 255, 255);stroke-width:0.5px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:16px;font-weight:400;text-anchor:start;dominant-baseline:auto"/>
    <text x="109" y="62" text-anchor="middle" style="fill:rgb(211, 209, 199);stroke:none;color:rgb(255, 255, 255);stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:14px;font-weight:500;text-anchor:middle;dominant-baseline:auto">main.h</text>
    <text x="109" y="80" text-anchor="middle" style="fill:rgb(180, 178, 169);stroke:none;color:rgb(255, 255, 255);stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:12px;font-weight:400;text-anchor:middle;dominant-baseline:auto">Header + include guard</text>
    <text x="38" y="100" style="fill:rgb(180, 178, 169);stroke:none;color:rgb(255, 255, 255);stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:12px;font-weight:400;text-anchor:start;dominant-baseline:auto">#include stdio, stdlib</text>
    <text x="38" y="116" style="fill:rgb(180, 178, 169);stroke:none;color:rgb(255, 255, 255);stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:12px;font-weight:400;text-anchor:start;dominant-baseline:auto">#include unistd, string</text>
    <text x="38" y="132" style="fill:rgb(180, 178, 169);stroke:none;color:rgb(255, 255, 255);stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:12px;font-weight:400;text-anchor:start;dominant-baseline:auto">#define MAX_ARGS 64</text>
    <text x="38" y="148" style="fill:rgb(180, 178, 169);stroke:none;color:rgb(255, 255, 255);stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:12px;font-weight:400;text-anchor:start;dominant-baseline:auto">extern char **environ</text>
    <text x="38" y="164" style="fill:rgb(180, 178, 169);stroke:none;color:rgb(255, 255, 255);stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:12px;font-weight:400;text-anchor:start;dominant-baseline:auto">Function prototypes</text>
  </g>

  <!-- Arrow: main.h → main.c -->
  <line x1="196" y1="110" x2="222" y2="110" marker-end="url(#arrow)" stroke-dasharray="4 3" style="fill:none;stroke:rgb(156, 154, 146);color:rgb(255, 255, 255);stroke-width:1.5px;stroke-dasharray:4px, 3px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:16px;font-weight:400;text-anchor:start;dominant-baseline:auto"/>
  <text x="209" y="103" text-anchor="middle" style="fill:rgb(194, 192, 182);stroke:none;color:rgb(255, 255, 255);stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:12px;font-weight:400;text-anchor:middle;dominant-baseline:auto">includes</text>

  <!-- STEP 1: main() entry -->
  <g style="fill:rgb(0, 0, 0);stroke:none;color:rgb(255, 255, 255);stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:16px;font-weight:400;text-anchor:start;dominant-baseline:auto">
    <rect x="222" y="42" width="200" height="56" rx="8" stroke-width="0.5" style="fill:rgb(60, 52, 137);stroke:rgb(175, 169, 236);color:rgb(255, 255, 255);stroke-width:0.5px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:16px;font-weight:400;text-anchor:start;dominant-baseline:auto"/>
    <text x="322" y="63" text-anchor="middle" style="fill:rgb(206, 203, 246);stroke:none;color:rgb(255, 255, 255);stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:14px;font-weight:500;text-anchor:middle;dominant-baseline:auto">1. main() starts</text>
    <text x="322" y="81" text-anchor="middle" style="fill:rgb(175, 169, 236);stroke:none;color:rgb(255, 255, 255);stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:12px;font-weight:400;text-anchor:middle;dominant-baseline:auto">int main(ac, av, env)</text>
  </g>

  <!-- Arrow down -->
  <line x1="322" y1="98" x2="322" y2="122" marker-end="url(#arrow)" style="fill:none;stroke:rgb(156, 154, 146);color:rgb(255, 255, 255);stroke-width:1.5px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:16px;font-weight:400;text-anchor:start;dominant-baseline:auto"/>

  <!-- STEP 2: while(1) loop -->
  <g style="fill:rgb(0, 0, 0);stroke:none;color:rgb(255, 255, 255);stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:16px;font-weight:400;text-anchor:start;dominant-baseline:auto">
    <rect x="222" y="122" width="200" height="56" rx="8" stroke-width="0.5" style="fill:rgb(60, 52, 137);stroke:rgb(175, 169, 236);color:rgb(255, 255, 255);stroke-width:0.5px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:16px;font-weight:400;text-anchor:start;dominant-baseline:auto"/>
    <text x="322" y="143" text-anchor="middle" style="fill:rgb(206, 203, 246);stroke:none;color:rgb(255, 255, 255);stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:14px;font-weight:500;text-anchor:middle;dominant-baseline:auto">2. while(1) loop</text>
    <text x="322" y="161" text-anchor="middle" style="fill:rgb(175, 169, 236);stroke:none;color:rgb(255, 255, 255);stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:12px;font-weight:400;text-anchor:middle;dominant-baseline:auto">Infinite read-execute cycle</text>
  </g>

  <!-- Arrow down -->
  <line x1="322" y1="178" x2="322" y2="202" marker-end="url(#arrow)" style="fill:none;stroke:rgb(156, 154, 146);color:rgb(255, 255, 255);stroke-width:1.5px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:16px;font-weight:400;text-anchor:start;dominant-baseline:auto"/>

  <!-- STEP 3: isatty check -->
  <g style="fill:rgb(0, 0, 0);stroke:none;color:rgb(255, 255, 255);stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:16px;font-weight:400;text-anchor:start;dominant-baseline:auto">
    <rect x="222" y="202" width="200" height="56" rx="8" stroke-width="0.5" style="fill:rgb(8, 80, 65);stroke:rgb(93, 202, 165);color:rgb(255, 255, 255);stroke-width:0.5px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:16px;font-weight:400;text-anchor:start;dominant-baseline:auto"/>
    <text x="322" y="223" text-anchor="middle" style="fill:rgb(159, 225, 203);stroke:none;color:rgb(255, 255, 255);stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:14px;font-weight:500;text-anchor:middle;dominant-baseline:auto">3. isatty(STDIN_FILENO)</text>
    <text x="322" y="241" text-anchor="middle" style="fill:rgb(93, 202, 165);stroke:none;color:rgb(255, 255, 255);stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:12px;font-weight:400;text-anchor:middle;dominant-baseline:auto">Interactive or piped?</text>
  </g>

  <!-- Arrow: isatty YES → print_prompt in shell.c -->
  <line x1="422" y1="230" x2="452" y2="230" marker-end="url(#arrow)" style="fill:none;stroke:rgb(156, 154, 146);color:rgb(255, 255, 255);stroke-width:1.5px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:16px;font-weight:400;text-anchor:start;dominant-baseline:auto"/>
  <text x="437" y="223" text-anchor="middle" style="fill:rgb(194, 192, 182);stroke:none;color:rgb(255, 255, 255);stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:12px;font-weight:400;text-anchor:middle;dominant-baseline:auto">yes</text>

  <!-- shell.c: print_prompt -->
  <g style="fill:rgb(0, 0, 0);stroke:none;color:rgb(255, 255, 255);stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:16px;font-weight:400;text-anchor:start;dominant-baseline:auto">
    <rect x="452" y="202" width="200" height="56" rx="8" stroke-width="0.5" style="fill:rgb(113, 43, 19);stroke:rgb(240, 153, 123);color:rgb(255, 255, 255);stroke-width:0.5px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:16px;font-weight:400;text-anchor:start;dominant-baseline:auto"/>
    <text x="552" y="223" text-anchor="middle" style="fill:rgb(245, 196, 179);stroke:none;color:rgb(255, 255, 255);stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:14px;font-weight:500;text-anchor:middle;dominant-baseline:auto">print_prompt()</text>
    <text x="552" y="241" text-anchor="middle" style="fill:rgb(240, 153, 123);stroke:none;color:rgb(255, 255, 255);stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:12px;font-weight:400;text-anchor:middle;dominant-baseline:auto">printf("($) "); fflush(stdout)</text>
  </g>

  <!-- Arrow: back down after prompt -->
  <line x1="322" y1="258" x2="322" y2="282" marker-end="url(#arrow)" style="fill:none;stroke:rgb(156, 154, 146);color:rgb(255, 255, 255);stroke-width:1.5px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:16px;font-weight:400;text-anchor:start;dominant-baseline:auto"/>
  <text x="332" y="273" style="fill:rgb(194, 192, 182);stroke:none;color:rgb(255, 255, 255);stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:12px;font-weight:400;text-anchor:start;dominant-baseline:auto">no prompt</text>

  <!-- line from shell.c back down -->
  <path d="M552 258 L552 270 L322 270 L322 282" fill="none" marker-end="url(#arrow)" stroke-dasharray="3 3" mask="url(#imagine-text-gaps-n3rbh3)" style="fill:none;stroke:rgb(156, 154, 146);color:rgb(255, 255, 255);stroke-width:1.5px;stroke-dasharray:3px, 3px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:16px;font-weight:400;text-anchor:start;dominant-baseline:auto"/>

  <!-- STEP 4: getline -->
  <g style="fill:rgb(0, 0, 0);stroke:none;color:rgb(255, 255, 255);stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:16px;font-weight:400;text-anchor:start;dominant-baseline:auto">
    <rect x="222" y="282" width="200" height="56" rx="8" stroke-width="0.5" style="fill:rgb(8, 80, 65);stroke:rgb(93, 202, 165);color:rgb(255, 255, 255);stroke-width:0.5px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:16px;font-weight:400;text-anchor:start;dominant-baseline:auto"/>
    <text x="322" y="303" text-anchor="middle" style="fill:rgb(159, 225, 203);stroke:none;color:rgb(255, 255, 255);stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:14px;font-weight:500;text-anchor:middle;dominant-baseline:auto">4. getline()</text>
    <text x="322" y="321" text-anchor="middle" style="fill:rgb(93, 202, 165);stroke:none;color:rgb(255, 255, 255);stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:12px;font-weight:400;text-anchor:middle;dominant-baseline:auto">Reads a line from stdin</text>
  </g>

  <!-- EOF branch -->
  <line x1="222" y1="310" x2="130" y2="310" marker-end="url(#arrow)" style="fill:none;stroke:rgb(156, 154, 146);color:rgb(255, 255, 255);stroke-width:1.5px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:16px;font-weight:400;text-anchor:start;dominant-baseline:auto"/>
  <text x="176" y="303" text-anchor="middle" style="fill:rgb(194, 192, 182);stroke:none;color:rgb(255, 255, 255);stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:12px;font-weight:400;text-anchor:middle;dominant-baseline:auto">EOF / nread==-1</text>
  <g style="fill:rgb(0, 0, 0);stroke:none;color:rgb(255, 255, 255);stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:16px;font-weight:400;text-anchor:start;dominant-baseline:auto">
    <rect x="22" y="286" width="108" height="48" rx="8" stroke-width="0.5" style="fill:rgb(121, 31, 31);stroke:rgb(240, 149, 149);color:rgb(255, 255, 255);stroke-width:0.5px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:16px;font-weight:400;text-anchor:start;dominant-baseline:auto"/>
    <text x="76" y="307" text-anchor="middle" style="fill:rgb(247, 193, 193);stroke:none;color:rgb(255, 255, 255);stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:14px;font-weight:500;text-anchor:middle;dominant-baseline:auto">free(line)</text>
    <text x="76" y="323" text-anchor="middle" style="fill:rgb(240, 149, 149);stroke:none;color:rgb(255, 255, 255);stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:12px;font-weight:400;text-anchor:middle;dominant-baseline:auto">exit(0)</text>
  </g>

  <!-- Arrow down -->
  <line x1="322" y1="338" x2="322" y2="362" marker-end="url(#arrow)" style="fill:none;stroke:rgb(156, 154, 146);color:rgb(255, 255, 255);stroke-width:1.5px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:16px;font-weight:400;text-anchor:start;dominant-baseline:auto"/>

  <!-- STEP 5: strip newline -->
  <g style="fill:rgb(0, 0, 0);stroke:none;color:rgb(255, 255, 255);stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:16px;font-weight:400;text-anchor:start;dominant-baseline:auto">
    <rect x="222" y="362" width="200" height="56" rx="8" stroke-width="0.5" style="fill:rgb(8, 80, 65);stroke:rgb(93, 202, 165);color:rgb(255, 255, 255);stroke-width:0.5px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:16px;font-weight:400;text-anchor:start;dominant-baseline:auto"/>
    <text x="322" y="383" text-anchor="middle" style="fill:rgb(159, 225, 203);stroke:none;color:rgb(255, 255, 255);stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:14px;font-weight:500;text-anchor:middle;dominant-baseline:auto">5. Strip newline</text>
    <text x="322" y="401" text-anchor="middle" style="fill:rgb(93, 202, 165);stroke:none;color:rgb(255, 255, 255);stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:12px;font-weight:400;text-anchor:middle;dominant-baseline:auto">line[nread-1] = '\0'</text>
  </g>

  <!-- Arrow down -->
  <line x1="322" y1="418" x2="322" y2="442" marker-end="url(#arrow)" style="fill:none;stroke:rgb(156, 154, 146);color:rgb(255, 255, 255);stroke-width:1.5px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:16px;font-weight:400;text-anchor:start;dominant-baseline:auto"/>

  <!-- STEP 6: Trim spaces (still in main.c but logically a trim block) -->
  <g style="fill:rgb(0, 0, 0);stroke:none;color:rgb(255, 255, 255);stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:16px;font-weight:400;text-anchor:start;dominant-baseline:auto">
    <rect x="222" y="442" width="200" height="70" rx="8" stroke-width="0.5" style="fill:rgb(8, 80, 65);stroke:rgb(93, 202, 165);color:rgb(255, 255, 255);stroke-width:0.5px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:16px;font-weight:400;text-anchor:start;dominant-baseline:auto"/>
    <text x="322" y="463" text-anchor="middle" style="fill:rgb(159, 225, 203);stroke:none;color:rgb(255, 255, 255);stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:14px;font-weight:500;text-anchor:middle;dominant-baseline:auto">6. Trim spaces</text>
    <text x="322" y="481" text-anchor="middle" style="fill:rgb(93, 202, 165);stroke:none;color:rgb(255, 255, 255);stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:12px;font-weight:400;text-anchor:middle;dominant-baseline:auto">Walk j backwards, set</text>
    <text x="322" y="497" text-anchor="middle" style="fill:rgb(93, 202, 165);stroke:none;color:rgb(255, 255, 255);stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:12px;font-weight:400;text-anchor:middle;dominant-baseline:auto">trailing spaces to '\0'</text>
  </g>

  <!-- Arrow down -->
  <line x1="322" y1="512" x2="322" y2="536" marker-end="url(#arrow)" style="fill:none;stroke:rgb(156, 154, 146);color:rgb(255, 255, 255);stroke-width:1.5px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:16px;font-weight:400;text-anchor:start;dominant-baseline:auto"/>

  <!-- STEP 7: skip leading spaces -->
  <g style="fill:rgb(0, 0, 0);stroke:none;color:rgb(255, 255, 255);stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:16px;font-weight:400;text-anchor:start;dominant-baseline:auto">
    <rect x="222" y="536" width="200" height="70" rx="8" stroke-width="0.5" style="fill:rgb(8, 80, 65);stroke:rgb(93, 202, 165);color:rgb(255, 255, 255);stroke-width:0.5px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:16px;font-weight:400;text-anchor:start;dominant-baseline:auto"/>
    <text x="322" y="557" text-anchor="middle" style="fill:rgb(159, 225, 203);stroke:none;color:rgb(255, 255, 255);stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:14px;font-weight:500;text-anchor:middle;dominant-baseline:auto">7. Skip leading spaces</text>
    <text x="322" y="575" text-anchor="middle" style="fill:rgb(93, 202, 165);stroke:none;color:rgb(255, 255, 255);stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:12px;font-weight:400;text-anchor:middle;dominant-baseline:auto">start = line;</text>
    <text x="322" y="591" text-anchor="middle" style="fill:rgb(93, 202, 165);stroke:none;color:rgb(255, 255, 255);stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:12px;font-weight:400;text-anchor:middle;dominant-baseline:auto">while (*start == ' ') start++</text>
  </g>

  <!-- blank line check -->
  <line x1="222" y1="571" x2="130" y2="571" marker-end="url(#arrow)" mask="url(#imagine-text-gaps-n3rbh3)" style="fill:none;stroke:rgb(156, 154, 146);color:rgb(255, 255, 255);stroke-width:1.5px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:16px;font-weight:400;text-anchor:start;dominant-baseline:auto"/>
  <text x="176" y="564" text-anchor="middle" style="fill:rgb(194, 192, 182);stroke:none;color:rgb(255, 255, 255);stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:12px;font-weight:400;text-anchor:middle;dominant-baseline:auto">blank line</text>
  <g style="fill:rgb(0, 0, 0);stroke:none;color:rgb(255, 255, 255);stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:16px;font-weight:400;text-anchor:start;dominant-baseline:auto">
    <rect x="22" y="549" width="108" height="44" rx="8" stroke-width="0.5" style="fill:rgb(68, 68, 65);stroke:rgb(180, 178, 169);color:rgb(255, 255, 255);stroke-width:0.5px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:16px;font-weight:400;text-anchor:start;dominant-baseline:auto"/>
    <text x="76" y="570" text-anchor="middle" style="fill:rgb(211, 209, 199);stroke:none;color:rgb(255, 255, 255);stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:14px;font-weight:500;text-anchor:middle;dominant-baseline:auto">continue</text>
    <text x="76" y="586" text-anchor="middle" style="fill:rgb(180, 178, 169);stroke:none;color:rgb(255, 255, 255);stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:12px;font-weight:400;text-anchor:middle;dominant-baseline:auto">back to loop top</text>
  </g>

  <!-- Arrow down -->
  <line x1="322" y1="606" x2="322" y2="630" marker-end="url(#arrow)" style="fill:none;stroke:rgb(156, 154, 146);color:rgb(255, 255, 255);stroke-width:1.5px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:16px;font-weight:400;text-anchor:start;dominant-baseline:auto"/>

  <!-- STEP 8: strtok split -->
  <g style="fill:rgb(0, 0, 0);stroke:none;color:rgb(255, 255, 255);stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:16px;font-weight:400;text-anchor:start;dominant-baseline:auto">
    <rect x="222" y="630" width="200" height="70" rx="8" stroke-width="0.5" style="fill:rgb(8, 80, 65);stroke:rgb(93, 202, 165);color:rgb(255, 255, 255);stroke-width:0.5px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:16px;font-weight:400;text-anchor:start;dominant-baseline:auto"/>
    <text x="322" y="651" text-anchor="middle" style="fill:rgb(159, 225, 203);stroke:none;color:rgb(255, 255, 255);stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:14px;font-weight:500;text-anchor:middle;dominant-baseline:auto">8. strtok() split</text>
    <text x="322" y="669" text-anchor="middle" style="fill:rgb(93, 202, 165);stroke:none;color:rgb(255, 255, 255);stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:12px;font-weight:400;text-anchor:middle;dominant-baseline:auto">argv[i] = strtok(start, " ")</text>
    <text x="322" y="685" text-anchor="middle" style="fill:rgb(93, 202, 165);stroke:none;color:rgb(255, 255, 255);stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:12px;font-weight:400;text-anchor:middle;dominant-baseline:auto">"ls -la" → ["ls","-la",NULL]</text>
  </g>

  <!-- Arrow down -->
  <line x1="322" y1="700" x2="322" y2="724" marker-end="url(#arrow)" style="fill:none;stroke:rgb(156, 154, 146);color:rgb(255, 255, 255);stroke-width:1.5px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:16px;font-weight:400;text-anchor:start;dominant-baseline:auto"/>

  <!-- STEP 9: fork() -->
  <g style="fill:rgb(0, 0, 0);stroke:none;color:rgb(255, 255, 255);stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:16px;font-weight:400;text-anchor:start;dominant-baseline:auto">
    <rect x="222" y="724" width="200" height="56" rx="8" stroke-width="0.5" style="fill:rgb(60, 52, 137);stroke:rgb(175, 169, 236);color:rgb(255, 255, 255);stroke-width:0.5px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:16px;font-weight:400;text-anchor:start;dominant-baseline:auto"/>
    <text x="322" y="745" text-anchor="middle" style="fill:rgb(206, 203, 246);stroke:none;color:rgb(255, 255, 255);stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:14px;font-weight:500;text-anchor:middle;dominant-baseline:auto">9. fork()</text>
    <text x="322" y="763" text-anchor="middle" style="fill:rgb(175, 169, 236);stroke:none;color:rgb(255, 255, 255);stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:12px;font-weight:400;text-anchor:middle;dominant-baseline:auto">Split into parent + child</text>
  </g>

  <!-- fork error -->
  <line x1="222" y1="752" x2="130" y2="752" marker-end="url(#arrow)" mask="url(#imagine-text-gaps-n3rbh3)" style="fill:none;stroke:rgb(156, 154, 146);color:rgb(255, 255, 255);stroke-width:1.5px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:16px;font-weight:400;text-anchor:start;dominant-baseline:auto"/>
  <text x="176" y="745" text-anchor="middle" style="fill:rgb(194, 192, 182);stroke:none;color:rgb(255, 255, 255);stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:12px;font-weight:400;text-anchor:middle;dominant-baseline:auto">fork==-1</text>
  <g style="fill:rgb(0, 0, 0);stroke:none;color:rgb(255, 255, 255);stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:16px;font-weight:400;text-anchor:start;dominant-baseline:auto">
    <rect x="22" y="730" width="108" height="44" rx="8" stroke-width="0.5" style="fill:rgb(121, 31, 31);stroke:rgb(240, 149, 149);color:rgb(255, 255, 255);stroke-width:0.5px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:16px;font-weight:400;text-anchor:start;dominant-baseline:auto"/>
    <text x="76" y="751" text-anchor="middle" style="fill:rgb(247, 193, 193);stroke:none;color:rgb(255, 255, 255);stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:14px;font-weight:500;text-anchor:middle;dominant-baseline:auto">perror("Error")</text>
    <text x="76" y="767" text-anchor="middle" style="fill:rgb(240, 149, 149);stroke:none;color:rgb(255, 255, 255);stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:12px;font-weight:400;text-anchor:middle;dominant-baseline:auto">return 1</text>
  </g>

  <!-- Arrow child path -->
  <line x1="322" y1="780" x2="322" y2="804" marker-end="url(#arrow)" style="fill:none;stroke:rgb(156, 154, 146);color:rgb(255, 255, 255);stroke-width:1.5px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:16px;font-weight:400;text-anchor:start;dominant-baseline:auto"/>

  <!-- STEP 10: child execve via find_path -->
  <g style="fill:rgb(0, 0, 0);stroke:none;color:rgb(255, 255, 255);stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:16px;font-weight:400;text-anchor:start;dominant-baseline:auto">
    <rect x="222" y="804" width="200" height="70" rx="8" stroke-width="0.5" style="fill:rgb(99, 56, 6);stroke:rgb(239, 159, 39);color:rgb(255, 255, 255);stroke-width:0.5px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:16px;font-weight:400;text-anchor:start;dominant-baseline:auto"/>
    <text x="322" y="825" text-anchor="middle" style="fill:rgb(250, 199, 117);stroke:none;color:rgb(255, 255, 255);stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:14px;font-weight:500;text-anchor:middle;dominant-baseline:auto">10. Child: find_path()</text>
    <text x="322" y="843" text-anchor="middle" style="fill:rgb(239, 159, 39);stroke:none;color:rgb(255, 255, 255);stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:12px;font-weight:400;text-anchor:middle;dominant-baseline:auto">Searches $PATH dirs</text>
    <text x="322" y="859" text-anchor="middle" style="fill:rgb(239, 159, 39);stroke:none;color:rgb(255, 255, 255);stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:12px;font-weight:400;text-anchor:middle;dominant-baseline:auto">returns "/bin/ls" or NULL</text>
  </g>

  <!-- path.c: get_env box -->
  <g style="fill:rgb(0, 0, 0);stroke:none;color:rgb(255, 255, 255);stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:16px;font-weight:400;text-anchor:start;dominant-baseline:auto">
    <rect x="452" y="780" width="200" height="56" rx="8" stroke-width="0.5" style="fill:rgb(39, 80, 10);stroke:rgb(151, 196, 89);color:rgb(255, 255, 255);stroke-width:0.5px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:16px;font-weight:400;text-anchor:start;dominant-baseline:auto"/>
    <text x="552" y="801" text-anchor="middle" style="fill:rgb(192, 221, 151);stroke:none;color:rgb(255, 255, 255);stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:14px;font-weight:500;text-anchor:middle;dominant-baseline:auto">get_env("PATH")</text>
    <text x="552" y="819" text-anchor="middle" style="fill:rgb(151, 196, 89);stroke:none;color:rgb(255, 255, 255);stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:12px;font-weight:400;text-anchor:middle;dominant-baseline:auto">Scans environ[] for "PATH="</text>
  </g>
  <line x1="422" y1="820" x2="452" y2="810" marker-end="url(#arrow)" mask="url(#imagine-text-gaps-n3rbh3)" style="fill:none;stroke:rgb(156, 154, 146);color:rgb(255, 255, 255);stroke-width:1.5px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:16px;font-weight:400;text-anchor:start;dominant-baseline:auto"/>
  <text x="437" y="808" text-anchor="middle" style="fill:rgb(194, 192, 182);stroke:none;color:rgb(255, 255, 255);stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:12px;font-weight:400;text-anchor:middle;dominant-baseline:auto">calls</text>

  <!-- path.c: strtok PATH dirs -->
  <g style="fill:rgb(0, 0, 0);stroke:none;color:rgb(255, 255, 255);stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:16px;font-weight:400;text-anchor:start;dominant-baseline:auto">
    <rect x="452" y="852" width="200" height="70" rx="8" stroke-width="0.5" style="fill:rgb(39, 80, 10);stroke:rgb(151, 196, 89);color:rgb(255, 255, 255);stroke-width:0.5px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:16px;font-weight:400;text-anchor:start;dominant-baseline:auto"/>
    <text x="552" y="873" text-anchor="middle" style="fill:rgb(192, 221, 151);stroke:none;color:rgb(255, 255, 255);stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:14px;font-weight:500;text-anchor:middle;dominant-baseline:auto">Check each PATH dir</text>
    <text x="552" y="891" text-anchor="middle" style="fill:rgb(151, 196, 89);stroke:none;color:rgb(255, 255, 255);stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:12px;font-weight:400;text-anchor:middle;dominant-baseline:auto">sprintf("/bin/ls")</text>
    <text x="552" y="907" text-anchor="middle" style="fill:rgb(151, 196, 89);stroke:none;color:rgb(255, 255, 255);stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:12px;font-weight:400;text-anchor:middle;dominant-baseline:auto">access(full, X_OK) == 0?</text>
  </g>
  <line x1="552" y1="836" x2="552" y2="852" marker-end="url(#arrow)" style="fill:none;stroke:rgb(156, 154, 146);color:rgb(255, 255, 255);stroke-width:1.5px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:16px;font-weight:400;text-anchor:start;dominant-baseline:auto"/>

  <!-- Arrow down to execve -->
  <line x1="322" y1="874" x2="322" y2="898" marker-end="url(#arrow)" style="fill:none;stroke:rgb(156, 154, 146);color:rgb(255, 255, 255);stroke-width:1.5px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:16px;font-weight:400;text-anchor:start;dominant-baseline:auto"/>

  <!-- STEP 11: execve -->
  <g style="fill:rgb(0, 0, 0);stroke:none;color:rgb(255, 255, 255);stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:16px;font-weight:400;text-anchor:start;dominant-baseline:auto">
    <rect x="222" y="898" width="200" height="56" rx="8" stroke-width="0.5" style="fill:rgb(60, 52, 137);stroke:rgb(175, 169, 236);color:rgb(255, 255, 255);stroke-width:0.5px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:16px;font-weight:400;text-anchor:start;dominant-baseline:auto"/>
    <text x="322" y="919" text-anchor="middle" style="fill:rgb(206, 203, 246);stroke:none;color:rgb(255, 255, 255);stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:14px;font-weight:500;text-anchor:middle;dominant-baseline:auto">11. execve()</text>
    <text x="322" y="937" text-anchor="middle" style="fill:rgb(175, 169, 236);stroke:none;color:rgb(255, 255, 255);stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:12px;font-weight:400;text-anchor:middle;dominant-baseline:auto">Replaces child with program</text>
  </g>

  <!-- execve fail -->
  <line x1="422" y1="926" x2="452" y2="926" marker-end="url(#arrow)" style="fill:none;stroke:rgb(156, 154, 146);color:rgb(255, 255, 255);stroke-width:1.5px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:16px;font-weight:400;text-anchor:start;dominant-baseline:auto"/>
  <text x="437" y="919" text-anchor="middle" style="fill:rgb(194, 192, 182);stroke:none;color:rgb(255, 255, 255);stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:12px;font-weight:400;text-anchor:middle;dominant-baseline:auto">fails</text>
  <g style="fill:rgb(0, 0, 0);stroke:none;color:rgb(255, 255, 255);stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:16px;font-weight:400;text-anchor:start;dominant-baseline:auto">
    <rect x="452" y="940" width="198" height="44" rx="8" stroke-width="0.5" style="fill:rgb(121, 31, 31);stroke:rgb(240, 149, 149);color:rgb(255, 255, 255);stroke-width:0.5px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:16px;font-weight:400;text-anchor:start;dominant-baseline:auto"/>
    <text x="551" y="961" text-anchor="middle" style="fill:rgb(247, 193, 193);stroke:none;color:rgb(255, 255, 255);stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:14px;font-weight:500;text-anchor:middle;dominant-baseline:auto">perror(av[0]); exit(1)</text>
  </g>
  <line x1="551" y1="926" x2="551" y2="940" marker-end="url(#arrow)" stroke-dasharray="3 3" style="fill:none;stroke:rgb(156, 154, 146);color:rgb(255, 255, 255);stroke-width:1.5px;stroke-dasharray:3px, 3px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:16px;font-weight:400;text-anchor:start;dominant-baseline:auto"/>

  <!-- parent: wait -->
  <line x1="222" y1="926" x2="130" y2="926" marker-end="url(#arrow)" style="fill:none;stroke:rgb(156, 154, 146);color:rgb(255, 255, 255);stroke-width:1.5px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:16px;font-weight:400;text-anchor:start;dominant-baseline:auto"/>
  <text x="176" y="919" text-anchor="middle" style="fill:rgb(194, 192, 182);stroke:none;color:rgb(255, 255, 255);stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:12px;font-weight:400;text-anchor:middle;dominant-baseline:auto">parent path</text>
  <g style="fill:rgb(0, 0, 0);stroke:none;color:rgb(255, 255, 255);stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:16px;font-weight:400;text-anchor:start;dominant-baseline:auto">
    <rect x="22" y="904" width="108" height="44" rx="8" stroke-width="0.5" style="fill:rgb(68, 68, 65);stroke:rgb(180, 178, 169);color:rgb(255, 255, 255);stroke-width:0.5px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:16px;font-weight:400;text-anchor:start;dominant-baseline:auto"/>
    <text x="76" y="925" text-anchor="middle" style="fill:rgb(211, 209, 199);stroke:none;color:rgb(255, 255, 255);stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:14px;font-weight:500;text-anchor:middle;dominant-baseline:auto">wait(NULL)</text>
    <text x="76" y="941" text-anchor="middle" style="fill:rgb(180, 178, 169);stroke:none;color:rgb(255, 255, 255);stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:12px;font-weight:400;text-anchor:middle;dominant-baseline:auto">waits for child</text>
  </g>

  <!-- Loop back arrow from parent wait to loop top -->
  <path d="M22 926 L10 926 L10 230 L222 230" fill="none" marker-end="url(#arrow)" stroke-dasharray="5 3" opacity="0.5" mask="url(#imagine-text-gaps-n3rbh3)" style="fill:none;stroke:rgb(156, 154, 146);color:rgb(255, 255, 255);stroke-width:1.5px;stroke-dasharray:5px, 3px;stroke-linecap:butt;stroke-linejoin:miter;opacity:0.5;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:16px;font-weight:400;text-anchor:start;dominant-baseline:auto"/>
  <text x="14" y="575" style="writing-mode:inherit;fill:rgb(194, 192, 182);stroke:none;color:rgb(255, 255, 255);stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;opacity:1;font-family:&quot;Anthropic Sans&quot;, -apple-system, &quot;system-ui&quot;, &quot;Segoe UI&quot;, sans-serif;font-size:12px;font-weight:400;text-anchor:start;dominant-baseline:auto">↑ back to top of loop</text>

</svg>]()


## Authors

* Shirleen Asre — https://github.com/bumble-beed
* Sean Sabino — https://github.com/SSabin0
