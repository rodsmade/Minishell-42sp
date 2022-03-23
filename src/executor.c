/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 22:53:25 by coder             #+#    #+#             */
/*   Updated: 2022/03/23 20:14:46 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_var_assignment(char *str)
{
	int	equal_sign;

	equal_sign = 0;
	if (!str)
		return (false);
	while (*str)
	{
		if (*str == '=')
			equal_sign++;
		str++;
	}
	if (equal_sign != 1)
		return (false);
	else
		return (true);
}

bool	has_only_var_assignments(t_list *pipeline)
{
	t_list	*pivot;

	pivot = ((t_command *)pipeline->content)->cmds_with_flags;
	while (pivot)
	{
		if (!is_var_assignment(pivot->content))
			return (false);
		pivot = pivot->next;
	}
	return (true);
}

bool	is_built_in(char *str)
{
	if ((ft_strncmp(str, "pwd", 4) == 0)
		|| (ft_strncmp(str, "cd", 3) == 0) 
		|| (ft_strncmp(str, "echo", 5) == 0)
		|| (ft_strncmp(str, "env", 4) == 0)
		|| (ft_strncmp(str, "exit", 5) == 0)
		|| (ft_strncmp(str, "export", 7) == 0)
		|| (ft_strncmp(str, "clear", 6) == 0)
		|| (ft_strncmp(str, "unset", 6) == 0))
		return (true);
	return (false);
}

void	execute_built_in(char *str)
{
	if (ft_strncmp(str, "pwd", 4) == 0)
		printf("pwd detected!\n");
	if (ft_strncmp(str, "cd", 3) == 0)
		printf("cd detected!\n");
	if (ft_strncmp(str, "echo", 5) == 0)
		printf("echo detected!\n");
	if (ft_strncmp(str, "env", 4) == 0)
		printf("env detected!\n");
	if (ft_strncmp(str, "exit", 5) == 0)
		printf("exit detected!\n");
	if (ft_strncmp(str, "export", 7) == 0)
		printf("export detected!\n");
	if (ft_strncmp(str, "unset", 6) == 0)
		printf("unset detected!\n");
	if (ft_strncmp(str, "clear", 6) == 0)
		printf("clear detected!\n");
	return ;
}

void	assign_var(void)
{
	printf("this is a variable assignment\n");
	return ;
}

void	execute_pipelines(void)
{
	t_list	*pivot_cmd;

	pivot_cmd = g_tudao.command_table.main_pipeline;
	while (pivot_cmd)
	{
		// handle_redirections(pivot_cmd);
		if (has_only_var_assignments(pivot_cmd))
			assign_var();
		else if (is_built_in(((t_command *)pivot_cmd->content)->cmds_with_flags->content))
			execute_built_in(((t_command *)pivot_cmd->content)->cmds_with_flags->content);
		// else if (has_absolute_path())
		// 	exec_absolute_path();
		// else
		// 	exec_env_path();
		pivot_cmd = pivot_cmd->next;
	}
	return ;
}