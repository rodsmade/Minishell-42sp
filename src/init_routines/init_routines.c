/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_routines.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 12:08:00 by roaraujo          #+#    #+#             */
/*   Updated: 2022/05/10 17:41:20 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_hashtable(t_list *(*hashtable)[TABLE_SIZE])
{
	int	i;

	i = -1;
	while (++i < TABLE_SIZE)
	{
		(*hashtable)[i] = NULL;
	}
	return ;
}

void	init_g_data(void)
{
	g_data.prompt_input = NULL;
	g_data.token_list = NULL;
	g_data.command_table.main_pipeline = NULL;
	g_data.command_table.secondary_pipeline = NULL;
	g_data.syntax_error = false;
	g_data.exit.flag = false;
	g_data.skip_execution = false;
	g_data.heredoc_stopped = false;
	g_data.is_ctrl_d = true;
	g_data.pipe_heredoc[0] = -1;
	g_data.pipe_heredoc[1] = -1;
	return ;
}

void	init_command(t_command *command)
{
	command->cmds_with_flags = NULL;
	command->inputs = NULL;
	command->outputs = NULL;
	command->heredocs = NULL;
	command->o_concats = NULL;
	command->err = NULL;
	command->input_fd = 0;
	command->output_fd = 0;
	command->heredoc_fd = 0;
	command->o_concat_fd = 0;
	command->err_fd = 0;
	return ;
}

void	init_core_variables(void)
{
	g_data.exit.flag = false;
	g_data.exit.code = 0;
	g_data.line_count = 0;
	g_data.backup_stdin = dup(STDIN_FILENO);
	g_data.home_at_start = ft_strdup(
			read_hashtable(g_data.hashtable[hash_string("HOME")], "HOME"));
	disable_signal(SIGQUIT, &g_data.action);
	disable_signal(SIGINT, &g_data.action);
}
