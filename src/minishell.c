/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrianofaus <adrianofaus@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 21:30:44 by roaraujo          #+#    #+#             */
/*   Updated: 2022/03/08 12:06:00 by adrianofaus      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

void	insert_in_hastable(char *current_variable)
{
	//Função que vai inserir dentro da hash
	//Criar função hash
}

void	get_env_variables(char **envp)
{
	int		i;

	i = -1;
	while (envp[++i])
	{
		insert_in_hashtable(envp[i]);
	}
}

int	main(int argc, char *argv[], char **envp)
{
	char	*line_read;

	(void)argv;
	line_read = NULL;
	if (argc != 1)
		return (1);
	write(1, "Hello World !\n", 14);
	get_env_variables(envp);
	while (1)
	{
		if (line_read)
			ft_free_ptr((void *)&line_read);
		line_read = readline("Type yr command (type \'quit\' to exit): ");
		add_history(line_read);
		if (ft_strncmp(line_read, "quit", 5) == 0)
			break ;
	}
	ft_free_ptr((void *)&line_read);
	rl_clear_history();
	close(0);
	close(1);
	close(2);
	return (0);
}
