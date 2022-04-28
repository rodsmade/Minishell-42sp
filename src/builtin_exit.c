/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:22:12 by roaraujo          #+#    #+#             */
/*   Updated: 2022/04/27 22:52:08 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_exit(t_command *command)
{
	t_list	*args_list;

	g_tudao.exit.flag = true;
	ft_putendl_fd("exit", 2);
	args_list = command->cmds_with_flags->next;
	if (args_list)
	{
		if (!ft_isnumeric_s((char *) args_list->content))
		{
			ft_putstr_fd("exit: ", 2);
			ft_putstr_fd((char *) args_list->content, 2);
			ft_putendl_fd(": numeric argument required", 2);
			g_tudao.exit.code = 2;
			return ;
		}
		if (args_list->next)
		{
			ft_putendl_fd("bash: exit: too many arguments", 2);
			g_tudao.exit.code = EXIT_FAILURE;
			return ;
		}
		g_tudao.exit.code = ft_atoi((char *) args_list->content);
	}
	return ;
}
