/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_executor_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 01:25:26 by roaraujo          #+#    #+#             */
/*   Updated: 2022/05/10 17:41:20 by coder            ###   ########.fr       */
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
		|| ft_strchr(command_str, '/'));
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
			|| (ft_strncmp(str, "unset", 6) == 0)))
		return (true);
	return (false);
}

void	process_child_return_code(int wstatus)
{
	if (WIFEXITED(wstatus))
		g_data.exit.code = WEXITSTATUS(wstatus);
	else if (WIFSIGNALED(wstatus))
	{
		g_data.exit.code = WTERMSIG(wstatus) + 128;
		if (g_data.exit.code == 130)
			ft_putendl_fd("", 2);
		else if (g_data.exit.code == 131)
			ft_putendl_fd(BRED "Quit (core dumped)" COLOUR_RESET, 2);
	}
	else
		g_data.exit.code = -42;
	return ;
}

bool	is_valid_env_path(char *path, char *command_str)
{
	if (path && path[0] != '\0')
		return (true);
	else
	{
		g_data.exit.msg = ft_strjoin(command_str,
				": No such file or directory");
		g_data.exit.code = 127;
		return (false);
	}
}
