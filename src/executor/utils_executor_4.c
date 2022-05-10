/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_executor_4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 22:38:02 by adrianofaus       #+#    #+#             */
/*   Updated: 2022/05/10 17:41:20 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_directory(char *path)
{
	struct stat	status_buffer;
	int			is_dir;

	if (stat(path, &status_buffer) == -1)
		return (0);
	is_dir = S_ISDIR(status_buffer.st_mode);
	if (is_dir != 0)
	{
		ft_free_ptr((void *)&g_data.exit.msg);
		g_data.exit.msg = ft_strjoin(path, \
		": Is a directory");
		g_data.exit.code = 126;
		return (true);
	}
	else
		return (false);
}

bool	is_accessible(char *cmd_str, int is_abs_path, char *combination)
{
	ft_free_ptr((void *)&g_data.exit.msg);
	if (combination != NULL && access(combination, F_OK) == 0)
	{
		g_data.exit.code = 0;
		g_data.exit.msg = NULL;
		return (true);
	}
	else
	{
		g_data.exit.code = 127;
		if (is_abs_path == true)
			g_data.exit.msg = ft_strjoin(cmd_str, \
			": No such file or directory");
		else if (is_abs_path == false)
			g_data.exit.msg = ft_strjoin(cmd_str, \
			": command not found");
		return (false);
	}
}

bool	is_executable(char *command_str)
{
	if (access(command_str, X_OK) == 0)
		return (true);
	else
	{
		ft_free_ptr((void *)&g_data.exit.msg);
		g_data.exit.msg = ft_strjoin(command_str, \
		"Permission denied");
		g_data.exit.code = 126;
		return (false);
	}
}

char	*find_valid_combination(char **split_paths, char *command_str)
{
	char	*combination;
	int		i;

	i = -1;
	combination = NULL;
	while (split_paths && split_paths[++i] && \
	ft_strncmp(command_str, ".", 2) && ft_strncmp(command_str, "..", 2))
	{
		combination = ft_strjoin_3(split_paths[i], "/", command_str);
		if (is_accessible(command_str, false, combination) == true)
			break ;
		ft_free_ptr((void *)&combination);
	}
	if (combination != NULL)
	{
		if (is_directory(combination) == false)
		{
			if (is_executable(combination) == true)
				return (combination);
		}
	}
	else
		is_accessible(command_str, false, combination);
	ft_free_ptr((void *)&combination);
	return (NULL);
}

void	capture_redirections(int cmd_counter, t_command *cmd)
{
	int	total_pipes;
	int	i;

	total_pipes = ft_lst_size(g_data.command_table.main_pipeline) - 1;
	if (!cmd->heredocs)
	{
		if (cmd_counter)
			dup2(g_data.cmd_pipes[cmd_counter - 1][0], STDIN_FILENO);
		close(g_data.pipe_heredoc[0]);
		close(g_data.pipe_heredoc[1]);
	}
	else
		capture_heredocs(cmd, cmd_counter);
	if (cmd_counter != total_pipes && total_pipes)
		dup2(g_data.cmd_pipes[cmd_counter][1], STDOUT_FILENO);
	capture_inputs(cmd);
	capture_outputs(cmd);
	capture_o_concats(cmd);
	close(g_data.backup_stdin);
	i = -1;
	while (++i < total_pipes)
	{
		close(g_data.cmd_pipes[i][0]);
		close(g_data.cmd_pipes[i][1]);
	}
}
