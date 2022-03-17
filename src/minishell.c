/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaraujo <roaraujo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 21:30:44 by roaraujo          #+#    #+#             */
/*   Updated: 2022/03/17 18:49:10 by roaraujo         ###   ########.fr       */
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

void	assemble_line(char **line_read)
{
	char	*aux_str;
	char	*temp;

	aux_str = readline("> ");
	temp = aux_str;
	aux_str = ft_strjoin(" ", aux_str);
	free(temp);
	temp = (*line_read);
	(*line_read) = ft_strjoin((*line_read), aux_str);
	lexer_line(aux_str);
	parse_tokens();
	free(aux_str);
	free(temp);
}

void	repl(void)
{
	char	*line_read;

	init_tudao();
	line_read = NULL;
	while (1)
	{
		g_tudao.syntax_error = false;
		line_read = readline("Type yr command (type \'quit\' to exit): ");
		if (ft_strncmp(line_read, "quit", 5) == 0)
			break ;
		lexer_line(line_read);
		parse_tokens();
		while (g_tudao.token_list && !g_tudao.syntax_error
			&& is_pipe_and_or((char *) ft_lstlast(g_tudao.token_list)->content))
			assemble_line(&line_read);
		add_history(line_read);
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
