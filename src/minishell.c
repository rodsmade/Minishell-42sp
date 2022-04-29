/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaraujo <roaraujo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 21:30:44 by roaraujo          #+#    #+#             */
/*   Updated: 2022/04/29 02:47:20 by roaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tudao	g_tudao;

void	print_intro(void)
{
	int		fd;
	char	buff[1];

	fd = open("assets/intro.txt", O_RDONLY);
	if (fd == -1)
		return ;
	while (read(fd, buff, 1))
	{
		if (buff[0] == '1')
			printf(BLUE "█" COLOUR_RESET);
		else if (buff[0] == '2')
			printf(LILAC "█" COLOUR_RESET);
		else if (buff[0] == '3')
			printf(MAGENTA "█" COLOUR_RESET);
		else if (buff[0] == '4')
			printf(PURPLE "█" COLOUR_RESET);
		else if (buff[0] == 'y')
			printf(LYELLOWB " " COLOUR_RESET);
		else if (buff[0] == 'r')
			printf(REDB " " COLOUR_RESET);
		else
			printf("%c", buff[0]);
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

void	add_to_history(char *string)
{
	int	i;

	i = -1;
	if (!string)
		return ;
	while (string[++i])
	{
		if (!ft_is_blankspace(string[i]))
		{
			add_history(string);
			return ;
		}
	}
	return ;
}

void	repl(void)
{
	init_core_variables();
	while (!g_tudao.exit.flag)
	{
		init_g_tudao();
		display_cmd_prompt();
		set_up_command_table();
		if (g_tudao.prompt_input && g_tudao.token_list
			&& g_tudao.token_list->content && !g_tudao.syntax_error
			&& !g_tudao.exit.flag && !g_tudao.skip_execution)
			execute_pipeline(g_tudao.command_table.main_pipeline);
		add_heredocs_to_history();
		add_to_history(g_tudao.prompt_input);
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
