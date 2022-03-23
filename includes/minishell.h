/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 22:01:44 by roaraujo          #+#    #+#             */
/*   Updated: 2022/03/23 01:45:32 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// ---------------------------------------------	INCLUDES	----------------
# include <readline/readline.h>	// readline(), etc.
# include <readline/history.h>	// add_history()
# include <unistd.h>	// write(), close()
# include <stdlib.h>	// free()
# include <stdbool.h>	// C99+ standard bool typedef
# include "libft.h"

// ----------------------------------------------	DEFINES		----------------
# define TABLE_SIZE	50

// ----------------------------------------------	STRUCTS		----------------
typedef struct s_env_var
{
	char				*name;
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
}				t_command;

typedef struct s_cmd_table
{
	t_list	*main_pipeline;
	t_list	*secondary_pipeline;
}				t_cmd_table;

typedef struct s_tudao
{
	t_list			*hashtable[TABLE_SIZE];
	t_list			*token_list;
	t_cmd_table		command_table;
	int				return_code;
	bool			syntax_error;
}				t_tudao;

// ----------------------------------------------	GLOBAL VAR	----------------
extern t_tudao		g_tudao;

// ----------------------------------------------	PROTOTYPES	----------------
// executor.c
void			execute_pipelines(void);

// exit_routines.c
void			free_env_var(void *element);
void			free_hashtable(t_list *(*hashtable)[TABLE_SIZE]);
void			free_main_pipeline(void);
void			print_syntax_error_exit(char *token);

// exit_routines.c
void			free_t_command_list(t_list *lst);
void			free_t_command(t_command *cmd);
void			free_main_pipeline(void);
void			close_fds(void);

// hashtable.c
void			insert_in_hashtable(char *string, int is_env_var,
					t_list *(*hashtable)[TABLE_SIZE]);

// init_routines.c
void			init_hashtable(t_list *(*hashtable)[TABLE_SIZE]);
void			init_tudao(void);
void			init_command(t_command *command);

// lexer.c
void			lexer_line(char	*line_read);

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

// parser.c
void			parse_tokens(void);

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

#endif