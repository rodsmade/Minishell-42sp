/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_routines_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 12:07:45 by roaraujo          #+#    #+#             */
/*   Updated: 2022/05/10 17:41:20 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_std_fds(void)
{
	close(0);
	close(1);
	close(2);
	close(g_data.backup_stdin);
	return ;
}

void	close_fds(t_command *command)
{
	if (command->input_fd)
		close(command->input_fd);
	if (command->output_fd)
		close(command->output_fd);
	if (command->heredoc_fd)
		close(command->heredoc_fd);
	if (command->o_concat_fd)
		close(command->o_concat_fd);
	if (command->err_fd)
		close(command->err_fd);
	return ;
}

void	close_heredoc_pipe(void)
{
	close(g_data.pipe_heredoc[0]);
	close(g_data.pipe_heredoc[1]);
	return ;
}

void	close_and_free_cmd_pipes(void)
{
	int	i;

	if (!g_data.cmd_pipes)
		return ;
	i = -1;
	while (++i < ft_lst_size(g_data.command_table.main_pipeline) - 1)
	{
		close(g_data.cmd_pipes[i][0]);
		close(g_data.cmd_pipes[i][1]);
		free(g_data.cmd_pipes[i]);
	}
	free(g_data.cmd_pipes);
	return ;
}
