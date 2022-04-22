/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_executor_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 17:25:38 by adrianofaus       #+#    #+#             */
/*   Updated: 2022/04/22 20:49:32 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fork_and_execute_cmd(int total_pipes, int counter, t_command *cmd)
{
	int	pid;
	int	wstatus;

	disable_signal(SIGQUIT, &g_tudao.action);
	disable_signal(SIGINT, &g_tudao.action);
	pid = fork();
	if (pid == -1)
		print_error_and_exit(1, ft_strdup("Error: forking executor"));
	else if (pid == 0)
	{
		set_signal_hook(SIGQUIT, catch_signals_child, &g_tudao.action);
		set_signal_hook(SIGINT, catch_signals_child, &g_tudao.action);
		capture_redirections(counter, cmd);
		execute_command(cmd);
	}
	else
	{
		waitpid(pid, &wstatus, WNOHANG);
		process_child_return_code(wstatus);
		if (counter != total_pipes)
			close(g_tudao.cmd_pipes[counter][1]);
	}
}

bool	execute_only_one_cmd(t_list *pipeline)
{
	t_command	*cmd;

	cmd = (t_command *) pipeline->content;
	if (pipeline && !pipeline->next && cmd->cmds_with_flags
		&& is_built_in((char *)cmd->cmds_with_flags->content)
		&& alters_main_memory((char *)cmd->cmds_with_flags->content))
	{
		execute_built_in(cmd);
		close_fds(cmd);
		if (g_tudao.exit.msg)
		{
			ft_putendl_fd(g_tudao.exit.msg, 2);
			ft_free_ptr((void *)&g_tudao.exit.msg);
		}
		return (true);
	}	
	return (false);
}

void	create_outputs(t_command *cmd)
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
			else
				cmd->output_fd = fd;
		}
		pivot = pivot->next;
	}
	return ;
}

void	create_o_concats(t_command *cmd)
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
			else
				cmd->o_concat_fd = fd;
		}
		pivot = pivot->next;
	}
	return ;
}

void	create_new_files(t_list *pipeline)
{
	t_command	*cmd;
	t_list		*pivot;

	pivot = pipeline;
	while (pivot)
	{
		cmd = ((t_command *)pivot->content);
		create_outputs(cmd);
		create_o_concats(cmd);
		pivot = pivot->next;
	}
	return ;
}
