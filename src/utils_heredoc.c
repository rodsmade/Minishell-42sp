/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaraujo <roaraujo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 17:27:16 by roaraujo          #+#    #+#             */
/*   Updated: 2022/04/11 21:31:23 by roaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_heredoc_data(t_data_hd *hd, t_command *cmd, int cmd_count)
{
	hd->total_pipes = ft_lst_size(((t_command *) \
	g_tudao.command_table.main_pipeline->content)->heredocs);
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
	g_tudao.prompt_input = ft_strjoin(temp, str);
	ft_free_ptr((void *)&temp);
	ft_free_ptr((void *)&str);
	close(g_tudao.pipe_heredoc[0]);
	return ;
}
