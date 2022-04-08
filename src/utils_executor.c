/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_executor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrianofaus <adrianofaus@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 18:45:03 by roaraujo          #+#    #+#             */
/*   Updated: 2022/04/08 16:50:22 by adrianofaus      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_built_in(char *str)
{
	if (str
		&& ((ft_strncmp(str, "pwd", 4) == 0)
			|| (ft_strncmp(str, "cd", 3) == 0)
			|| (ft_strncmp(str, "echo", 5) == 0)
			|| (ft_strncmp(str, "env", 4) == 0)
			|| (ft_strncmp(str, "exit", 5) == 0)
			|| (ft_strncmp(str, "export", 7) == 0)
			|| (ft_strncmp(str, "clear", 6) == 0)
			|| (ft_strncmp(str, "unset", 6) == 0)))
		return (true);
	return (false);
}

char	**assemble_cmd_array(t_command *command)
{
	char	**cmd_arr;
	t_list	*pivot;
	int		lst_len;
	int		i;

	lst_len = ft_lst_size(command->cmds_with_flags);
	cmd_arr = (char **)malloc((lst_len + 1) * sizeof(char *));
	pivot = command->cmds_with_flags;
	i = 0;
	while (pivot)
	{
		cmd_arr[i] = (char *)pivot->content;
		i++;
		pivot = pivot->next;
	}
	cmd_arr[i] = NULL;
	return (cmd_arr);
}

bool	has_absolute_path(char *command_str)
{
	return (!ft_strncmp(command_str, "~", 1)
		|| !ft_strncmp(command_str, "/", 1)
		|| !ft_strncmp(command_str, "./", 2)
		|| !ft_strncmp(command_str, "../", 3)
		|| !ft_strncmp(command_str, ".", 1));
}

char	*find_cmd_in_path_var(char *command_str)
{
	char	*all_paths;
	char	**split_paths;
	char	*cmd_path;
	int		i;

	all_paths = read_hashtable(g_tudao.hashtable[hash_string("PATH")],
			"PATH");
	split_paths = ft_split(all_paths, ':');
	i = -1;
	while (split_paths[++i])
	{
		cmd_path = ft_strjoin_3(split_paths[i], "/", command_str);
		if (access(cmd_path, F_OK) == 0)
		{
			ft_free_arr((void *)&split_paths);
			return (cmd_path);
		}
		else
			ft_free_ptr((void *)&cmd_path);
	}
	ft_free_arr((void *)&split_paths);
	return (NULL);
}

char	*find_cmd_path(char *command_str)
{
	if (has_absolute_path(command_str))
	{
		if (access(command_str, F_OK) == 0)
			return (command_str);
		else
			return (NULL);
	}
	return (find_cmd_in_path_var(command_str));
}
