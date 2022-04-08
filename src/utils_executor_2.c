/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_executor_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrianofaus <adrianofaus@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 17:25:38 by adrianofaus       #+#    #+#             */
/*   Updated: 2022/04/08 19:29:05 by adrianofaus      ###   ########.fr       */
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

void	create_outputs(t_command * cmd)
{
	t_list	*pivot;
	int		fd;
	
	pivot = cmd->outputs;
	while (pivot)
	{
		if (access((char *) pivot->content, F_OK) == -1)
		{
			fd = open((char *) pivot->content, O_CREAT | O_WRONLY | O_TRUNC,
					S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
			if (pivot->next)
				close(fd);
		}
		check_file_has_permissions((char *) pivot->content, W_OK);
		if (!pivot->next)
		{
			cmd->output_fd = open((char *) pivot->content,
					O_CREAT | O_WRONLY | O_TRUNC,
					S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
		}
		pivot = pivot->next;
	}
	return ;
}

void	create_o_concats(t_command * cmd)
{
	t_list	*pivot;
	int		fd;

	pivot = cmd->o_concats;
	while (pivot)
	{
		if (access((char *) pivot->content, F_OK) == -1)
		{
			fd = open((char *) pivot->content, O_CREAT | O_WRONLY | O_APPEND,
					S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
			if (pivot->next)
				close(fd);
		}
		check_file_has_permissions((char *) pivot->content, W_OK);
		if (!pivot->next)
		{
			cmd->o_concat_fd = open((char *) pivot->content,
					O_CREAT | O_WRONLY | O_APPEND,
					S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
		}
		pivot = pivot->next;
	}
	return ;	
}

void	create_new_files(void)
{
	t_command	*cmd;
	t_list		*pivot;

	pivot = g_tudao.command_table.main_pipeline;
	cmd = ((t_command *)pivot->content);
	while (pivot)
	{
		create_outputs(cmd);
		create_o_concats(cmd);
		pivot = pivot->next;
	}
	return ;
}