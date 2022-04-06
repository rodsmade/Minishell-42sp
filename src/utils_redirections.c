/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrianofaus <adrianofaus@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 20:10:21 by roaraujo          #+#    #+#             */
/*   Updated: 2022/04/06 20:44:51 by adrianofaus      ###   ########.fr       */
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
	// int		g_tudao.pipe_heredoc[2];
	// char	buffer[50];
	// char	*str;
	// char	*temp;
	// int		chars_read;
	int		pid;
	int		wstatus;

	pivot = cmd->heredocs;
	while (pivot)
	{
		if (pipe(pipe_fds) == -1)
			free_and_exit_fork(ft_strdup("Error creating pipe for heredoc"));
		// if (pipe(g_tudao.pipe_heredoc) == -1)
		// 	free_and_exit_fork(ft_strdup("Error creating auxiliar pipe for heredoc"));
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
				write(g_tudao.pipe_heredoc[1], line_read, ft_strlen(line_read));
				write(g_tudao.pipe_heredoc[1], "\n", 1);
				ft_free_ptr((void *)&line_read);
				line_read = readline("> ");
			}
			write(g_tudao.pipe_heredoc[1], line_read, ft_strlen(line_read));
			write(g_tudao.pipe_heredoc[1], "\n", 1);
			close(pipe_fds[0]);
			close(pipe_fds[1]);
			close(g_tudao.pipe_heredoc[0]);
			close(g_tudao.pipe_heredoc[1]);
			ft_free_ptr((void *)&line_read);
			free_and_exit_fork(NULL);
		}
		else
		{
			waitpid(pid, &wstatus, 0);
			close(pipe_fds[1]);
			close(g_tudao.pipe_heredoc[0]);
			close(g_tudao.pipe_heredoc[1]);
			// close(g_tudao.pipe_heredoc[1]);
			// chars_read = read(g_tudao.pipe_heredoc[0], buffer, 49);
			// buffer[chars_read] = '\0';
			// str = ft_strdup("");
			// while (chars_read > 0)
			// {
			// 	temp = str;
			// 	str = ft_strjoin(temp, buffer);
			// 	ft_free_ptr((void *)&temp);
			// 	chars_read = read(g_tudao.pipe_heredoc[0], buffer, 49);
			// 	buffer[chars_read] = '\0';
			// }
			// dprintf(2, "what's been read: >|%s|<\n", str);
			// add_history(str);
			// ft_free_ptr((void *)&str);
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
