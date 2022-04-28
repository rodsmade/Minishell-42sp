/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_routines.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaraujo <roaraujo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 12:08:00 by roaraujo          #+#    #+#             */
/*   Updated: 2022/04/25 19:28:10 by roaraujo         ###   ########.fr       */
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

void	init_tudao(void)
{
	g_tudao.prompt_input = NULL;
	g_tudao.token_list = NULL;
	g_tudao.command_table.main_pipeline = NULL;
	g_tudao.command_table.secondary_pipeline = NULL;
	g_tudao.syntax_error = false;
	g_tudao.exit.flag = false;
	g_tudao.skip_execution = false;
	g_tudao.is_ctrl_d = true;
	g_tudao.pipe_heredoc[0] = -1;
	g_tudao.pipe_heredoc[1] = -1;
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
