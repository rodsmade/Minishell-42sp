/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_heredoc_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 17:27:16 by roaraujo          #+#    #+#             */
/*   Updated: 2022/05/10 17:41:20 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_heredoc_data(t_data_hd *hd, t_command *cmd, int cmd_count)
{
	hd->total_pipes = ft_lst_size(cmd->heredocs);
	hd->pipes_per_eof = ft_make_pipes(hd->total_pipes);
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

	close(g_data.pipe_heredoc[1]);
	str = ft_strdup("");
	chars_read = read(g_data.pipe_heredoc[0], buffer, 49);
	while (chars_read > 0)
	{
		buffer[chars_read] = '\0';
		temp = str;
		str = ft_strjoin(temp, buffer);
		ft_free_ptr((void *)&temp);
		chars_read = read(g_data.pipe_heredoc[0], buffer, 49);
	}
	temp = g_data.prompt_input;
	if (temp)
		g_data.prompt_input = ft_strjoin(temp, str);
	ft_free_ptr((void *)&temp);
	ft_free_ptr((void *)&str);
	close(g_data.pipe_heredoc[0]);
	return ;
}

void	get_heredoc_content(t_data_hd *hd, int *pipe_fds, int hd_line_nbr)
{
	char	*line_read;

	line_read = readline("> ");
	if (!line_read)
		close_heredoc_prompt(hd, hd_line_nbr);
	else if (line_read)
	{
		while (ft_strncmp(line_read, (char *) hd->cursor->content,
				ft_strlen((char *) hd->cursor->content) + 1) != 0)
		{
			g_data.line_count++;
			ft_putendl_fd(line_read, pipe_fds[1]);
			ft_putendl_fd(line_read, hd->pipes_per_eof[hd->counter][1]);
			ft_free_ptr((void *)&line_read);
			line_read = readline("> ");
			if (!line_read)
			{
				close_heredoc_prompt(hd, hd_line_nbr);
				break ;
			}
		}
		if (line_read)
			ft_putendl_fd(line_read, hd->pipes_per_eof[hd->counter][1]);
		ft_free_ptr((void *)&line_read);
	}
}

void	get_input_line(t_data_hd *hd, int *pipe_fds)
{
	int		hd_line_nbr;

	hd_line_nbr = g_data.line_count;
	set_signal_hook(SIGINT, sighandler_within_hd_prompt, &g_data.action);
	get_heredoc_content(hd, pipe_fds, hd_line_nbr);
	ft_close_pipe_fds(pipe_fds);
	ft_free_ptr((void *)&(hd->str));
	ft_free_pipe_arr(&(hd->pipes_per_eof), hd->total_pipes);
	free_and_exit_fork(NULL, g_data.exit.code);
}
