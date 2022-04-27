/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaraujo <roaraujo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 21:30:44 by roaraujo          #+#    #+#             */
/*   Updated: 2022/04/27 04:26:24 by roaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

t_tudao	g_tudao;

void	print_intro(void)
{
	int		fd;
	int		chars_read;
	char	buff[50];

	fd = open("assets/intro.txt", O_RDONLY);
	if (fd == -1)
		return ;
	chars_read = read(fd, buff, 49);
	buff[chars_read] = '\0';
	while (chars_read)
	{
		ft_putstr_fd(buff, 1);
		chars_read = read(fd, buff, 49);
		buff[chars_read] = '\0';
	}
	close(fd);
	return ;
}

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
	g_tudao.exit.flag = false;
	g_tudao.exit.code = 0;
	g_tudao.line_count = 0;
	g_tudao.backup_stdin = dup(STDIN_FILENO);
	while (!g_tudao.exit.flag)
	{
		init_tudao();
		display_cmd_prompt();
		set_up_command_table();
		if (g_tudao.prompt_input && g_tudao.token_list
			&& g_tudao.token_list->content && !g_tudao.syntax_error
			&& !g_tudao.exit.flag && !g_tudao.skip_execution)
			execute_pipeline(g_tudao.command_table.main_pipeline);
		add_heredocs_to_history();
		add_history(g_tudao.prompt_input);
		free_lexer();
		free_main_pipeline(&g_tudao.command_table.main_pipeline);
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
	print_intro();
	get_env_variables(envp);
	repl();
	free_g_tudao();
	return (g_tudao.exit.code);
}
