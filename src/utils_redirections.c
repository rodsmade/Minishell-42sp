/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaraujo <roaraujo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 20:10:21 by roaraujo          #+#    #+#             */
/*   Updated: 2022/04/06 22:47:05 by roaraujo         ###   ########.fr       */
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

void	capture_heredocs(t_command *cmd)
{
	t_list	*pivot;
	char	*line_read;
	int		pipe_fds[2];
	int		pid;
	int		wstatus;

	pivot = cmd->heredocs;
	while (pivot)
	{
		if (pipe(pipe_fds) == -1)
			free_and_exit_fork(ft_strdup("Error creating pipe for heredoc"));
		pid = fork();
		if (pid == -1)
			free_and_exit_fork(ft_strdup("Error forking process for heredoc"));
		if (pid == 0)
		{
			line_read = readline("> ");
			while (strncmp(line_read, (char *) pivot->content,
					sizeof((char *) pivot->content) + 1) != 0)
			{
				write(pipe_fds[1], line_read, ft_strlen(line_read));
				write(pipe_fds[1], "\n", 1);
				ft_free_ptr((void *)&line_read);
				line_read = readline("> ");
			}
			close(pipe_fds[0]);
			close(pipe_fds[1]);
			ft_free_ptr((void *)&line_read);
			free_and_exit_fork(NULL);
		}
		else
		{
			waitpid(pid, &wstatus, 0);
			close(pipe_fds[1]);
			if (!pivot->next)
				dup2(pipe_fds[0], STDIN_FILENO);
			else
				close(pipe_fds[0]);
		}
		pivot = pivot->next;
	}
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
