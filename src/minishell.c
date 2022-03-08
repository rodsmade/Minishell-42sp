/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrianofaus <adrianofaus@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 21:30:44 by roaraujo          #+#    #+#             */
/*   Updated: 2022/03/08 12:53:49 by adrianofaus      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

# define	TABLE_SIZE	50

typedef struct s_env_var
{
	char				*name;
	char				*content;
	struct s_env_var	*next;
}				t_env_var;

void	repl(void)
{
	char	*line_read;

	line_read = NULL;
	while (1)
	{
		line_read = readline("Type yr command (type \'quit\' to exit): ");
		add_history(line_read);
		if (ft_strncmp(line_read, "quit", 5) == 0)
			break ;
		if (line_read)
			ft_free_ptr((void *)&line_read);
	}
	ft_free_ptr((void *)&line_read);
	rl_clear_history();
	return ;
}

void	insert_in_hashtable(char *current_variable, t_env_var *(*hashtable)[TABLE_SIZE])
{
	//Função que vai inserir dentro da hash
	//Criar função hash
	(void) current_variable;
}

void	init_hashtable(t_env_var *(*hashtable)[TABLE_SIZE])
{
	int	i;

	i = -1;
	while (++i < TABLE_SIZE)
	{
		(*hashtable)[i] = NULL;
	}
	return ;
}

void	print_hashtable(t_env_var *(*hashtable)[TABLE_SIZE])
{
	int	i;

	i = -1;
	while (++i < TABLE_SIZE)
	{
		printf(">: Position %d - %p\n", i, (*hashtable)[i]);
	}
	return ;
}

void	get_env_variables(char **envp)
{
	int			i;
	t_env_var	*hashtable[TABLE_SIZE];

	i = -1;
	init_hashtable(&hashtable);
	print_hashtable(&hashtable);
	while (envp[++i])
	{
		insert_in_hashtable(envp[i], &hashtable);
	}
	return ;
}

int	main(int argc, char *argv[], char **envp)
{
	(void)argv;
	(void)envp;
	if (argc != 1)
		return (1);
	write(1, "Hello World !\n", 14);
	get_env_variables(envp);
	repl();
	close(0);
	close(1);
	close(2);
	return (0);
}
