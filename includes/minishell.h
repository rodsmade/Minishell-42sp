/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaraujo <roaraujo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 22:01:44 by roaraujo          #+#    #+#             */
/*   Updated: 2022/04/06 17:26:23 by roaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// ---------------------------------------------	INCLUDES	----------------
# include <readline/readline.h>	// readline(), etc.
# include <readline/history.h>	// add_history()
# include <unistd.h>			// write(), close(), access(), fork(), pipe()
# include <stdlib.h>			// free()
# include <stdbool.h>			// C99+ standard <bool> typedef
# include <fcntl.h>				// open()
# include <dirent.h>			// opendir(), closedir(), readdir()
# include <sys/stat.h>			// stat(), fstat(), lstat()
# include <sys/types.h>			// stat(), fstat(), lstat()
# include <stdarg.h>			// variadic functions concat() and free()
# include <sys/types.h>			// <pid_t> typedef
# include <sys/wait.h>			// wait()
# include "libft.h"

// ----------------------------------------------	DEFINES		----------------
# define TABLE_SIZE	50

// ----------------------------------------------	STRUCTS		----------------
typedef struct s_env_var
{
	char				*key;
	char				*value;
	int					is_env_var;
}				t_env_var;

typedef struct s_command
{
	t_list	*cmds_with_flags;
	t_list	*inputs;
	t_list	*outputs;
	t_list	*heredocs;
	t_list	*o_concats;
	t_list	*err;
	int		input_fd;
	int		output_fd;
	int		heredoc_fd;
	int		o_concat_fd;
	int		err_fd;
}				t_command;

typedef struct s_cmd_table
{
	t_list	*main_pipeline;
	t_list	*secondary_pipeline;
}				t_cmd_table;

typedef struct s_tudao
{
	char			*prompt_input;
	t_list			*hashtable[TABLE_SIZE];
	t_list			*token_list;
	t_cmd_table		command_table;
	int				**pipes;
	int				return_code;
	bool			syntax_error;
	bool			exit;
}				t_tudao;

// ----------------------------------------------	GLOBAL VAR	----------------
extern t_tudao		g_tudao;

// ----------------------------------------------	PROTOTYPES	----------------
// builtin_cd.c
void			builtin_cd(t_list *path);

// builtin_echo.c
void			builtin_echo(t_list *lst);

// builtin_env.c
void			builtin_env(void);

// builtin_exit.c
void			builtin_exit(void);

//builtin_export.c
void			builtin_export(t_list *lst);

// builtin_pwd.c
void			builtin_pwd(void);

// builtin_unset.c
void			builtin_unset(t_list *cmd_with_args);

// builtin_var_assignment.c
void			assign_vars(t_command *command);
bool			is_var_assignment(char *str);

// executor.c
void			execute_main_pipeline(void);

// exit_routines.c
void			free_env_var(void *element);
void			free_hashtable(t_list *(*hashtable)[TABLE_SIZE]);
void			print_syntax_error_exit(char *token);
void			close_fds(void);
void			free_g_tudao(void);

// exit_routines_2.c
void			free_t_command_list(t_list *lst);
void			free_t_command(t_command *cmd);
void			free_main_pipeline(void);
void			close_and_free_pipes(void);
void			free_and_exit_fork(char *err_msg);

// expansor.c
void			expand_tokens(void);

// hashtable.c
void			insert_in_hashtable(char *string, int is_env_var,
					t_list *(*hashtable)[TABLE_SIZE]);
int				hash_string(char *str);
void			insert_or_update_hashtable(char *string, int is_env_var,
					t_list *(*hashtable)[TABLE_SIZE]);

// init_routines.c
void			init_hashtable(t_list *(*hashtable)[TABLE_SIZE]);
void			init_tudao(void);
void			init_command(t_command *command);

// lexer.c
void			lexer_line(char	*line_read);

// parser.c
void			parse_tokens(void);

// utils_expansor.c
void			remove_null_nodes_from_token_list(void);
char			*ft_append_char(char *str, char c);
int				is_valid_key_char(char c);
void			expand_wildcards(void);

// utils_lexer.c
void			skip_quotes(char *line_read, int *index);
void			quoted_generate(char *line_read, int *index, char *content);
int				count_redirect(char *line_read);
void			redirect_gen(char *line_read, char *content);
void			free_lexer(void);

// utils_lexer_mock.c
void			print_list_so_far(void);
void			mock_tokens(void);
void			free_mock(void);

// utils_parser.c
bool			is_special_token(char *token);
bool			is_redirect(char *token);
bool			is_pipe(char *token);
bool			is_and_or(char *token);
bool			is_pipe_and_or(char *token);

// utils_parser_2.c
bool			is_input(t_list *token);
bool			is_output(t_list *token);
bool			is_heredoc(t_list *token);
bool			is_o_concat(t_list *token);

// utils_test.c
void			print_hashtable(t_list *(*hashtable)[TABLE_SIZE]);
void			print_commands_and_redirects(void);

//utils_hashtable.c
void			update_hashtable(char *key, char *new_value, int new_env_var);
char			*read_hashtable(t_list *head, char *key);
t_list			*find_node_in_hashtable(char *var_name);

//utils_export.c
int				value_len(char *line_read);
int				check_key(char *key_value);
int				key_len(char *key_value);
void			print_exported_vars(void);
void			concat_and_free(char **pair, char *s1, char *s2, char *s3);

//utils_export_2.c
void			iter_quoted_value(char *line_read, int *i, char *value, int *j);

#endif