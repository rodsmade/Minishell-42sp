/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaraujo <roaraujo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 21:30:44 by roaraujo          #+#    #+#             */
/*   Updated: 2022/03/08 12:35:10 by roaraujo         ###   ########.fr       */
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

void	insert_in_hashtable(char *current_variable)
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
		*hashtable[i] = NULL;
	}
	return ;
}

void	get_env_variables(char **envp)
{
	int			i;
	t_env_var	*hashtable[TABLE_SIZE];

	i = -1;
	init_hashtable(&hashtable);
	while (envp[++i])
	{
		insert_in_hashtable(envp[i]);
	}
	return ;
}

int	main(int argc, char *argv[], char **envp)
{
	(void)argv;
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
