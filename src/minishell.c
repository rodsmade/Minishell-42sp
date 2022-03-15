/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrianofaus <adrianofaus@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 21:30:44 by roaraujo          #+#    #+#             */
/*   Updated: 2022/03/15 13:40:22 by roaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

void	get_env_variables(char **envp)
{
	int			i;

	i = -1;
	init_hashtable(&g_tudao.hashtable);
	while (envp[++i])
	{
		insert_in_hashtable(envp[i], 1, &g_tudao.hashtable);
	}
	free_hashtable(&g_tudao.hashtable);
	return ;
}

void	repl(void)
{
	char	*line_read;

	init_tudao();
	line_read = NULL;
	while (1)
	{
		line_read = readline("Type yr command (type \'quit\' to exit): ");
		if (ft_strncmp(line_read, "quit", 5) == 0)
			break ;
		add_history(line_read);
		lexer_line(line_read);
		parse_tokens();
		if (line_read)
		{
			ft_free_ptr((void *)&line_read);
			free_lexer();
		}
	}
	ft_free_ptr((void *)&line_read);
	rl_clear_history();
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
