/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrianofaus <adrianofaus@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 22:01:44 by roaraujo          #+#    #+#             */
/*   Updated: 2022/04/18 14:37:59 by adrianofaus      ###   ########.fr       */
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

typedef struct s_ext_routine
{
	char	*msg;
	int		code;
}		t_ext_routine;

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
	int		main_pl_size;
	t_list	*secondary_pipeline;
}				t_cmd_table;

typedef struct s_tudao
{
	char			*prompt_input;
	t_list			*hashtable[TABLE_SIZE];
	t_list			*token_list;
	t_cmd_table		command_table;
	int				**cmd_pipes;
	int				pipe_heredoc[2];
	int				is_forked;
	t_ext_routine	ext_routine;
	bool			syntax_error;
	bool			exit;
}				t_tudao;

typedef struct s_data_hd
{
	int		total_pipes;
	int		**aux_pipes;
	t_list	*cursor;
	char	*str;
	int		counter;
}				t_data_hd;

// ----------------------------------------------	GLOBAL VAR	----------------
extern t_tudao		g_tudao;

// ----------------------------------------------	PROTOTYPES	----------------
// builtin_cd.c
void			builtin_cd(t_list *path);

// builtin_echo.c
void			builtin_echo(t_list *lst);

// builtin_env.c
void			builtin_env(t_list *cmd_with_flags);

// builtin_exit.c
void			builtin_exit(void);

// builtin_export.c
void			builtin_export(t_list *lst);

// builtin_pwd.c
void			builtin_pwd(void);

// builtin_unset.c
void			builtin_unset(t_list *cmd_with_args);

// builtin_var_assignment.c
void			assign_vars(t_command *command);
bool			is_var_assignment(char *str);

// executor.c
void			execute_pipeline(t_list *pipeline);
void			execute_command(t_command *cmd);
void			capture_redirections(int cmd_counter, t_command *cmd);
void			execute_built_in(t_command *command);

// exit_routines.c
void			close_std_fds(void);
void			close_fds_by_cmd(t_command *command);
void			close_and_free_pipes(void);

// exit_routines_2.c
void			free_t_command_list(t_list *lst);
void			free_main_pipeline(t_list **pipeline);
void			free_and_exit_fork(char *err_msg);
void			free_env_var(void *element);
void			free_hashtable(t_list *(*hashtable)[TABLE_SIZE]);

// exit_routines_3.c
void			print_syntax_error_exit(char *token);
void			free_g_tudao(void);
void			print_error_and_exit(int ext_code, char *msg);
void			free_list(t_list *list);

// expansor.c
void			expand_tokens(t_list *token_list);

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

// utils_env_vars.c
char			*env_var_to_string(t_env_var *env_var);
int				count_env_vars(void);

// utils_executor.c
char			**assemble_cmd_array(t_command *command);
char			*find_cmd_in_path_var(char *command_str);
char			*find_cmd_path(char *command_str);

// utils_executor_2.c
void			process_executor(int total_pipes, int counter, t_command *cmd);
bool			execute_only_one_cmd(t_list *pipeline);
void			create_new_files(t_list *pipeline);
bool			alters_main_memory(char *built_in);

// utils_executor_3.c
bool			alters_main_memory(char *built_in);
bool			is_built_in(char *str);
bool			has_absolute_path(char *command_str);

// utils_expansor.c
void			remove_null_nodes_from_token_list(void);
char			*ft_append_char(char *str, char c);
int				is_valid_key_char(char c);
void			expand_wildcards(void);
void			append_single_quotes(char *token_str, char **expanded_cont,
					int *index);

// utils_expansor_2.c
void			substitute_token_by_sublist(char *expanded_str,
					t_list **token_address);
bool			is_expansible(char *token_content);
char			*treat_quotes(char *token_content);

// utils_export.c
int				value_len(char *line_read);
int				is_valid_identifier(char *key_value);
int				key_len(char *key_value);
void			print_exported_vars(void);
void			concat_and_free(char **pair, char *s1, char *s2, char *s3);

// utils_export_2.c
void			iter_quoted_value(char *line_read, int *i, char *value, int *j);

// utils_file_check.c
void			check_file_exists(char *file_name);
void			check_file_has_permissions(char *file_name, int permissions);

// utils_hashtable.c
void			update_hashtable(char *key, char *new_value, int new_env_var);
char			*read_hashtable(t_list *head, char *key);
t_list			*find_node_in_hashtable(char *var_name);
char			**hashtable_to_array(void);

// utils_hashtable_2.c
char			**split_key_and_value(char *string);

// utils_heredoc.c
void			init_heredoc_data(t_data_hd *hd, t_command *cmd, int cmd_count);
void			process_heredoc_position(t_data_hd *hd, int pipe_fd);
void			add_heredocs_to_history(void);

// utils_lexer.c
void			skip_quotes(char *line_read, int *index, int *token_len);
void			quoted_generate(char *line_read, int *index, char *content);
int				count_redirect(char *line_read);
void			redirect_gen(char *line_read, char *content);
void			free_lexer(void);

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

// utils_redirections.c
void			capture_inputs(t_command *cmd);
void			capture_outputs(t_command *cmd);
void			capture_heredocs(t_command *cmd, int cmd_count);
void			capture_o_concats(t_command *cmd);

// utils_redirections_2.c
char			*get_pipe_content(int fd);
char			*concat_pipe_content(int *pipe, char *str);
int				pipe_and_fork(int *pipe_fds);
void			get_input_line(t_data_hd *hd, int *pipe_fds);

// utils_test.c
void			print_hashtable(t_list *(*hashtable)[TABLE_SIZE]);
void			print_commands_and_redirects(void);
void			print_token_lst(t_list *lst);

#endif