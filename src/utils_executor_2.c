/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_executor_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrianofaus <adrianofaus@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 17:25:38 by adrianofaus       #+#    #+#             */
/*   Updated: 2022/04/08 18:48:19 by adrianofaus      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_executor(int total_pipes, int counter, t_command *cmd)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		ft_putendl_fd("Error while forking", 2);
	else if (pid == 0)
	{
		capture_redirections(counter, cmd);
		execute_command(cmd);
	}
	else
	{
		waitpid(pid, NULL, 0);
		if (counter != total_pipes)
			close(g_tudao.cmd_pipes[counter][1]);
	}
}

bool	execute_only_one_cmd(void)
{
	t_list		*cmd_pivot;
	t_command	*cmd;

	cmd_pivot = g_tudao.command_table.main_pipeline;
	cmd = (t_command *) cmd_pivot->content;
	if (!cmd_pivot->next && is_built_in((char *)cmd->cmds_with_flags->content))
	{
		capture_redirections(0, cmd);
		execute_built_in(cmd);
		return (true);
	}	
	return (false);
}
