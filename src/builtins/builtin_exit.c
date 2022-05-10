/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:22:12 by roaraujo          #+#    #+#             */
/*   Updated: 2022/05/10 17:41:20 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_exit(t_command *command)
{
	t_list	*args_list;

	g_data.exit.flag = true;
	ft_putendl_fd("exit", 2);
	args_list = command->cmds_with_flags->next;
	if (args_list)
	{
		if (!ft_isnumeric_s((char *) args_list->content))
		{
			ft_putstr_fd("exit: ", 2);
			ft_putstr_fd((char *) args_list->content, 2);
			ft_putendl_fd(": numeric argument required", 2);
			g_data.exit.code = 2;
			return ;
		}
		if (args_list->next)
		{
			g_data.exit.msg = ft_strdup("exit: too many arguments");
			g_data.exit.code = 2;
			g_data.exit.flag = false;
			return ;
		}
		g_data.exit.code = ft_atoi((char *) args_list->content);
	}
}
