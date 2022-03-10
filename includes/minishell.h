/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaraujo <roaraujo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 22:01:44 by roaraujo          #+#    #+#             */
/*   Updated: 2022/03/10 14:53:28 by roaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// ---------------------------------------------	INCLUDES	----------------
# include <readline/readline.h>	// readline(), etc.
# include <readline/history.h>	// add_history()
# include <unistd.h>	// write(), close()
# include <stdlib.h>	// free()
# include "libft.h"

// ----------------------------------------------	DEFINES		----------------
# define TABLE_SIZE 50

// ----------------------------------------------	STRUCTS		----------------
typedef struct s_env_var
{
	char				*name;
	char				*value;
	int					is_env_var;
}				t_env_var;

// ----------------------------------------------	PROTOTYPES	----------------
// exit_routines.c
void	free_env_var(void *element);
void	free_hashtable(t_list *(*hashtable)[TABLE_SIZE]);

// hashtable.c
void	insert_in_hashtable(char *string, int is_env_var,
			t_list *(*hashtable)[TABLE_SIZE]);

// init_routines.c
void	init_hashtable(t_list *(*hashtable)[TABLE_SIZE]);

// utils_test.c
void	print_hashtable(t_list *(*hashtable)[TABLE_SIZE]);

#endif