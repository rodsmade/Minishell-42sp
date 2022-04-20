/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrianofaus <adrianofaus@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 21:30:44 by roaraujo          #+#    #+#             */
/*   Updated: 2022/04/20 19:11:47 by adrianofaus      ###   ########.fr       */
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

void	repl(void)
{
	g_tudao.exit = false;
	g_tudao.ext_routine.code = 0;
	g_tudao.line_count = 0;
	g_tudao.backup_stdin = dup(STDIN_FILENO);
	while (!g_tudao.exit)
	{
		init_tudao();
		display_cmd_prompt();
		if (g_tudao.prompt_input && g_tudao.token_list
			&& g_tudao.token_list->content && !g_tudao.syntax_error
			&& !g_tudao.exit && !g_tudao.skip_execution)
			execute_pipeline(g_tudao.command_table.main_pipeline);
		free_lexer();
		free_main_pipeline(&g_tudao.command_table.main_pipeline);
		add_heredocs_to_history();
		add_history(g_tudao.prompt_input);
		ft_free_ptr((void *)&g_tudao.prompt_input);
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
	free_g_tudao();
	return (g_tudao.ext_routine.code);
}
