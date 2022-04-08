/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrianofaus <adrianofaus@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 20:10:21 by roaraujo          #+#    #+#             */
/*   Updated: 2022/04/07 21:42:43 by adrianofaus      ###   ########.fr       */
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
			dup2(cmd->output_fd, STDOUT_FILENO);
		}
		pivot = pivot->next;
	}
	return ;
}

void	get_input_line(t_data_hd *hd, int *pipe_fds)
{
	char	*line_read;
	char	*eof;

	eof = (char *) hd->cursor->content;
	line_read = readline("> ");
	while (ft_strncmp(line_read, eof, sizeof(eof) + 1) != 0)
	{
		ft_putendl_fd(line_read, pipe_fds[1]);
		ft_putendl_fd(line_read, hd->aux_pipes[hd->counter][1]);
		ft_free_ptr((void *)&line_read);
		line_read = readline("> ");
	}
	ft_putendl_fd(line_read, hd->aux_pipes[hd->counter][1]);
	ft_free_ptr((void *)&line_read);
	ft_close_pipe_fds(pipe_fds);
	ft_free_ptr((void *)&(hd->str));
	ft_free_pipe_arr(&(hd->aux_pipes), hd->total_pipes);
	ft_close_pipe_fds(g_tudao.pipe_heredoc);
	free_and_exit_fork(NULL);
}

void	capture_heredocs(t_command *cmd)
{
	int			pipe_fds[2];
	t_data_hd	hd;
	int			pid;

	init_heredoc_data(&hd, cmd);
	while (hd.cursor)
	{
		pid = pipe_and_fork(pipe_fds);
		if (pid == 0)
			get_input_line(&hd, pipe_fds);
		waitpid(pid, NULL, 0);
		close(pipe_fds[1]);
		hd.str = concat_pipe_content(hd.aux_pipes[hd.counter], hd.str);
		process_heredoc_position(&hd, pipe_fds[0]);
	}
	write(g_tudao.pipe_heredoc[1], hd.str, ft_strlen(hd.str));
	ft_free_ptr((void *)&(hd.str));
	ft_free_ptr((void *)&(hd.aux_pipes));
	return ;
}

void	capture_o_concats(t_command *cmd)
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
			dup2(cmd->o_concat_fd, STDOUT_FILENO);
		}
		pivot = pivot->next;
	}
	return ;
}
