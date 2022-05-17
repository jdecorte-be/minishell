<header>
<h1 align="center">
  <a href="https://github.com/jdecorte-be/minishell"><img src=".assets/banner.png" alt="minishell" ></a>
  minishell
  <br>
</h1>

<p align="center">
  This program tries to recreate bash --posix behaviour in some ways.
</p>

<p align="center">
<a href="https://www.42.fr/">
    <img src="https://img.shields.io/badge/42-School%20Project-00B8D4?logo=42&logoColor=white&labelColor=000000"
         alt="42 School Project">
  </a>
<a href="https://github.com/jdecorte-be/minishell">
    <img src="https://img.shields.io/badge/Focus-Shell%20Emulation-555555?logo=gnubash&logoColor=white&labelColor=000000"
         alt="Focus Shell Emulation">
  </a>
<a href="https://github.com/jdecorte-be/minishell">
    <img src="https://img.shields.io/badge/Type-Command--Line%20Interface-4695E3?logo=powershell&logoColor=white&labelColor=000000"
         alt="Type Command-Line Interface">
  </a>
<a href="https://en.wikipedia.org/wiki/C_(programming_language)">
    <img src="https://img.shields.io/badge/Technology-C%20Language-A8B9CC?logo=c&logoColor=white&labelColor=000000"
         alt="Technology C Language">
  </a>
</p>

<p align="center">
<a href="https://en.wikipedia.org/wiki/POSIX">
    <img src="https://img.shields.io/badge/Environment-POSIX-4CAF50?logo=linux&logoColor=white&labelColor=000000"
         alt="Environment POSIX">
  </a>
  <a href="https://github.com/jdecorte-be/minishell">
    <img src="https://img.shields.io/badge/Type-CLI-informational?logo=terminal&logoColor=white&labelColor=000000&color=66D9EF"
         alt="minishell cli">
  </a>
  <a href="https://github.com/jdecorte-be/minishell/stargazers">
    <img src="https://img.shields.io/github/stars/jdecorte-be/minishell?logo=star&logoColor=white&labelColor=000000&color=E6DB74"
         alt="minishell stars">
  </a>
  <a href="https://github.com/jdecorte-be/minishell/issues">
    <img src="https://img.shields.io/github/issues/jdecorte-be/minishell?logoColor=white&labelColor=000000&color=orange"
         alt="minishell issues">
  </a>
  <a href="https://github.com/jdecorte-be/minishell">
    <img src="https://img.shields.io/github/repo-size/jdecorte-be/minishell?logo=database&logoColor=white&labelColor=000000&color=AE81FF"
         alt="minishell repo size">
  </a>
  <a href="https://github.com/jdecorte-be/minishell">
    <img src="https://img.shields.io/github/languages/top/jdecorte-be/minishell?logo=code&logoColor=white&labelColor=000000&color=A6E22E"
         alt="minishell top language">
  </a>
</p>
<p align="center">
  <a href="#execution">Execution :</a> •
  <a href="#informations-briefly">Informations Briefly</a> •
  <a href="#what-you-should-know-summary">What you should know (Summary)</a> •
  <a href="#i-parsing">I- Parsing</a> •
  <a href="#1-separation-commandeline">1. Separation commande_line</a> •
  <a href="#11-quote-close-quoting-rules">1.1 Quote close, Quoting rules</a> •
  <a href="#2-separation-of-words-in-commandeline">2. Separation of words in commande_line</a>
</p>
</header>

Minishell is a 42 school project to create a simple shell interpreter in C. This project recreates core `bash` functionalities, including pipes, redirections, environment variable handling, and several built-in commands.

## Features

- **Command Execution:** Executes system commands found in `PATH`.
- **Pipes (`|`):** Chains multiple commands, piping the output of one to the input of the next.
- **Redirections:**
  - Input: `<`
  - Output: `>` (truncate) and `>>` (append)
  - Here-document: `<<`
- **Built-in Commands:**
  - `echo` with the `-n` option
  - `cd` to change the current directory
  - `pwd` to print the working directory
  - `export` to set environment variables
  - `unset` to remove environment variables
  - `env` to list environment variables
  - `exit` to terminate the shell
- **Environment Variables:** Expands variables like `$USER` and handles the exit status variable `$?`.
- **Signal Handling:** Manages `Ctrl-C`, `Ctrl-D`, and `Ctrl-\` to behave similarly to `bash`.
- **Quoting:** Supports single (`'`) and double (`"`) quotes to control expansion and word splitting.

## Getting Started

### Prerequisites

- A C compiler (like `gcc` or `clang`)
- `make`
- The `readline` library

### Installation & Usage

1.  **Clone the repository:**
    ```sh
    git clone https://github.com/jdecorte-be/minishell.git
    cd minishell
    ```

2.  **Compile the program:**
    ```sh
    make
    ```

3.  **Run the shell:**
    ```sh
    ./minishell
    ```

## Technical Overview

This section details the internal logic of Minishell, from parsing the input to executing commands.

### 1. Parsing

The parser is responsible for transforming the raw command line string into a structured format that the executor can understand.

#### 1.1. Command Line Tokenization

The input string is first split into a linked list of tokens. The primary delimiter is the pipe (`|`) character, which separates individual commands. Special care is taken to ignore pipes that are inside single or double quotes.

Each node in the command list contains the raw command string for that segment.

```c
struct cmd_line {
    char             *cmd;
    struct token     *word;
    char             **args;
    struct cmd_line  *next;
};
```

#### 1.2. Quote Handling

The parser correctly handles quoted strings to ensure that special characters within them are treated as literals.

-   **Single Quotes (`'`):** All characters within single quotes are treated literally. No expansion occurs.
    ```sh
    # This will print the literal string '$USER | ls'
    echo '$USER | ls'
    ```

-   **Double Quotes (`"`):** Most characters are treated literally, but environment variables (e.g., `$USER`) are expanded.
    ```sh
    # This will print the current user's name followed by "| 'hello'"
    echo "$USER | 'hello'"
    ```

-   **Unquoted:** All special characters (`|`, `<`, `>`, `$`) are interpreted by the shell. Spaces act as word delimiters.

#### 1.3. Word Splitting and Typing

Each command string is further broken down into a linked list of words (tokens). Each token is assigned a type to guide the execution process.

```c
struct token {
    char          *word;
    enum type     type;
    struct token  *next;
};

enum type {
    NONE,         // Default
    ARG,          // A command or argument
    FILE_IN,      // A redirection operator: <
    HERE_DOC,     // A here-document operator: <<
    FILE_OUT,     // A redirection operator: >
    FILE_OUT_SUR, // A redirection operator: >>
    OPEN_FILE,    // The name of a file for input
    LIMITOR,      // The delimiter for a here-document
    EXIT_FILE,    // The name of a file for output
    EXIT_FILE_RET // The name of a file for appending output
};
```

The parser also checks for syntax errors, such as `cat > > file_out` or an unexpected pipe `|`.

#### 1.4. Variable Expansion (`$`)

The parser expands environment variables based on quoting rules:

-   Variables are identified by a `$` prefix followed by alphanumeric characters or `_`.
-   `$?` is a special variable that expands to the exit status of the last command.
-   `$$` is handled as a literal `$`.
-   If a variable is unquoted and its value contains spaces (e.g., `export VAR="ls -l"`), the expanded result is split into multiple words (`ls` and `-l`).
-   If a variable is inside double quotes (`"$VAR"`), its value is treated as a single word, even if it contains spaces.
-   Expansion is disabled for here-document limiters and within single quotes.

### 2. Built-in Commands

Built-in commands are executed directly by the shell without creating a new process.

-   `echo [-n] [string ...]`: Prints arguments to standard output. The `-n` flag suppresses the trailing newline.
-   `cd [path]`: Changes the current directory.
-   `pwd`: Prints the absolute path of the current directory.
-   `export [name[=value] ...]`: Creates or modifies environment variables.
-   `unset [name ...]`: Deletes environment variables.
-   `env`: Prints the environment variables.
-   `exit [n]`: Exits the shell.
    -   `exit`: Exits with status 0.
    -   `exit <num>`: Exits with status `<num>`.
    -   `exit <num> <arg>`: Prints an error and exits with status 2.
    -   `exit <arg1> <arg2> ...`: Prints a "too many arguments" error and does not exit; sets status to 1.

### 3. Redirection and Pipes

File descriptors are managed to redirect I/O and connect commands.

-   **Pipes:** For a command like `cmd1 | cmd2`, a pipe is created. `cmd1`'s standard output is redirected to the pipe's write-end, and `cmd2`'s standard input is redirected from the pipe's read-end.
-   **File Redirection:** Before execution, the token list is scanned for redirection operators. The shell opens the specified files and uses `dup2` to replace `STDIN_FILENO` or `STDOUT_FILENO` with the new file descriptors.
-   **Here-documents (`<<`):** The shell reads input from the user until a line containing only the specified delimiter is found. This input is typically stored in a temporary file, which then serves as the standard input for the command.

### 4. Command Execution

#### 4.1. Forking

A new process is created using `fork()` for every external command. The only exception is when a single command is a built-in, which is executed in the main shell process to allow it to modify the shell's state (e.g., `cd`, `export`, `exit`).

#### 4.2. Finding and Executing Commands

-   If a command starts with `./` or `/`, it is treated as an absolute or relative path.
-   Otherwise, the shell searches for the executable in the directories listed in the `PATH` environment variable.
-   The `access()` function is used to check if the file exists and is executable.
-   Once the command path is resolved, `execve()` is called in the child process to replace its memory space with the new program.

#### 4.3. Managing File Descriptors

In each forked child process:
1.  `dup2()` is used to redirect `stdin` and `stdout` to the correct file descriptors (from a pipe or a file).
2.  All unused file descriptors are closed to prevent resource leaks and hanging processes.
3.  The command is executed via `execve()`.

The parent process waits for all child processes to complete using `waitpid()` and closes its copies of the pipe file descriptors.

#### 4.4. Exit Status

The shell sets the exit status (`$?`) based on the outcome of the last executed command:
-   **0**: Success.
-   **1**: General error (e.g., failed built-in).
-   **2**: Syntax error during parsing.
-   **126**: Command found but not executable (permission denied).
-   **127**: Command not found.
-   **128 + N**: Command terminated by signal N.
