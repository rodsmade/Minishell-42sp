/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_heredoc_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaraujo <roaraujo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 00:02:14 by roaraujo          #+#    #+#             */
/*   Updated: 2022/04/18 00:14:37 by roaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
