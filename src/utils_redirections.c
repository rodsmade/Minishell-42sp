/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaraujo <roaraujo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 20:10:21 by roaraujo          #+#    #+#             */
/*   Updated: 2022/04/07 21:18:43 by roaraujo         ###   ########.fr       */
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

int	**ft_make_pipes(int total_pipes)
{
	int	i;
	int	**pipes;

	pipes = (int **)malloc(total_pipes * sizeof(int *));
	if (!pipes)
	{
		ft_putendl_fd("Malloc error", 2);
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < total_pipes)
	{
		pipes[i] = (int *)malloc(2 * sizeof(int));
		if (!pipes[i])
		{
			ft_putendl_fd("Malloc error", 2);
			exit(EXIT_FAILURE);
		}
		pipe(pipes[i]);
		i++;
	}
	return (pipes);
}

void	ft_close_pipe_fds(int *pipe)
{
	if (pipe)
	{
		close(pipe[0]);
		close(pipe[1]);
	}
	return ;
}

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

void	capture_heredocs(t_command *cmd)
{
	t_list	*pivot;
	char	*line_read;
	int		pipe_fds[2];
	int		**aux_pipes;
	int		pid;
	int		wstatus;
	char	*str;
	char	*aux_str;
	char	*tmp_str;
	int		total_pipes;
	int		counter;

	total_pipes = ft_lst_size(((t_command *)g_tudao.command_table.main_pipeline->content)->heredocs);
	aux_pipes = ft_make_pipes(total_pipes);
	pivot = cmd->heredocs;
	str = ft_strdup("\n");
	counter = 0;
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
				write(aux_pipes[counter][1], line_read, ft_strlen(line_read));
				write(aux_pipes[counter][1], "\n", 1);
				ft_free_ptr((void *)&line_read);
				line_read = readline("> ");
			}
			write(aux_pipes[counter][1], line_read, ft_strlen(line_read));
			write(aux_pipes[counter][1], "\n", 1);
			close(pipe_fds[0]);
			close(pipe_fds[1]);
			ft_free_ptr((void *)&line_read);
			ft_free_ptr((void *)&str);
			free_and_exit_fork(NULL);
		}
		waitpid(pid, &wstatus, 0);
		close(pipe_fds[1]);
		close(aux_pipes[counter][1]);
		tmp_str = get_pipe_content(aux_pipes[counter][0]);
		close(aux_pipes[counter][0]);
		aux_str = str;
		str = ft_strjoin(aux_str, tmp_str);
		ft_free_ptr((void *)&tmp_str);
		ft_free_ptr((void *)&aux_str);
		if (!pivot->next)
			dup2(pipe_fds[0], STDIN_FILENO);
		else
			close(pipe_fds[0]);
		pivot = pivot->next;
		counter++;
	}
	write(g_tudao.pipe_heredoc[1], str, ft_strlen(str));
	ft_free_ptr((void *)&str);
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
