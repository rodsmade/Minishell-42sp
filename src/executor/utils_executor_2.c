/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_executor_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 17:25:38 by adrianofaus       #+#    #+#             */
/*   Updated: 2022/05/10 17:41:20 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fork_and_execute_cmd(pid_t **pids, t_list *pipeline)
{
	t_list		*cmd_pivot;
	t_command	*cmd;
	int			i;

	cmd_pivot = pipeline;
	disable_signal(SIGQUIT, &g_data.action);
	disable_signal(SIGINT, &g_data.action);
	*pids = malloc (g_data.command_table.main_pl_size * sizeof(**pids));
	i = -1;
	while (cmd_pivot)
	{
		cmd = (t_command *) cmd_pivot->content;
		(*pids)[++i] = fork();
		if ((*pids)[i] == -1)
			print_error_and_exit(1, ft_strdup("Error: forking executor"));
		else if ((*pids)[i] == 0)
		{
			set_signal_hook(SIGQUIT, sighandler_child, &g_data.action);
			set_signal_hook(SIGINT, sighandler_child, &g_data.action);
			capture_redirections(i, cmd);
			execute_command(cmd);
		}
		close_fds(cmd);
		cmd_pivot = cmd_pivot->next;
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
		if (g_data.exit.msg)
		{
			ft_putstr_fd(BRED "✘ minishell: " COLOUR_RESET, 2);
			ft_putendl_fd(g_data.exit.msg, 2);
			ft_free_ptr((void *)&g_data.exit.msg);
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
		fd = open((char *) pivot->content, O_CREAT | O_RDWR | O_TRUNC,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
		if (pivot->next)
			close(fd);
		else
			cmd->output_fd = fd;
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
		fd = open((char *) pivot->content, O_CREAT | O_RDWR | O_APPEND,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
		if (pivot->next)
			close(fd);
		else
			cmd->o_concat_fd = fd;
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
