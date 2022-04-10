/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_routines.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaraujo <roaraujo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 12:07:45 by roaraujo          #+#    #+#             */
/*   Updated: 2022/04/10 17:22:22 by roaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_std_fds(void)
{
	close(0);
	close(1);
	close(2);
	return ;
}

void	close_fds_by_cmd(t_command *command)
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

void	close_and_free_pipes(void)
{
	int	i;

	if (!g_tudao.cmd_pipes)
		return ;
	i = -1;
	while (++i < ft_lst_size(g_tudao.command_table.main_pipeline) - 1)
	{
		close(g_tudao.cmd_pipes[i][0]);
		close(g_tudao.cmd_pipes[i][1]);
		free(g_tudao.cmd_pipes[i]);
	}
	free(g_tudao.cmd_pipes);
	return ;
}
