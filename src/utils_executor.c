/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_executor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrianofaus <adrianofaus@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 18:45:03 by roaraujo          #+#    #+#             */
/*   Updated: 2022/04/26 01:25:01 by adrianofaus      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*find_cmd_in_path_var(char *command_str)
{
	char	*all_paths;
	char	**split_paths;
	char	*combination;

	if (command_str && command_str[0] != '\0')
	{
		all_paths = read_hashtable(g_tudao.hashtable[hash_string("PATH")],
				"PATH");
		if (is_valid_env_path(all_paths, command_str) == true)
		{
			split_paths = ft_split(all_paths, ':');
			combination = find_valid_combination(split_paths, command_str);
			ft_free_arr((void *)&split_paths);
			if (combination == NULL)
				return (NULL);
			else if (combination)
				return (combination);
		}
	}
	return (NULL);
}

char	*find_cmd_path(char **cmd_arr)
{
	char	*command_str;

	command_str = cmd_arr[0];
	if (has_absolute_path(command_str) == true)
	{
		if (is_accessible(command_str, true) == true)
		{
			if (is_directory(command_str) == false)
			{
				if (is_executable(command_str) == true)
					return (command_str);
			}
		}
		ft_free_ptr((void *)&cmd_arr);
		free_and_exit_fork(g_tudao.exit.msg, g_tudao.exit.code);
	}
	command_str = find_cmd_in_path_var(command_str);
	if (command_str == NULL)
	{
		ft_free_ptr((void *)&cmd_arr);
		free_and_exit_fork(g_tudao.exit.msg, g_tudao.exit.code);
	}
	return (command_str);
}
