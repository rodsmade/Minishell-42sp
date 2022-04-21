/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redirections_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaraujo <roaraujo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 17:25:06 by adrianofaus       #+#    #+#             */
/*   Updated: 2022/04/18 00:02:40 by roaraujo         ###   ########.fr       */
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

void	close_heredoc_prompt(char *hd_delimiter, int curr_line_count)
{
	char	*itoa;

	ft_putstr_fd("bash: warning: here-document at line ", 2);
	itoa = ft_itoa(curr_line_count);
	ft_putstr_fd(itoa, 2);
	ft_free_ptr((void *)&itoa);
	ft_putstr_fd(" delimited by end-of-file (wanted `", 2);
	ft_putstr_fd(hd_delimiter, 2);
	ft_putendl_fd("')", 2);
	return ;
}
