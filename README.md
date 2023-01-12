# Minishell-42sp

This is a minified Bash-like shell!

*GIF*

In this projects, students are tasked with building a program that executes in a loop*, prompting the user for a command (or sequence of commands**), interpreting the inserted input and then executing the command, finally returning the prompt back to the user, until it is terminated via the `exit` command or the file descriptor `STD_IN` is closed (via `ctrl+D`).

> *Commonly referred to as REPL - Read, Evaluate and Print Loop. This diagram 
> **Also know as `pipelines`, that is, a sequence of terminal commands separated by the pipe character `|`.

## Features

- **Redirection operatores** `>` (redirected output), `<` (redirected input), `>>` (append redirected output), and `<<` (heredoc);
- Basic built-ins for **navigation in the directory tree** (`pwd`, `cd`);
- Basic built-ins for **environment variables manipulation** (`env`, `export`, `unset`);
- Basic builtiins for **printing** on the terminal and **exiting** the shell (`echo`, `exit`);
- Parsing of **double quotes** and **single quotes** (`""` and `''`);
- Environment variable **expansion** (`$`);
- Execution of command via `$PATH`;
- Execution of command via **relative/absolute paths**;
- Execution of **pipelines** (sequential commands separated by `|`);
- :star: **Wildcards** (`*`);


## Download and use this project

``` shell
$> git clone https://github.com/rodsmade/Minishell-42sp.git
$> cd Minishell-42sp
$> make
$> ./minishell
```

If you want to exit the minishell, simply type in the command `exit` or press `Ctrl+D`. There ya go!

## Final note
If you're a 42 student struggling to understand this project, I got your back! Please refer to this Notion page that I wrote covering the general concepts related to this project! It's in Portuguese :cactus:

> [Acelera — Minishell](https://rodsmade.notion.site/Acelera-Minishell-f6c3f8463e3e4580b4e61f4886036faf)
