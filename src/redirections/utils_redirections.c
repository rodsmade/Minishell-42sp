/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 20:10:21 by roaraujo          #+#    #+#             */
/*   Updated: 2022/05/10 17:41:20 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	capture_inputs(t_command *cmd)
{
	t_list	*pivot;

	pivot = cmd->inputs;
	while (pivot)
	{
		check_file_exists((char *) pivot->content);
		check_file_has_permissions((char *) pivot->content, R_OK);
		if (!pivot->next)
		{
			cmd->input_fd = open((char *) pivot->content, O_RDONLY);
			dup2(cmd->input_fd, STDIN_FILENO);
		}
		pivot = pivot->next;
	}
	return ;
}

void	capture_outputs(t_command *cmd)
{
	if (cmd->outputs)
	{
		dup2(cmd->output_fd, STDOUT_FILENO);
	}
	return ;
}

void	capture_heredocs(t_command *cmd, int cmd_count)
{
	int			pipe_fds[2];
	t_data_hd	hd;
	int			pid;
	int			i;
	int			wstatus;

	init_heredoc_data(&hd, cmd, cmd_count);
	while (hd.cursor)
	{
		pid = pipe_and_fork(&pipe_fds);
		if (pid == 0)
			get_input_line(&hd, pipe_fds);
		waitpid(pid, &wstatus, 0);
		process_child_return_code(wstatus);
		close(pipe_fds[1]);
		hd.str = concat_pipe_content(hd.pipes_per_eof[hd.counter], hd.str);
		process_heredoc_position(&hd, pipe_fds[0]);
	}
	write(g_data.pipe_heredoc[1], hd.str, ft_strlen(hd.str));
	ft_free_ptr((void *)&(hd.str));
	i = -1;
	while (++i < hd.total_pipes)
		ft_free_ptr((void *)&hd.pipes_per_eof[i]);
	ft_free_ptr((void *)&(hd.pipes_per_eof));
	return ;
}

void	capture_o_concats(t_command *cmd)
{
	if (cmd->o_concats)
		dup2(cmd->o_concat_fd, STDOUT_FILENO);
	return ;
}
