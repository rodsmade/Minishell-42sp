/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redirections2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrianofaus <adrianofaus@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 17:25:06 by adrianofaus       #+#    #+#             */
/*   Updated: 2022/04/07 21:52:54 by adrianofaus      ###   ########.fr       */
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

void	process_heredoc_position(t_data_hd *hd, int pipe_fd)
{
	if (!hd->cursor->next)
		dup2(pipe_fd, STDIN_FILENO);
	else
		close(pipe_fd);
	hd->cursor = hd->cursor->next;
	hd->counter++;
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

void	init_heredoc_data(t_data_hd *hd, t_command *cmd)
{
	hd->total_pipes = ft_lst_size(((t_command *) \
	g_tudao.command_table.main_pipeline->content)->heredocs);
	hd->aux_pipes = ft_make_pipes(hd->total_pipes);
	hd->cursor = cmd->heredocs;
	hd->str = ft_strdup("");
	hd->counter = 0;
}
