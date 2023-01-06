# Minishell-42sp

This is a minified Bash-like shell!

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
