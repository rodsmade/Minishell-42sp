/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_executor_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaraujo <roaraujo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 01:25:26 by roaraujo          #+#    #+#             */
/*   Updated: 2022/04/09 01:26:22 by roaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	alters_main_memory(char *built_in)
{
	if (ft_strncmp("cd", built_in, 3) == 0
		|| ft_strncmp("exit", built_in, 5) == 0
		|| ft_strncmp("export", built_in, 7) == 0
		|| ft_strncmp("unset", built_in, 6) == 0)
		return (true);
	else
		return (false);
}

bool	has_absolute_path(char *command_str)
{
	return (!ft_strncmp(command_str, "~", 1)
		|| !ft_strncmp(command_str, "/", 1)
		|| !ft_strncmp(command_str, "./", 2)
		|| !ft_strncmp(command_str, "../", 3)
		|| !ft_strncmp(command_str, ".", 1));
}

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
