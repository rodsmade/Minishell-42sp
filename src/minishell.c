/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaraujo <roaraujo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 21:30:44 by roaraujo          #+#    #+#             */
/*   Updated: 2022/03/29 18:29:17 by roaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

t_tudao	g_tudao;

void	get_env_variables(char **envp)
{
	int			i;

	i = -1;
	init_hashtable(&g_tudao.hashtable);
	while (envp[++i])
		insert_in_hashtable(envp[i], 1, &g_tudao.hashtable);
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
	expand_tokens();
	parse_tokens();
	free(aux_str);
	free(temp);
}

char	*display_cmd_prompt(void)
{
	char	*line_read;
	char	*curr_path;
	char	*prompt;

	curr_path = getcwd(NULL, 0);
	prompt = ft_strjoin(curr_path, " $ ");
	line_read = readline(prompt);
	if (ft_strncmp(line_read, "quit", 5) == 0)
	{
		g_tudao.exit = true;
		ft_free_ptr((void *)&prompt);
		ft_free_ptr((void *)&curr_path);
		return (line_read);
	}
	lexer_line(line_read);
	expand_tokens();
	parse_tokens();
	while (g_tudao.token_list && !g_tudao.syntax_error
		&& is_pipe_and_or((char *) ft_lstlast(g_tudao.token_list)->content))
		assemble_line(&line_read);
	ft_free_ptr((void *)&curr_path);
	ft_free_ptr((void *)&prompt);
	return (line_read);
}

void	repl(void)
{
	char	*line_read;

	line_read = NULL;
	g_tudao.exit = false;
	while (!g_tudao.exit)
	{
		init_tudao();
		line_read = display_cmd_prompt();
		if (line_read && g_tudao.token_list && g_tudao.token_list->content
			&& !g_tudao.syntax_error && !g_tudao.exit)
			execute_pipelines();
		add_history(line_read);
		free_lexer();
		free_main_pipeline();
		ft_free_ptr((void *)&line_read);
	}
	free_hashtable(&g_tudao.hashtable);
	ft_free_ptr((void *)&line_read);
	free_hashtable(&g_tudao.hashtable);
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
	close_fds();
	return (0);
}
