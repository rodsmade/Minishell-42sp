/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redirections_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaraujo <roaraujo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 17:25:06 by adrianofaus       #+#    #+#             */
/*   Updated: 2022/04/08 17:29:23 by roaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_pipe_content(int fd)
{
	char	*temp;
	char	buffer[50];
	char	*str;
	int		chars_read;

	chars_read = read(fd, buffer, 49);
	str = ft_strdup("");
	while (chars_read > 0)
	{
		buffer[chars_read] = '\0';
		temp = str;
		str = ft_strjoin(temp, buffer);
		ft_free_ptr((void *)&temp);
		chars_read = read(fd, buffer, 49);
	}
	return (str);
}

char	*concat_pipe_content(int *pipe, char *str)
{
	char	*pipe_content;
	char	*aux;
	char	*new_str;

	close(pipe[1]);
	aux = str;
	pipe_content = get_pipe_content(pipe[0]);
	close(pipe[0]);
	new_str = ft_strjoin(aux, pipe_content);
	ft_free_ptr((void *)&aux);
	ft_free_ptr((void *)&pipe_content);
	return (new_str);
}

int	pipe_and_fork(int *pipe_fds)
{
	int	pid;

	if (pipe(pipe_fds) == -1)
		free_and_exit_fork(ft_strdup("Error creating pipe for heredoc"));
	pid = fork();
	if (pid == -1)
		free_and_exit_fork(ft_strdup("Error forking process for heredoc"));
	return (pid);
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
