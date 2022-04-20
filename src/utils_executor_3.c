/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_executor_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaraujo <roaraujo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 01:25:26 by roaraujo          #+#    #+#             */
/*   Updated: 2022/04/21 01:30:08 by roaraujo         ###   ########.fr       */
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

void	process_child_return_code(int wstatus)
{
	if (WIFEXITED(wstatus))
		g_tudao.ext_routine.code = WEXITSTATUS(wstatus);
	else if (WIFSIGNALED(wstatus))
	{
		g_tudao.ext_routine.code = WTERMSIG(wstatus) + 128;
		if (g_tudao.ext_routine.code == 130)
			ft_putendl_fd("", 2);
		else if (g_tudao.ext_routine.code == 131)
			ft_putendl_fd("Quit (core dumped)", 2);
	}
	else
		g_tudao.ext_routine.code = -42;
	return ;
}
