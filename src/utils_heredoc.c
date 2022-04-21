/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaraujo <roaraujo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 17:27:16 by roaraujo          #+#    #+#             */
/*   Updated: 2022/04/22 00:18:16 by roaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_heredoc_data(t_data_hd *hd, t_command *cmd, int cmd_count)
{
	hd->total_pipes = ft_lst_size(cmd->heredocs);
	hd->aux_pipes = ft_make_pipes(hd->total_pipes);
	hd->cursor = cmd->heredocs;
	if (cmd_count == 0)
		hd->str = ft_strdup("\n");
	else
		hd->str = ft_strdup("");
	hd->counter = 0;
}

void	process_heredoc_position(t_data_hd *hd, int pipe_fd)
{
	if (!hd->cursor->next)
		dup2(pipe_fd, STDIN_FILENO);
	close(pipe_fd);
	hd->cursor = hd->cursor->next;
	hd->counter++;
}

void	add_heredocs_to_history(void)
{
	char	*str;
	char	*temp;
	char	buffer[50];
	int		chars_read;

	close(g_tudao.pipe_heredoc[1]);
	str = ft_strdup("");
	chars_read = read(g_tudao.pipe_heredoc[0], buffer, 49);
	while (chars_read > 0)
	{
		buffer[chars_read] = '\0';
		temp = str;
		str = ft_strjoin(temp, buffer);
		ft_free_ptr((void *)&temp);
		chars_read = read(g_tudao.pipe_heredoc[0], buffer, 49);
	}
	temp = g_tudao.prompt_input;
	if (temp)
		g_tudao.prompt_input = ft_strjoin(temp, str);
	ft_free_ptr((void *)&temp);
	ft_free_ptr((void *)&str);
	close(g_tudao.pipe_heredoc[0]);
	return ;
}

void	get_heredoc_content(t_data_hd *hd, int *pipe_fds, int hd_line_nbr)
{
	char	*line_read;

	line_read = readline("> ");
	if (!line_read)
		close_heredoc_prompt((char *) hd->cursor->content, hd_line_nbr);
	else
	{
		while (ft_strncmp(line_read, (char *) hd->cursor->content,
				ft_strlen((char *) hd->cursor->content) + 1) != 0)
		{
			g_tudao.line_count++;
			ft_putendl_fd(line_read, pipe_fds[1]);
			ft_putendl_fd(line_read, hd->aux_pipes[hd->counter][1]);
			ft_free_ptr((void *)&line_read);
			line_read = readline("> ");
			if (!line_read)
			{
				close_heredoc_prompt((char *) hd->cursor->content, hd_line_nbr);
				break ;
			}
		}
		if (line_read)
			ft_putendl_fd(line_read, hd->aux_pipes[hd->counter][1]);
		ft_free_ptr((void *)&line_read);
	}
}

void	get_input_line(t_data_hd *hd, int *pipe_fds)
{
	int		hd_line_nbr;

	hd_line_nbr = g_tudao.line_count;
	get_heredoc_content(hd, pipe_fds, hd_line_nbr);
	ft_close_pipe_fds(pipe_fds);
	ft_free_ptr((void *)&(hd->str));
	ft_free_pipe_arr(&(hd->aux_pipes), hd->total_pipes);
	ft_close_pipe_fds(g_tudao.pipe_heredoc);
	free_and_exit_fork(NULL);
}
